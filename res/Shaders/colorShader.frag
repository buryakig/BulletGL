#version 450 core

#define NR_POINT_LIGHTS 1  

/////////////// MACROS ///////////////

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

vec2 GetParallacMappingUVOffset(vec2 uv)
{
    vec3 tangentViewDir = normalize(TangentViewPos - TangentFragPos);

    const float heightScale = 0.1;

    const float numLayers = 32.0;

    float layerDepth = 1.0 / numLayers;
    float currentLayerDepth = 0.0;
    
    vec2 p = tangentViewDir.xy * heightScale;
    vec2 uvstep = p / numLayers;

    vec2 currentUVs = uv;
    float currentDepthMapValue  = 1.0 - texture(material.texture_height, uv).r;

    while(currentLayerDepth < currentDepthMapValue )
    {
        currentUVs -= uvstep;
        currentDepthMapValue  = 1.0 - texture(material.texture_height, uv).r;
        currentLayerDepth += layerDepth;
    }

    return currentUVs;
}

void main()
{
    #if 0
        vec2 texCoordsParallaxed = GetParallacMappingUVOffset(TexCoord);
    #else
        vec2 texCoordsParallaxed = TexCoord;
    #endif
    vec4 diffuse = vec4(texture(material.texture_diffuse, texCoordsParallaxed));
    if(diffuse.a < 0.5) discard;

    dirLight.direction = normalize(vec3(-1.0, -1.0 , -1.0));
    dirLight.ambient = vec3(0.5, 0.5 , 0.3);
    dirLight.diffuse = vec3(0.95, 0.85 , 0.6);
    dirLight.specular = vec3(0.85, 0.75 , 0.5);

    // properties
    vec3 viewDir = normalize(cameraPos.xyz - FragPos);
    //vec3 normal = normalize(Normal);
    vec3 tangent = normalize(Tangent);
    vec3 bitangent = normalize(BiTangent);
    float specular = vec3(texture(material.texture_specular, texCoordsParallaxed)).r;
    vec3 normalMap = GetNormalMapUnPacked(texCoordsParallaxed);


    // Directional lighting
    vec3 result = CalcDirLight(dirLight, normalMap.xyz, viewDir, diffuse.rgb, vec3(1.0 - specular));
    
    float depth = LinearizeDepth(gl_FragCoord.z) / far;

    FragColor = vec4(result.rgb, 1.0);// + vec4(material.matDiffuseColor, 0.0);
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