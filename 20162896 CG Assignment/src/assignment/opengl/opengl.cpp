#include "opengl.h"

//Screen size
unsigned int SCR_WIDTH = 800;
unsigned int SCR_HEIGHT = 600;

//Camera
Camera camera(glm::vec3(2.0f, 2.0f, 4.0f)); 
bool firstMouse = true;
float lastX = SCR_WIDTH / 2; //Half of vertical window size
float lastY = SCR_HEIGHT / 2; //Half of horizontal window size

//Timing stuff
float deltaTime = 0.0f;	// Time between current frame and last frame
float lastFrame = 0.0f; // Time of last frame

// lighting
glm::vec3 lightPos(0.0f, 1.0f, 3.0f); //Sets the origin of the light source.

//Settings
float lightRadius = 1.0;
int perspectiveProj = true;
int followCamera = true;
int sceneBrightness = true;
float chestAnimationFrame = 0.0f;

int perspectiveProjHeld = false;
int followCameraHeld = false;
int sceneBrightnessHeld = false;
int chestAnimationHeld = false;

int main()
{
    glfwInit(); // initialize GLFW

    //glfwWindowHint(OPTION, VALUE FOR OPTION);
    glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 3); //Specifies the version number
    glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 3);
    glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE); //Use core profile mode
    //glfwWindowHint(GLFW_OPENGL_FORWARD_COMPAT, GL_TRUE); //For MAC-OS
  

    //glfwCreateWindow(WIDTH, HEIGHT, "WINDOW NAME", NULL, NULL); 
    GLFWwindow* window = glfwCreateWindow(SCR_WIDTH, SCR_HEIGHT, "LearnOpenGL", NULL, NULL); //Creates a window object
    if (window == NULL) //Error state, if the window is never created
    {
        std::cout << "Failed to create GLFW window" << std::endl; //C++ print statement
        glfwTerminate(); //Terminates the GLFW library
        return -1; 
    }
    glfwMakeContextCurrent(window); //Makes the created window the "current" window
    glfwSetFramebufferSizeCallback(window, framebuffer_size_callback); //Specifies which method to call on window resize.
    glfwSetCursorPosCallback(window, mouse_callback); //Method call on cursor position change
    glfwSetScrollCallback(window, scroll_callback); //Method call on mouse scroll

    glfwSetInputMode(window, GLFW_CURSOR, GLFW_CURSOR_DISABLED); // tell GLFW to capture our mouse

    // Some GLAD config stuff
    if (!gladLoadGLLoader((GLADloadproc)glfwGetProcAddress)) //Initialises GLAD depending on the OS
    {
        std::cout << "Failed to initialize GLAD" << std::endl;
        return -1;
    }    

    glViewport(0, 0, SCR_WIDTH, SCR_HEIGHT); //Specifies an OpenGL viewport of size 800x600
	
    // configure global opengl state
    // -----------------------------
    glEnable(GL_DEPTH_TEST); //Enables Z Buffering


	// build and compile our shader program
    // ------------------------------------
    Shader singleTexture("singleTexture.vs", "singleTexture.fs");
    Shader twoTextures("TwoTextures.vs", "TwoTextures.fs");
    Shader doorShader("door.vs", "door.fs");    
    Shader slabShader("slab.vs", "slab.fs");    
    Shader pigShader("pig.vs", "pig.fs");  
    Shader pigBodyShader("pig.vs", "pigBody.fs");  
    Shader chestShader("chest.vs", "chest.fs");  


    //CUBE VAO + VBO
	unsigned int VBO; //Vertex buffer object. Stores vertexes in the GPU
	unsigned int cubeVAO; //Vertex array object. Stores configurations for VBOs
	glGenBuffers(1, &VBO); //Generates the buffer object
	glGenVertexArrays(1, &cubeVAO); //Generate VBO

	glBindVertexArray(cubeVAO); //Binds VAO as as vertex array.

	glBindBuffer(GL_ARRAY_BUFFER, VBO); //Binds the created buffer as an ARRAY_BUFFER	
	glBufferData(GL_ARRAY_BUFFER, sizeof(vertices), vertices, GL_STATIC_DRAW); //Copies all the data in verticies to the buffer

	//Tells openGL how it should render verticies.  
	// position attribute  - attribute location 0, stride of 3 floats, offset of 0 floats
    glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 8 * sizeof(float), (void*)0);
    glEnableVertexAttribArray(0);
    // normal attribute
    glVertexAttribPointer(1, 3, GL_FLOAT, GL_FALSE, 8 * sizeof(float), (void*)(3 * sizeof(float)));
    glEnableVertexAttribArray(1);
    //Texture attribute
    glVertexAttribPointer(2, 2, GL_FLOAT, GL_FALSE, 8 * sizeof(float), (void*)(6 * sizeof(float)));
    glEnableVertexAttribArray(2);

   //Load and create textures
    unsigned int wood = loadTexture("wood");
    unsigned int cb_top = loadTexture("cb_top");
    unsigned int cb_side = loadTexture("cb_side_1");
    unsigned int grass_top = loadTexture("grass_top");
    unsigned int grass_side = loadTexture("grass_side");
    unsigned int door = loadTexture("door");
    unsigned int glass = loadTexture("glass");
    unsigned int stone = loadTexture("stone");
    unsigned int tree_side = loadTexture("tree_side");
    unsigned int tree_leaf = loadTexture("tree_leaf"); 
    unsigned int water = loadTexture("water");

    //Load pig textures
    int pigTextures[8];
    pigTextures[0] = loadTexture("pig/pig_head_front");
    pigTextures[1] = loadTexture("pig/pig_head_side");  
    pigTextures[2] = loadTexture("pig/pig_head_else"); 
    pigTextures[3] = loadTexture("pig/pig_body_front"); 
    pigTextures[4] = loadTexture("pig/pig_body_back"); 
    pigTextures[5] = loadTexture("pig/pig_body_side"); 
    pigTextures[6] = loadTexture("pig/pig_foot_front");     
    pigTextures[7] = loadTexture("pig/pig_foot_else");    

    //Load chest textures
    int chestTextures[7];
    chestTextures[0] = loadTexture("chest/chest_square");
    chestTextures[1] = loadTexture("chest/chest_bottom_front"); 
    chestTextures[2] = loadTexture("chest/chest_bottom_top");     
    chestTextures[3] = loadTexture("chest/chest_bottom_side"); 
    chestTextures[4] = loadTexture("chest/chest_top_front");  
    chestTextures[5] = loadTexture("chest/chest_top_bottom");  
    chestTextures[6] = loadTexture("chest/chest_top_side");     

   

    //Render loop
    while(!glfwWindowShouldClose(window)) //checks at the start of each loop iteration if GLFW has been instructed to close.
    {
        //Deltatime timing things for camera
        float currentFrame = glfwGetTime();
        deltaTime = currentFrame - lastFrame;
        lastFrame = currentFrame; 

		//INPUT 
        processInput(window); //Checks for input every iteration

		//RENDER
    	glClearColor(0.1f, 0.1f, 0.1f, 1.0f); //Sets the background state
        glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT); // also clear the depth buffer now!
        
        renderTwoTextures(twoTextures, grass_top, grass_side, cubeVAO, glm::vec3(-10,-1,-10), glm::vec3(20,1,20), &grassMat); //GRASS 
        renderSingleTexture(singleTexture, water, cubeVAO, glm::vec3(-20,-2,-20), glm::vec3(40,1,40), &waterMat); //WATER 
        renderPig(pigShader, pigBodyShader, pigTextures, cubeVAO, glm::vec3(-4.0f,0.8f,1.0f), &pigMat); //PIG
        
        renderSingleTexture(singleTexture, wood, cubeVAO, glm::vec3(0,0,0), glm::vec3(7,1,7), &woodMat); //FLOOR
        renderSingleTexture(singleTexture, wood, cubeVAO, glm::vec3(0,1,0), glm::vec3(7,4,1), &woodMat); //WALL BACK
        renderSingleTexture(singleTexture, wood, cubeVAO, glm::vec3(0,1,1), glm::vec3(1,4,6), &woodMat); //WALL LEFT SIDE
        renderSingleTexture(singleTexture, wood, cubeVAO, glm::vec3(6,1,1), glm::vec3(1,4,6), &woodMat); //WALL RIGHT SIDE
        renderTwoTextures(twoTextures, cb_top, cb_side, cubeVAO, glm::vec3(1,1,1), glm::vec3(1,1,1), &woodMat); //CRAFTING BENCH

        renderSingleTexture(singleTexture, wood, cubeVAO, glm::vec3(1,3,6), glm::vec3(5,2,1), &woodMat); //WALL FRONT - WOOD 
        renderSingleTexture(singleTexture, glass, cubeVAO, glm::vec3(1,1,6), glm::vec3(2,2,1), &glassMat); //WALL FRONT - GLASS (LEFT)
        renderSingleTexture(singleTexture, glass, cubeVAO, glm::vec3(4,1,6), glm::vec3(2,2,1), &glassMat); //WALL FRONT - GLASS (RIGHT)
        renderDoor(doorShader, door, cubeVAO, glm::vec3(3,1,7), &woodMat); //WALL FRONT - DOOR 

        renderSingleTexture(slabShader, wood, cubeVAO, glm::vec3(0,0,7), glm::vec3(7,0.5,1), &woodMat); //FRONT SLABS
        renderSingleTexture(slabShader, stone, cubeVAO, glm::vec3(-1,5,-1), glm::vec3(9,0.5,9), &stoneMat); //ROOF SLABS
        renderSingleTexture(slabShader, stone, cubeVAO, glm::vec3(0,5.5,0), glm::vec3(7,0.5,7), &stoneMat); //ROOF SLABS

        renderSingleTexture(singleTexture, tree_side, cubeVAO, glm::vec3(-6,0,0), glm::vec3(1,4,1), &woodMat); // TREE LOG
        renderSingleTexture(singleTexture, tree_leaf, cubeVAO, glm::vec3(-8,4,-2), glm::vec3(5,1,5), &leafMat); // TREE LEAFS (Layer 1)
        renderSingleTexture(singleTexture, tree_leaf, cubeVAO, glm::vec3(-7,5,-1), glm::vec3(3,1,3), &leafMat); // TREE LEAFS (Layer 2)
        renderChest(chestShader, chestTextures, cubeVAO, glm::vec3(-5,0,0), &woodMat);
        if (chestAnimationFrame > 1) {
            renderInsideChest(singleTexture, wood, cubeVAO, glm::vec3(-5,1,0), &woodMat);
        }
        
		//GLFW
        glfwSwapBuffers(window); //Changes the colors of the pixels on the screen 
        glfwPollEvents();    //Checks if any events (e.g. input) have occured, changes states and calls functions
    }

    // De-allocate all resources once they've outlived their purpose:
    glDeleteVertexArrays(1, &cubeVAO);
    glDeleteBuffers(1, &VBO);

    glfwTerminate(); //Terminates all GLFW stuff before we exit
    return 0;

}

