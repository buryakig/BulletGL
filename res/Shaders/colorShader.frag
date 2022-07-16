#version 450 core

/////////////// MACROS ///////////////
#define NR_POINT_LIGHTS 1  
#define PI 3.14159265359 


// VARIABLES
struct Material 
{
    sampler2D texture_diffuse;
    sampler2D texture_normal;
    sampler2D texture_height;
    sampler2D texture_specular;
    sampler2D texture_metallic;
    sampler2D texture_ao;
    float shininess;
    vec3 matDiffuseColor;
}; 

struct DirLight
{
    vec3 direction;

    vec3 ambient;
    vec3 diffuse;
    vec3 specular;
};

struct PointLight
{
    vec3 position;

    float constant;
    float linear;
    float quadratic;

    vec3 ambient;
    vec3 diffuse;
    vec3 specular;
};

struct SpotLight
{
    vec3 position;
    vec3 direction;

    float outCutOff;
    float inCutOff;

    float constant;
    float linear;
    float quadratic;

    vec3 ambient;
    vec3 diffuse;
    vec3 specular;
};

uniform sampler2D envMap;

out vec4 FragColor;
 
in vec3 Normal;
in vec3 Tangent;
in vec3 BiTangent;
in vec2 TexCoord;
in vec3 CamPos;
in vec3 FragPos;
in vec3 Color;
in vec3 TangentViewPos;
in vec3 TangentFragPos;

in mat3 TBN;

uniform Material material;

DirLight dirLight;
uniform PointLight pointLights[NR_POINT_LIGHTS];
uniform SpotLight spotLight;

vec3 CalcDirLight(DirLight light, vec3 normal, vec3 viewDir, vec3 diffuseColor, vec3 specularColor);
vec3 CalcPointLight(PointLight light, vec3 normal, vec3 fragPos, vec3 viewDir, vec3 diffuseColor, vec3 specularColor);
vec3 CalcSpotLight(SpotLight light, vec3 normal, vec3 fragPos, vec3 viewDir, vec3 diffuseColor, vec3 specularColor);


float near = 0.1; 
float far  = 1000.0; 

layout(std140, binding = 0) uniform PerFrameData {
 uniform mat4 MVP;
 uniform vec3 cameraPos;
};

float LinearizeDepth(float depth) 
{
    float ndc = depth * 2.0 - 1.0; // back to NDC 
    return (2.0 * near * far) / (far + near - ndc * (far - near));	
}

vec3 GetNormalMapUnPacked(vec2 uv)
{
    vec4 normalMap = vec4(texture(material.texture_normal, uv));
    normalMap.xyz = normalize(normalMap.xyz * 2.0 - 1.0);
    return normalize(TBN * normalMap.xyz);
}

// PBR rendering functions decl
vec3 fresnelShlick(float cosTheta, vec3 F0);
float DistributionGGX(vec3 N, vec3 H, float roughness);
float GeometrySchlickGGXDirect(float NdotX, float roughness);
float GeometrySmith(vec3 N, vec3 V, vec3 L, float roughness);



void main() //////////////////////////////////////////////////////////////////////////////////// MAIN
{
    // Temporary!!!!!!!!!!!
    // Setting our light in shader
    dirLight.direction = normalize(vec3(-1.0, -1.0 , -1.0));
    dirLight.ambient = vec3(0.05, 0.05 , 0.05);
    dirLight.diffuse = vec3(2.95, 2.85 , 2.3);
    dirLight.specular = vec3(0.85, 0.75 , 0.5);
    
    vec3 normalMap = GetNormalMapUnPacked(TexCoord);
    vec4 albedo = texture(material.texture_diffuse, TexCoord);
    float metallic = texture(material.texture_metallic, TexCoord).r;
    float roughness = vec3(texture(material.texture_specular, TexCoord)).r;
    //float specular = 1.0f - roughness;
    
    vec3 viewDir = normalize(cameraPos.xyz - FragPos);
    
    // Calculate reflectance at normal incidence; if dia-electric (like plastic) use F0 
    // of 0.04 and if it's a metal, use the albedo color as F0 (metallic workflow)   
    vec3 F0 = vec3(0.04);
    F0 = mix(F0, albedo.rgb, metallic);

    // Reflectance equation
    vec3 Lo = vec3(0.0);
    {
        vec3 lightDir = -dirLight.direction;
        vec3 halfVec = normalize(lightDir + viewDir);
        
        vec3 radiance = dirLight.diffuse;

        //Cook-Torrance BRDF
        vec3 F = fresnelShlick(max(dot(halfVec, viewDir), 0.0), F0);
        float DF = DistributionGGX(normalMap, halfVec, roughness);
        float G = GeometrySmith(normalMap, viewDir, lightDir, roughness);

        vec3 numerator = DF * G * F;
        float denominator = 4.0f * max(dot(normalMap, viewDir), 0.0) * max(dot(normalMap, lightDir), 0.0) + 0.0001f;
        vec3 specular = numerator / denominator;

        // kS is equal to Fresnel
        vec3 kS = F;
        vec3 kD = vec3(1.0) - kS;
        kD *= 1.0 - metallic;

        // scale light by NdotL
        float NdotL = max(dot(normalMap, lightDir), 0.0);

        // add to outgoing radiance Lo
        Lo += (kD * albedo.rgb / PI + specular) * radiance * NdotL;
    }

    vec3 ambient = vec3(0.02) * albedo.rgb;
    
    vec3 color = ambient + Lo;

    //DEBUG//
    //    vec3 normal = normalize(Normal);
    //    vec3 tangent = normalize(Tangent);
    //    vec3 bitangent = normalize(BiTangent);

    vec3 envColor = texture(envMap, TexCoord).rgb;

    // Directional lighting
    //vec3 result = CalcDirLight(dirLight, normalMap.xyz, viewDir, albedo.rgb, vec3(roughness));
    
    float depth = LinearizeDepth(gl_FragCoord.z) / far;

    FragColor = vec4(color, 1.0);// + vec4(material.matDiffuseColor, 0.0);
}   
//////////////////////////////////////////////////////////////////////////////////// END MAIN

