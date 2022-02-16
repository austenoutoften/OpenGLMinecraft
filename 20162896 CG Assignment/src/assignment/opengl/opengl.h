#ifndef OPENGL_H
#define OPENGL_H

#include <glad/glad.h> //Must be included before GLFW
#include <GLFW/glfw3.h>
#include <stb_image.h>

#include <glm/glm.hpp> //Same math things in GLM
#include <glm/gtc/matrix_transform.hpp>
#include <glm/gtc/type_ptr.hpp>

#include <learnopengl/filesystem.h>
#include <learnopengl/shader_m.h> //Learnopengl shader compiler
#include <learnopengl/camera.h>

#include <string>
#include <iostream>
#include <cmath>
#include <unistd.h>

#include "verticies.h"
#include "materials.h"
#include "render.h"
#include "transform.h"

//Function declariations
void framebuffer_size_callback(GLFWwindow* window, int width, int height);
void mouse_callback(GLFWwindow* window, double xpos, double ypos);
void scroll_callback(GLFWwindow* window, double xoffset, double yoffset);
void processInput(GLFWwindow *window);
unsigned int loadTexture(std::string filename);

extern unsigned int SCR_WIDTH;
extern unsigned int SCR_HEIGHT;

//Camera
extern Camera camera;
extern bool firstMouse;
extern float lastX;
extern float lastY;

//Timing stuff
extern float deltaTime;
extern float lastFrame;

// lighting
extern glm::vec3 lightPos;

//Settings
extern float lightRadius;
extern int perspectiveProj;
extern int followCamera ;
extern int sceneBrightness;
extern float chestAnimationFrame;

extern int perspectiveProjHeld ;
extern int followCameraHeld;
extern int sceneBrightnessHeld;
extern int chestAnimationHeld;

#endif