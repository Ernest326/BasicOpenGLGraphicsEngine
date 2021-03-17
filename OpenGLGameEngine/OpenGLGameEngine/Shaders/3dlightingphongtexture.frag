#version 330 core
out vec4 FragColor;

in vec3 Normal;  
in vec3 FragPos; 

in vec2 TexCoord;
  
uniform vec3 lightPos; 
uniform vec3 lightColor;
uniform vec3 viewPos;

uniform sampler2D texture1;

void main()
{
    // ambient
    float ambientStrength = 0.1;
    vec3 ambient = ambientStrength * lightColor;

	//Normal
    vec3 normal = normalize(Normal);

	//Directions
    vec3 lightDir = normalize(lightPos - FragPos);
	vec3 viewDir = normalize(viewPos - FragPos);
	vec3 reflectDir = reflect(-lightDir, normal);

	//Diffuse
    float diff = max(dot(lightDir, normal), 0.0);
    vec3 diffuse = diff * lightColor;
          
	//Specular  
	float specularStrength = 0.5;

	//float spec = pow(max(dot(normal, halfwayDir), 0.0), 32);
	float spec = pow(max(dot(viewDir, reflectDir), 0.0), 8);
	vec3 specular = specularStrength * spec * lightColor; 

    vec3 result = ambient + diffuse + specular;
    FragColor = vec4(result, 1.0) * texture(texture1, TexCoord);
} 