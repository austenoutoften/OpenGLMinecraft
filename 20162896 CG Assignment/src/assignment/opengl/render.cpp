#include "render.h"

void renderSingleTexture(Shader lightingShader, int texture, int cubeVAO, glm::vec3 displacement, glm::vec3 scale, Material* mat){
    renderObject(lightingShader, mat);
    modelTransform(lightingShader, displacement, scale);

    //BIND TEXTURES
    glActiveTexture(GL_TEXTURE0); // activate the texture unit first before binding texture
    glBindTexture(GL_TEXTURE_2D, texture);
    lightingShader.setInt("texture1", 0); // or with shader class

    //Render the cubes
    glBindVertexArray(cubeVAO);
    glDrawArrays(GL_TRIANGLES, 0, 36);
}

void renderTwoTextures(Shader lightingShader, int topTexture, int sideTexture, int cubeVAO, glm::vec3 displacement, glm::vec3 scale, Material* mat){

    renderObject(lightingShader, mat);
    modelTransform(lightingShader, displacement, scale);

    //BIND TEXTURES
    glActiveTexture(GL_TEXTURE0); // activate the texture unit first before binding texture
    glBindTexture(GL_TEXTURE_2D, topTexture);
    //BIND TEXTURES
    glActiveTexture(GL_TEXTURE1); // activate the texture unit first before binding texture
    glBindTexture(GL_TEXTURE_2D, sideTexture);

    lightingShader.setInt("topTexture", 0); // or with shader class
    lightingShader.setInt("sideTexture", 1); // or with shader class
    //Render the cubes
    glBindVertexArray(cubeVAO);
    glDrawArrays(GL_TRIANGLES, 0, 36);
}

void renderDoor(Shader doorShader, int doorTexture, int cubeVAO, glm::vec3 displacement, Material* mat){
    renderObject(doorShader, mat);
    modelTransform(doorShader, displacement, glm::vec3(1.0f,2.0f,3.0/16.0));

    //BIND TEXTURES
    glActiveTexture(GL_TEXTURE0); // activate the texture unit first before binding texture
    glBindTexture(GL_TEXTURE_2D, doorTexture);
    doorShader.setInt("texture", 0); // or with shader class

    //Render the cubes
    glBindVertexArray(cubeVAO);
    glDrawArrays(GL_TRIANGLES, 0, 36);
}

void renderChest(Shader chestShader, int textures[7], int cubeVAO, glm::vec3 displacement, Material* mat){
    //TOP CHEST
    renderObject(chestShader, mat);

    modelTransform(chestShader,displacement, glm::vec3(1.0f,0.6f,1.0f));
    chestBindTextures(chestShader, textures[1], textures[2], textures[0], textures[3], cubeVAO);

    renderObject(chestShader, mat);
    if (chestAnimationFrame == 0){
        modelTransform(chestShader, glm::vec3(0.0f,0.6f, 0.0f) + displacement, glm::vec3(1.0f,0.4f,1.0f));
    }
    else{
        topChestAnimate(chestShader, glm::vec3(0.0f,0.6f, 0.0f) + displacement, glm::vec3(1.0f,0.4f,1.0f));
        chestAnimationFrame+=1*deltaTime;
    }
    chestBindTextures(chestShader, textures[4], textures[0], textures[5], textures[6], cubeVAO);
}

void chestBindTextures(Shader chestShader, int textureFront, int textureTop, int textureBottom, int textureSide, int cubeVAO){
    glActiveTexture(GL_TEXTURE0); // activate the texture unit first before binding texture
    glBindTexture(GL_TEXTURE_2D, textureFront);
    chestShader.setInt("chestFront", 0); // or with shader class

    glActiveTexture(GL_TEXTURE1); // activate the texture unit first before binding texture
    glBindTexture(GL_TEXTURE_2D, textureTop);
    chestShader.setInt("chestTop", 1); // or with shader class

    glActiveTexture(GL_TEXTURE2); // activate the texture unit first before binding texture
    glBindTexture(GL_TEXTURE_2D, textureBottom);
    chestShader.setInt("chestBottom", 2); // or with shader class

    glActiveTexture(GL_TEXTURE3); // activate the texture unit first before binding texture
    glBindTexture(GL_TEXTURE_2D, textureSide);
    chestShader.setInt("chestOther", 3); // or with shader class

    glBindVertexArray(cubeVAO);
    glDrawArrays(GL_TRIANGLES, 0, 36);    
}
void renderInsideChest(Shader shader, int texture, int cubeVAO, glm::vec3 displacement, Material* mat){
    renderObject(shader, mat);
    inChestTransform(shader, displacement + glm::vec3(0.4f,-0.4f,0.5f), glm::vec3(0.2f,0.2f,0.2f));

    //BIND TEXTURES
    glActiveTexture(GL_TEXTURE0); // activate the texture unit first before binding texture
    glBindTexture(GL_TEXTURE_2D, texture);
    shader.setInt("texture1", 0); // or with shader class

    //Render the cubes
    glBindVertexArray(cubeVAO);
    glDrawArrays(GL_TRIANGLES, 0, 36);
}

