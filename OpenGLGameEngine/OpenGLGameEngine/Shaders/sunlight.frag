#version 330 core
out vec4 FragColor;

struct Material { 
    float shininess;
}; 

struct Light {

    vec3 direction;

	vec3 diffuse;
	vec3 specular;

    vec3 ambient;

};

in vec3 FragPos;  
in vec3 Normal; 
  
uniform vec3 viewPos;
uniform Material material;
uniform Light light;

void main()
{
	vec3 color = vec3(0.8, 0.8, 0.8);

    // ambient
    vec3 ambient = light.ambient * color;
  	
    // diffuse 
    vec3 norm = normalize(Normal);
    vec3 lightDir = normalize(-light.direction);
    float diff = max(dot(norm, lightDir), 0.0);
    vec3 diffuse = light.diffuse * diff * color;  
    
    // specular
    vec3 viewDir = normalize(viewPos - FragPos);
    vec3 reflectDir = reflect(-lightDir, norm);  
    float spec = pow(max(dot(viewDir, reflectDir), 0.0), material.shininess);
    vec3 specular = light.specular * spec * color.rgb;  
        
    vec3 result = ambient + diffuse + specular;
    FragColor = vec4(result, 1.0);
} 