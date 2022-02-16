#include "transform.h"

//Translates and scales an object.
void modelTransform(Shader lightingShader, glm::vec3 displacement, glm::vec3 scale){
    // world transformation
    glm::mat4 model = glm::mat4(1.0f);
    //model = glm::rotate(model, (float)glfwGetTime() * glm::radians(50.0f), glm::vec3(0.5f, 1.0f, 0.0f));

    model = glm::translate(model, glm::vec3(-0.5,-0.5,-0.5));
    model = glm::translate(model, displacement);
    model = glm::scale(model, scale);
    model = glm::translate(model, glm::vec3(0.5,0.5,0.5));   

    lightingShader.setInt("texSizeX", scale.x);
    lightingShader.setInt("texSizeY", scale.y);
    lightingShader.setInt("texSizeZ", scale.z);
    lightingShader.setMat4("model", model);
}

//A function which transforms the pig to walk around the tree
void pigTransform(Shader lightingShader, glm::vec3 displacement, glm::vec3 scale){
    // world transformation
    glm::mat4 model = glm::mat4(1.0f);

    model = glm::translate(model, glm::vec3(-0.5f,-0.5f,-0.5f));
    model = glm::translate(model, glm::vec3(-5.0f, 0.0f, 0.0f));
    model = glm::rotate(model, (float)glfwGetTime()/2 * glm::radians(50.0f), glm::vec3(0.0f, 1.0f, 0.0f));
    model = glm::translate(model, displacement);
    model = glm::scale(model, scale);
    model = glm::translate(model, glm::vec3(0.5,0.5,0.5));   

    lightingShader.setInt("texSizeX", scale.x);
    lightingShader.setInt("texSizeY", scale.y);
    lightingShader.setInt("texSizeZ", scale.z);
    lightingShader.setMat4("model", model);
}

//Identical to the above, but adds an extra rotation to give the illusion of the pig's feet moving
void pigFeetTransform(Shader lightingShader, glm::vec3 displacement, glm::vec3 scale, int side){
   // world transformation
    glm::mat4 model = glm::mat4(1.0f);

    model = glm::translate(model, glm::vec3(-0.5f,-0.5f,-0.5f));
    model = glm::translate(model, glm::vec3(-5.0f, 0.0f, 0.0f));
    model = glm::rotate(model, (float)glfwGetTime()/2 * glm::radians(50.0f), glm::vec3(0.0f, 1.0f, 0.0f));
    model = glm::translate(model, displacement);
    model = glm::scale(model, scale);
    if (side % 2 == 1)
        model = glm::rotate(model, glm::sin((float)glfwGetTime()*4) * glm::radians(20.0f), glm::vec3(1.0f, 0.0f, 0.0f));
    else 
        model = glm::rotate(model, glm::sin((float)glfwGetTime()*4) * glm::radians(-20.0f), glm::vec3(1.0f, 0.0f, 0.0f));
    model = glm::translate(model, glm::vec3(0.5,0.5,0.5));   

    lightingShader.setInt("texSizeX", scale.x);
    lightingShader.setInt("texSizeY", scale.y);
    lightingShader.setInt("texSizeZ", scale.z);
    lightingShader.setMat4("model", model);
}

void topChestAnimate(Shader lightingShader, glm::vec3 displacement, glm::vec3 scale){
    // world transformation
    glm::mat4 model = glm::mat4(1.0f);

    float f;
    if (chestAnimationFrame > 5.0)
        f = 5.0;
    else   
        f = chestAnimationFrame;

    model = glm::translate(model, glm::vec3(-0.5,-0.5,-0.5));
    model = glm::translate(model, displacement);
    model = glm::rotate(model, (f/5.0f) * glm::radians(-90.0f), glm::vec3(0.1f, 0.0f, 0.0f));
    model = glm::scale(model, scale);
    model = glm::translate(model, glm::vec3(0.5,0.5,0.5));   

    lightingShader.setInt("texSizeX", scale.x);
    lightingShader.setInt("texSizeY", scale.y);
    lightingShader.setInt("texSizeZ", scale.z);
    lightingShader.setMat4("model", model);    
}

void inChestTransform(Shader lightingShader, glm::vec3 displacement, glm::vec3 scale){
    // world transformation
    glm::mat4 model = glm::mat4(1.0f);

    model = glm::translate(model, glm::vec3(-0.5,-0.5,-0.5));
    model = glm::translate(model, glm::vec3(0.0f, abs(glm::sin((float)glfwGetTime())/2), 0.0f));   
    model = glm::translate(model, displacement);
    model = glm::scale(model, scale);
    model = glm::translate(model, glm::vec3(0.5,0.5,0.5));   
    model = glm::rotate(model, (float)glfwGetTime() * glm::radians(50.0f), glm::vec3(0.0f, 1.0f, 0.0f));

    lightingShader.setInt("texSizeX", scale.x);
    lightingShader.setInt("texSizeY", scale.y);
    lightingShader.setInt("texSizeZ", scale.z);
    lightingShader.setMat4("model", model);    
}