//This method gets called every time the window is resized, and sets the new dimentions of the viewport
void framebuffer_size_callback(GLFWwindow* window, int width, int height)
{
    glViewport(0, 0, width, height);
}  

//Mouse movement
void mouse_callback(GLFWwindow* window, double xpos, double ypos){

    if (firstMouse) // initially set to true. Is so camera does not jump when we initially start the program
    {
        lastX = xpos;
        lastY = ypos;
        firstMouse = false;
    }
    float xoffset = xpos - lastX; //Calculates offset between previous and current frame
    float yoffset = lastY - ypos; // reversed since y-coordinates range from bottom to top
    lastX = xpos;
    lastY = ypos;

    camera.ProcessMouseMovement(xoffset, yoffset);
}

//Mouse scrolling
void scroll_callback(GLFWwindow* window, double xoffset, double yoffset)
{
    camera.ProcessMouseScroll(yoffset);
}

//Controls all user input
void processInput(GLFWwindow *window)
{

    //Sprint 
    if (glfwGetKey(window, GLFW_KEY_LEFT_SHIFT) == GLFW_PRESS){
        camera.updateSpeed(5.0f);
    }
    else {
        camera.updateSpeed(2.5f);
    }

    //Close window
    if(glfwGetKey(window, GLFW_KEY_ESCAPE) == GLFW_PRESS) //If the escape key is pressed
        glfwSetWindowShouldClose(window, true); //Close the window
    
    //Switch between normal and wireframe rendering
	if (glfwGetKey(window, GLFW_KEY_1) == GLFW_PRESS)
		glPolygonMode(GL_FRONT_AND_BACK, GL_LINE);
	if (glfwGetKey(window, GLFW_KEY_2) == GLFW_PRESS)
		glPolygonMode(GL_FRONT_AND_BACK, GL_FILL);
    
    //Camera controls
    if (glfwGetKey(window, GLFW_KEY_W) == GLFW_PRESS)
        camera.ProcessKeyboard(FORWARD, deltaTime); //Renders objects closer (increases z value)
    if (glfwGetKey(window, GLFW_KEY_S) == GLFW_PRESS) 
        camera.ProcessKeyboard(BACKWARD, deltaTime); //Renders objects further away (decreases z)
    if (glfwGetKey(window, GLFW_KEY_A) == GLFW_PRESS)
        camera.ProcessKeyboard(LEFT, deltaTime);
    if (glfwGetKey(window, GLFW_KEY_D) == GLFW_PRESS) 
        camera.ProcessKeyboard(RIGHT, deltaTime);

    //Change Settings - Change projection
    if (glfwGetKey(window, GLFW_KEY_P) == GLFW_PRESS){ 
        if (!perspectiveProjHeld){
            perspectiveProj = !perspectiveProj;
            perspectiveProjHeld = true;
        }    
    }
    if (glfwGetKey(window, GLFW_KEY_P) == GLFW_RELEASE)
        perspectiveProjHeld = false;

    if (glfwGetKey(window, GLFW_KEY_F) == GLFW_PRESS){ 
        if (!followCameraHeld){
            followCamera = !followCamera;
            followCameraHeld = true;
        }    
    }

    if (glfwGetKey(window, GLFW_KEY_F) == GLFW_RELEASE)
        followCameraHeld = false;

    //Change Settings - Light intensity
    if (glfwGetKey(window, GLFW_KEY_K) == GLFW_PRESS)
        if (lightRadius > 0) {
            lightRadius -= 0.05;
        }
    if (glfwGetKey(window, GLFW_KEY_L) == GLFW_PRESS) {
        if (lightRadius < 5) {
            lightRadius += 0.05;
        }
    }

    //Change Settings - Scenery light
    if (glfwGetKey(window, GLFW_KEY_O) == GLFW_PRESS){ 
        if (!sceneBrightnessHeld){
            sceneBrightness = !sceneBrightness;
            sceneBrightnessHeld = true;
        }    
    }
    if (glfwGetKey(window, GLFW_KEY_O) == GLFW_RELEASE)
        sceneBrightnessHeld = false;

    //Start animation - chest
    if (glfwGetKey(window, GLFW_KEY_R) == GLFW_PRESS){ 
        if (!chestAnimationHeld){
            chestAnimationFrame = 0.05;
            chestAnimationHeld = true;
        }    
    }
    if (glfwGetKey(window, GLFW_KEY_R) == GLFW_RELEASE)
        chestAnimationHeld = false;
}

