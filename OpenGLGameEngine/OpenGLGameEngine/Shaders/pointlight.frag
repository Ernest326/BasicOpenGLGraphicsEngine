#version 330 core
out vec4 FragColor;

struct Material { 
    float shininess;
	vec3 color;
}; 

struct Light {

	vec3 position;

	vec3 diffuse;
	vec3 specular;
    vec3 ambient;

	float constant;
	float linear;
	float quadratic;

	float brightness;
	float distance;

};

in vec3 FragPos;  
in vec3 Normal; 
  
uniform vec3 viewPos;
uniform Material material;
uniform Light light;

void main()
{


    // ambient
    vec3 ambient = light.ambient;
  	
    // diffuse 
    vec3 norm = normalize(Normal);
    vec3 lightDir = normalize(light.position - FragPos);
    float diff = max(dot(norm, lightDir), 0.0);
    vec3 diffuse = light.diffuse * diff;
    
    // specular
    vec3 viewDir = normalize(viewPos - FragPos);
    vec3 reflectDir = reflect(-lightDir, norm);  
    float spec = pow(max(dot(viewDir, reflectDir), 0.0), material.shininess);
    vec3 specular = light.specular * spec;  

	// attenuation
	float distance = length(light.position - FragPos);
	float attenuation = 1.0 / (light.constant + light.linear * distance + light.quadratic * (distance * distance));

	ambient *= attenuation;
	diffuse *= attenuation;
	specular *= attenuation;

    vec3 result = (ambient + diffuse + specular) * material.color * light.brightness;
    FragColor = vec4(result, 1.0);
} 