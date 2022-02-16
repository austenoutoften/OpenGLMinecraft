#version 330 core
out vec4 FragColor;

in vec3 Normal;  
in vec3 FragPos;  
in vec2 texCords;
in vec3 normalVec;

struct Material {
    vec3 ambient;
    vec3 diffuse;
    vec3 specular;
    float shininess;
}; 
  
struct Light {
    vec3 position;

    vec3 ambient;
    vec3 diffuse;
    vec3 specular;

    float constant;
    float linear;
    float quadratic;
};
  
uniform vec3 viewPos;
uniform Material material;
uniform Light light;
uniform int setBrightness;

// texture samplers
uniform sampler2D bodyFront;
uniform sampler2D bodyBack;
uniform sampler2D bodySide;

void main()
{
    vec4 color;
    if (normalVec.z == 1.0f){ 
        color = texture(bodyFront, texCords);
    }
    else if (normalVec.z == -1.0f){
        color = texture(bodyBack, texCords);
    }
    else{
        color = texture(bodySide, texCords);        
    }

    if(color.a < 0.1)
        discard;

    if (setBrightness == 1) {        
        // ambient
        vec3 ambient = light.ambient * material.ambient;
        
        // diffuse 
        vec3 norm = normalize(Normal);
        vec3 lightDir = normalize(light.position - FragPos);
        float diff = max(dot(norm, lightDir), 0.0);
        vec3 diffuse = light.diffuse * (diff * material.diffuse);
        
        // specular
        vec3 viewDir = normalize(viewPos - FragPos);
        vec3 reflectDir = reflect(-lightDir, norm);  
        float spec = pow(max(dot(viewDir, reflectDir), 0.0), material.shininess);
        vec3 specular = light.specular * (spec * material.specular);  
        
        // attenuation
        float distance    = length(light.position - FragPos);
        float attenuation = 1.0 / (light.constant + light.linear * distance + light.quadratic * (distance * distance));    

        ambient  *= attenuation;  
        diffuse   *= attenuation;
        specular *= attenuation;   

        vec3 result = ambient + diffuse + specular;
        FragColor = vec4(result, 1.0) * color;
    }
    else{
        FragColor = color;
    }
} 