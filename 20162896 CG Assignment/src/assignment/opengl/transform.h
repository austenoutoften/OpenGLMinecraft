#ifndef TRANS_H
#define TRANS_H
#include "opengl.h"

void modelTransform(Shader lightingShader, glm::vec3 displacement, glm::vec3 scale);
void pigTransform(Shader lightingShader, glm::vec3 displacement, glm::vec3 scale);
void pigFeetTransform(Shader lightingShader, glm::vec3 displacement, glm::vec3 scale, int side);
void topChestAnimate(Shader lightingShader, glm::vec3 displacement, glm::vec3 scale);
void inChestTransform(Shader lightingShader, glm::vec3 displacement, glm::vec3 scale);

#endif