#version 330 core

#define NR_POINT_LIGHTS 1  

/////////////// MACROS ///////////////



struct Material 
{
    sampler2D texture_diffuse1;
    sampler2D texture_specular1;
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
in vec3 FragPos;
in vec3 Color;

uniform vec4 viewPos;

uniform Material material;

uniform sampler2D diff;

uniform DirLight dirLight;
uniform PointLight pointLights[NR_POINT_LIGHTS];
uniform SpotLight spotLight;

vec3 CalcDirLight(DirLight light, vec3 normal, vec3 viewDir, vec3 diffuseColor, vec3 specularColor);
vec3 CalcPointLight(PointLight light, vec3 normal, vec3 fragPos, vec3 viewDir, vec3 diffuseColor, vec3 specularColor);
vec3 CalcSpotLight(SpotLight light, vec3 normal, vec3 fragPos, vec3 viewDir, vec3 diffuseColor, vec3 specularColor);


float near = 0.1; 
float far  = 1000.0; 

float LinearizeDepth(float depth) 
{
    float ndc = depth * 2.0 - 1.0; // back to NDC 
    return (2.0 * near * far) / (far + near - ndc * (far - near));	
}

void main()
{
    // properties
    vec3 viewDir = normalize(viewPos.xyz - FragPos);
    vec3 normal = normalize(Normal);
    vec3 tangent = normalize(Tangent);
    vec3 bitangent = normalize(BiTangent);
    vec4 diffuse = vec4(texture(diff, TexCoord));
    vec3 specular = vec3(texture(material.texture_specular1, TexCoord));

    // Directional lighting
    vec3 result = CalcDirLight(dirLight, normal, viewDir, diffuse.rgb, specular);

    float depth = LinearizeDepth(gl_FragCoord.z) / far;

    FragColor = vec4(diffuse.rgb, 1.0);// + vec4(material.matDiffuseColor, 0.0);
}

vec3 CalcDirLight(DirLight light, vec3 normal, vec3 viewDir, vec3 diffuseColor, vec3 specularColor)
{
    vec3 lightDir = normalize(-light.direction);
    // diffuse shading
    float diff = max(dot(normal, lightDir), 0.0);
    // specular shading
    vec3 halfwayDir = normalize(lightDir + viewDir);
    float spec = pow(max(dot(normal, halfwayDir), 0.0), material.shininess);
    // combine result
    vec3 ambient = light.ambient * diffuseColor;
    vec3 diffuse = light.diffuse * diff * diffuseColor;
    vec3 specular = light.ambient * spec * specularColor;
    return ambient + diffuse + specular;
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