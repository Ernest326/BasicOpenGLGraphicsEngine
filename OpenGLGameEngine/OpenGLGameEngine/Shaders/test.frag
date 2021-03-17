#version 330 core
out vec4 FragColor;

struct Material { 
    float roughness;
	float metallic;
	float ao;
	vec3 albedo;
};

in vec3 FragPos;  
in vec3 Normal; 

uniform vec3 WorldPos;

uniform vec3 lightPositions[4];
uniform vec3 lightColors[4];

uniform Material material;

uniform vec3 cameraPos;

float PI = 3.14159265359;

vec3 fresnelSchlick(float cosTheta, vec3 F0) 
{
	return F0 + (1 - F0) * pow(1 - cosTheta, 5.0);
}

float DistributionGGX(vec3 N, vec3 H, float a)
{
	float a2 = a*a;
	float NdotH = max(dot(N, H), 0.0);
	float NdotH2 = NdotH*NdotH;

	float nom = a2;
	float denom = (NdotH2 * (a2 - 1.0) + 1.0);
	denom = PI * denom * denom;

	return nom / denom;
}

float GeometrySchlickGGX(float NdotV, float k)
{
	float nom = NdotV;
	float denom = NdotV * (1.0 - k) + k;

	return nom / denom;
}

float GeometrySmith(vec3 N, vec3 V, vec3 L, float k)
{
	float NdotV = max(dot(N, V), 0.0);
	float NdotL = max(dot(N, L), 0.0);
	float ggx1 = GeometrySchlickGGX(NdotV, k);
	float ggx2 = GeometrySchlickGGX(NdotL, k);

	return ggx1 * ggx2;
}

void main()
{

	vec3 N = normalize(Normal);
    vec3 V = normalize(cameraPos - WorldPos);

	vec3 F0 = vec3(0.04);
	F0 = mix(F0, material.albedo, material.metallic);

	vec3 Lo = vec3(0.0);
	
	for(int i = 0; i < 4; i++) {
	
		vec3 L = normalize(lightPositions[i] - WorldPos);
        vec3 H = normalize(V + L);
        float distance    = length(lightPositions[i] - WorldPos);
        float attenuation = 1.0 / (distance * distance);
        vec3 radiance     = lightColors[i] * attenuation;        
        
        // cook-torrance brdf
        float NDF = DistributionGGX(N, H, material.roughness);        
        float G   = GeometrySmith(N, V, L, material.roughness);      
        vec3 F    = fresnelSchlick(max(dot(H, V), 0.0), F0);       
        
        vec3 kS = F;
        vec3 kD = vec3(1.0) - kS;
        kD *= 1.0 - material.metallic;	  
        
        vec3 numerator    = NDF * G * F;
        float denominator = 4.0 * max(dot(N, V), 0.0) * max(dot(N, L), 0.0);
        vec3 specular     = numerator / max(denominator, 0.001);  
            
        // add to outgoing radiance Lo
        float NdotL = max(dot(N, L), 0.0);                
        Lo += (kD * material.albedo / PI + specular) * radiance * NdotL;
	
	}

	vec3 ambient = vec3(0.03) * material.albedo * material.ao;
	vec3 color = ambient + Lo;

	color = color / (color + vec3(1.0f));
	color = pow(color, vec3(1.0/2.2));

    FragColor = vec4(color, 1.0);
} 