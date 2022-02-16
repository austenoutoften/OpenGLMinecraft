#ifndef RENDER_H
#define RENDER_H

#include "opengl.h"
#include "materials.h"
#include "transform.h"

void renderSingleTexture(Shader lightingShader, int texture, int cubeVAO, glm::vec3 displacement, glm::vec3 scale, Material* mat);
void renderTwoTextures(Shader lightingShader, int texture1, int texture2, int cubeVAO, glm::vec3 displacement, glm::vec3 scale, Material* mat);
void renderDoor(Shader doorShader, int doorTexture, int cubeVAO, glm::vec3 displacement, Material* mat);
void renderChest(Shader chestShader, int textures[7], int cubeVAO, glm::vec3 displacement, Material* mat);
void chestBindTextures(Shader chestShader, int textureFront, int textureTop, int textureBottom, int textureSide, int cubeVAO);
void renderInsideChest(Shader chestShader, int texture, int cubeVAO, glm::vec3 displacement, Material* mat);
void renderPig(Shader pigShader, Shader pigBodyShader, int textures[8], int cubeVAO, glm::vec3 displacement, Material* mat);
void pigFeet(Shader pigShader, int textures[8], int cubeVAO, glm::vec3 displacement, Material* mat);
void renderObject(Shader lightingShader, Material* mat);

#endif