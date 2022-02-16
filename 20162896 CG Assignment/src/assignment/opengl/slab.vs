#version 330 core
layout (location = 0) in vec3 aPos;
layout (location = 1) in vec3 aNormal;
layout (location = 2) in vec2 aTexCoord;

out vec3 FragPos;
out vec3 Normal;
out vec2 texCords;

uniform mat4 model;
uniform mat4 view;
uniform mat4 projection;
uniform int texSizeX;
uniform int texSizeY;
uniform int texSizeZ;

void main()
{
    FragPos = vec3(model * vec4(aPos, 1.0));
    Normal = mat3(transpose(inverse(model))) * aNormal;  
    float xCoord = 1.0f;
    float yCoord = 1.0f;

    // Front and back faces
    if (aNormal.z != 0){ 
        xCoord = xCoord * texSizeX;
        yCoord = yCoord * 0.5;
    }

    //Side faces
    if (aNormal.x != 0){ 
        xCoord = xCoord * texSizeZ;
        yCoord = yCoord * 0.5;        
    }

    //Top and bottom faces
    if (aNormal.y != 0){ 
        xCoord = xCoord * texSizeZ;
        yCoord = yCoord * texSizeX;        
    }
    texCords = vec2(aTexCoord.x * xCoord, aTexCoord.y * yCoord);
    
    gl_Position = projection * view * vec4(FragPos, 1.0);
}