//Loads a texture and returns the binded value as an int.
unsigned int loadTexture(std::string filename){
    unsigned int texture;
    glGenTextures(1, &texture);  //Generates a texture 
    glBindTexture(GL_TEXTURE_2D, texture);  //Sets the texture variable to the current texture
    // set the texture wrapping parameters
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_REPEAT);	// set texture wrapping to GL_REPEAT (default wrapping method)
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_REPEAT);
    
    // set texture filtering parameters
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_NEAREST);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_NEAREST);

    int width, height, nrChannels;
    stbi_set_flip_vertically_on_load(true); // tell stb_image.h to flip loaded texture's on the y-axis.
    unsigned char *data = stbi_load(FileSystem::getPath("resources/textures/" + filename +".png").c_str(), &width, &height, &nrChannels, 0); //Loads container.jpg and saves data to data.
    if (data) //Error checking
    {
        //Generates the texture using the currently buffered texture, the height, type. width, and data.
        glTexImage2D(GL_TEXTURE_2D, 0, GL_RGBA, width, height, 0, GL_RGBA, GL_UNSIGNED_BYTE, data);
        glGenerateMipmap(GL_TEXTURE_2D); //Automatically creates mipmaps for the tecture
    }
    else //Will occur if no data has been generated
    {
        std::cout << "Failed to load texture" << std::endl;
    }
    stbi_image_free(data); //Frees texture once we're done.
    return texture;
}