void renderPig(Shader pigShader, Shader pigBodyShader, int textures[8], int cubeVAO, glm::vec3 displacement, Material* mat){
    //HEAD
    renderObject(pigShader, mat);
    pigTransform(pigShader, glm::vec3(0.0f,-0.25f, 0.0f) + displacement, glm::vec3(0.5f,0.5f,0.5f));
    glActiveTexture(GL_TEXTURE0); // activate the texture unit first before binding texture
    glBindTexture(GL_TEXTURE_2D, textures[0]);
    pigShader.setInt("frontTexture", 0); // or with shader class

    glActiveTexture(GL_TEXTURE1); // activate the texture unit first before binding texture
    glBindTexture(GL_TEXTURE_2D, textures[1]);
    pigShader.setInt("sideTexture", 1); // or with shader class

    glActiveTexture(GL_TEXTURE2); // activate the texture unit first before binding texture
    glBindTexture(GL_TEXTURE_2D, textures[2]);
    pigShader.setInt("otherTexture", 2); // or with shader class

    glBindVertexArray(cubeVAO);
    glDrawArrays(GL_TRIANGLES, 0, 36);

    //BODY
    renderObject(pigBodyShader, mat);
    pigTransform(pigBodyShader, glm::vec3(0.0f,-0.45f,-1.0f) + displacement, glm::vec3(0.5f,0.5f,1.0f));
    pigBodyShader.use();
    glActiveTexture(GL_TEXTURE3); // activate the texture unit first before binding texture
    glBindTexture(GL_TEXTURE_2D, textures[3]);
    pigBodyShader.setInt("bodyFront", 3); // or with shader class

    glActiveTexture(GL_TEXTURE4); // activate the texture unit first before binding texture
    glBindTexture(GL_TEXTURE_2D, textures[4]);
    pigBodyShader.setInt("bodyBack", 4); // or with shader class

    glActiveTexture(GL_TEXTURE5); // activate the texture unit first before binding texture
    glBindTexture(GL_TEXTURE_2D, textures[5]);
    pigBodyShader.setInt("bodySide", 5); // or with shader class

    glBindVertexArray(cubeVAO);
    glDrawArrays(GL_TRIANGLES, 0, 36);

    //FEET
    pigFeet(pigShader, textures, cubeVAO, displacement, mat);
}

void pigFeet(Shader pigShader, int textures[8], int cubeVAO, glm::vec3 displacement, Material* mat){
    glm::vec3 feetCordindates[] = {glm::vec3(0.35f, -0.7f, -0.2f), glm::vec3(-0.05f, -0.7f, -0.2f), glm::vec3(0.35f, -0.7f, -1.0f), glm::vec3(-0.05f, -0.7f, -1.0f)};
    pigShader.use();
    glActiveTexture(GL_TEXTURE6); // activate the texture unit first before binding texture
    glBindTexture(GL_TEXTURE_2D, textures[6]);
    pigShader.setInt("frontTexture", 6); // or with shader class

    glActiveTexture(GL_TEXTURE7); // activate the texture unit first before binding texture
    glBindTexture(GL_TEXTURE_2D, textures[7]);
    pigShader.setInt("sideTexture", 7); // or with shader class
    pigShader.setInt("otherTexture", 7); // or with shader class

    for (int i = 0; i < 4; i++){
        renderObject(pigShader, mat);
        pigFeetTransform(pigShader, feetCordindates[i] + displacement, glm::vec3(0.25f,0.25f,0.25f), i);
        glBindVertexArray(cubeVAO);
        glDrawArrays(GL_TRIANGLES, 0, 36);
    }
}

//Sets lighting, material properties and projection properties for every rendered object.
void renderObject(Shader lightingShader, Material* mat){
    //Activate Shader
    lightingShader.use();
    lightingShader.setInt("setBrightness", sceneBrightness);
    lightingShader.setVec3("material.ambient", glm::vec3(mat->matambient[0],mat->matambient[1],mat->matambient[2]));
    lightingShader.setVec3("material.diffuse", glm::vec3(mat->matdiffuse[0],mat->matdiffuse[1],mat->matdiffuse[2]));
    lightingShader.setVec3("material.specular", glm::vec3(mat->matspecular[0],mat->matspecular[1],mat->matspecular[2]));
    lightingShader.setFloat("material.shininess", mat->shininess);
    if (followCamera){
        lightPos = camera.Position;
    }
    lightingShader.setVec3("light.position", lightPos);
    lightingShader.setVec3("viewPos", camera.Position);

    // light properties
    glm::vec3 lightColor;
    lightColor.x = 1.0f;
    lightColor.y = 1.0f;
    lightColor.z = 1.0f;
    glm::vec3 diffuseColor = lightColor   * glm::vec3(0.8f); // decrease the influence
    glm::vec3 ambientColor = diffuseColor * glm::vec3(0.2); // low influence
    
    lightingShader.setVec3("light.ambient", ambientColor);
    lightingShader.setVec3("light.diffuse", diffuseColor);
    lightingShader.setVec3("light.specular", 1.0f, 1.0f, 1.0f);

    //Sets attenuation distance to 100. Can be increased / decreased with lightRadius variable
    lightingShader.setFloat("light.constant",  1.0f);
    lightingShader.setFloat("light.linear",    0.045f * lightRadius);
    lightingShader.setFloat("light.quadratic", 0.0075f * pow(lightRadius,2));	  

    //PROJECTION 
    glm::mat4 projection;
    if (perspectiveProj){ //Perspective projection
        projection = glm::perspective(glm::radians(camera.Zoom), (float)SCR_WIDTH / (float)SCR_HEIGHT, 0.1f, 100.0f);
    }
    else{ //Orthographic projection
        projection = glm::ortho(-30.0f, 30.0f, -30.0f, 30.0f, -1000.0f, 1000.0f);
    }
    lightingShader.setMat4("projection", projection);

    //Camera / view transformation
    glm::mat4 view = camera.GetViewMatrix();
    lightingShader.setMat4("view", view);
}