float GeometrySmith(vec3 N, vec3 V, vec3 L, float roughness)
{
    float NdotV = max(dot(N, V), 0.0);
    float NdotL = max(dot(N, L), 0.0);

    float ggx1 = GeometrySchlickGGXDirect(NdotV, roughness);
    float ggx2 = GeometrySchlickGGXDirect(NdotL, roughness);

    return ggx1 * ggx2;
}

float GeometrySchlickGGXDirect(float NdotX, float roughness)
{
    float r = (roughness + 1.0);
    float k = (r*r) / 8.0;

    float num = NdotX;
    float denom = NdotX * (1.0 - k) + k;

    return num / denom;
}

float DistributionGGX(vec3 N, vec3 H, float roughness)
{
    float a = roughness * roughness;
    float a2 = a * a;
    float NdotH  = max(dot(N, H), 0.0);
    float NdotH2 = NdotH * NdotH;

    float num = a2;
    float denom = (NdotH2*(a2 - 1.0) + 1.0);
    denom = PI * denom * denom;

    return num / denom;
}

vec3 fresnelShlick(float cosTheta, vec3 F0)
{
    return F0 + (1.0 - F0) * pow(clamp(1.0 - cosTheta, 0.0, 1.0), 5.0);
}




vec3 CalcDirLight(DirLight light, vec3 normal, vec3 viewDir, vec3 diffuseColor, vec3 specularColor)
{
    vec3 lightDir = -light.direction;
    // diffuse shading
    float diff = max(dot(normal, lightDir), 0.0);
    // specular shading
    vec3 halfwayDir = normalize(lightDir + viewDir);
    float spec = pow(max(dot(normal, halfwayDir), 0.0), 5.0);
    // combine result
    vec3 ambient = light.ambient * diffuseColor;
    vec3 diffuse = light.diffuse * diff * diffuseColor;
    vec3 specular = light.specular * spec * specularColor;
    return ambient + diffuse + specular;
    //return specular;
}

vec3 CalcPointLight(PointLight light, vec3 normal, vec3 fragPos, vec3 viewDir, vec3 diffuseColor, vec3 specularColor)
{
    vec3 lightDir = normalize(light.position - fragPos);
    // diifuse shading
    float diff = max(dot(normal, lightDir), 0.0);
    // specular shading
    vec3 halfwayDir = normalize(lightDir + viewDir);
    float spec = pow(max(dot(normal, halfwayDir), 0.0), material.shininess);
    // attenuation
    float distance = length(light.position - fragPos);
    float attenuation = 1.0 / (light.constant + light.linear * distance + light.quadratic * distance * distance);

    // combine results
    vec3 ambient  = light.ambient  * diffuseColor;
    vec3 diffuse  = light.diffuse  * diff * diffuseColor;
    vec3 specular = light.specular * spec * specularColor;

    return (ambient + diffuse + specular) * attenuation;
}

vec3 CalcSpotLight(SpotLight light, vec3 normal, vec3 fragPos, vec3 viewDir, vec3 diffuseColor, vec3 specularColor)
{
    float theta = dot(viewDir, normalize(-light.direction));
    float intensity = clamp((light.outCutOff - theta) / (light.outCutOff - light.inCutOff), 0.0, 1.0);

    vec3 ambient  = vec3(0.0);
    vec3 diffuse  = vec3(0.0);
    vec3 specular = vec3(0.0);

    if(theta > light.outCutOff)
    {
        vec3 lightDir = normalize(light.position - fragPos);
        float diff = max(dot(normal, lightDir), 0.0);
        // specular shading
        vec3 reflectDir = reflect(-lightDir, normal);
        float spec = pow(max(dot(viewDir, reflectDir), 0.0), material.shininess);
        // attenuation
        float distance = length(light.position - fragPos);
        float attenuation = intensity / (light.constant + light.linear * distance + light.quadratic * distance * distance);

        ambient  = light.ambient  * diffuseColor * attenuation;
        diffuse  = light.diffuse  * diff * diffuseColor * attenuation;
        specular = light.specular * spec * specularColor * attenuation;
    }
    
    return (ambient + diffuse + specular);
}