#version 330 core
struct Material {
  vec3 ambient;
  vec3 diffuse;
  vec3 specular;
  float shininess;
  sampler2D ambientTexture;
  sampler2D diffuseTexture;
  sampler2D specularTexture;
};
uniform Material material;

struct PointLight {
  vec3 position;

  vec3 ambient;
  vec3 diffuse;
  vec3 specular;

  float constant;
  float linear;
  float quadratic;
};
uniform PointLight pLight;

struct DirLight {
  vec3 direction;

  vec3 ambient;
  vec3 diffuse;
  vec3 specular;
};
uniform DirLight dLight;

struct SpotLight {
  vec3 position;
  vec3 direction;
  float cutOff;
  float extCutOff;

  float constant;
  float linear;
  float quadratic;

  vec3 ambient;
  vec3 diffuse;
  vec3 specular;
};
uniform SpotLight sLight;

out vec4 FragColor;
in vec2 TexCoord;
in vec3 Normal;
in vec3 FragPos;
in vec4 FragPosLightSpace;

uniform vec3 viewPos;
uniform sampler2D shadowMap;

vec3 CalcPointLight(PointLight light, Material m, vec2 texCoord, vec3 fragPos, vec3 normal, vec3 ViewPos, float shadow) {
  vec3 ambient = m.ambient * light.ambient * vec3(texture(m.ambientTexture, texCoord));

  vec3 norm = normalize(normal);
  vec3 lightDir = normalize(light.position - fragPos);
  float diff = max(dot(norm, lightDir), 0.0f);

  vec3 diffuse = (diff * m.diffuse) * light.diffuse * vec3(texture(m.diffuseTexture,texCoord));

  vec3 viewDir = normalize(ViewPos - fragPos);
  vec3 reflectDir = reflect(-lightDir, norm);
  float spec = pow(max(dot(viewDir, reflectDir), 0.0f), m.shininess);
  vec3 specular = (m.specular * spec) * light.specular * vec3(texture(m.specularTexture,texCoord));

  float distance = length(light.position - fragPos);
  float attenuation = 1.0 / (light.constant + light.linear * distance + light.quadratic * (distance * distance));

  // ambient *= attenuation;
  // diffuse *= attenuation;
  // specular *= attenuation;
  
  diffuse *= (1.0f - shadow);
  specular *= (1.0f - shadow);

  return ambient+diffuse+specular;
}

vec3 CalcDirLight(DirLight light, Material m, vec2 texCoord, vec3 fragPos, vec3 normal, vec3 ViewPos) {
  vec3 ambient = light.ambient * m.ambient * vec3(texture(m.ambientTexture, texCoord));

  vec3 norm = normalize(normal);
  vec3 lightDir = normalize(-light.direction);
  float diff = max(dot(norm, lightDir), 0.0f);
  vec3 diffuse = (diff * m.diffuse) * light.diffuse * vec3(texture(m.diffuseTexture, texCoord));

  vec3 viewDir = normalize(ViewPos - fragPos);
  vec3 reflectDir = reflect(lightDir, norm);
  float spec = pow(max(dot(viewDir, reflectDir), 0.0f), m.shininess);
  vec3 specular = (m.specular * spec) * light.specular * vec3(texture(m.specularTexture, texCoord));

  return ambient+diffuse+specular;
}

vec3 CalcSpotLight(SpotLight light, Material m, vec2 texCoord, vec3 fragPos, vec3 normal, vec3 ViewPos) {
  vec3 lightDir = normalize(light.position - fragPos);
  float theta = dot(lightDir, normalize(-light.direction));

  float epsilon = light.cutOff - light.extCutOff;
  float intensity = clamp((theta - light.extCutOff) / epsilon, 0, 1);

  vec3 ambient = light.ambient * m.ambient * vec3(texture(m.ambientTexture, texCoord));

  vec3 norm = normalize(normal);
  float diff = max(dot(norm, light.direction), 0.0f);
  vec3 diffuse = (diff * m.diffuse) * light.diffuse * vec3(texture(m.diffuseTexture, texCoord));

  vec3 viewDir = normalize(ViewPos - fragPos);
  vec3 reflectDir = reflect(light.direction, norm);
  float spec = pow(max(dot(viewDir, reflectDir), 0.0f), m.shininess);
  vec3 specular = (m.specular * spec) * light.specular * vec3(texture(m.specularTexture, texCoord));
  
  float distance = length(light.position - fragPos);
  float attenuation = 1.0 / (light.constant + light.linear * distance + light.quadratic * (distance * distance));

  ambient *= attenuation;
  diffuse *= attenuation;
  specular *= attenuation;

  diffuse *= intensity;
  specular *= intensity;

  return ambient+diffuse+specular;
}

float CalcShadow(vec4 fragPosLightSpace) {
  vec3 projCoords = fragPosLightSpace.xyz / fragPosLightSpace.w;
  projCoords = projCoords * 0.5f + 0.5f; // [-1, 1] -> [0, 1]

  float closestDepth = texture(shadowMap, projCoords.xy).r;
  float currentDepth = projCoords.z;
  float bias = 0.05f;  
  float shadow = currentDepth - bias > closestDepth ? 1.0f : 0.0f;

  return shadow;
}

void main()
{
  float shadow = CalcShadow(FragPosLightSpace);
  vec3 color = CalcPointLight(pLight, material, TexCoord, FragPos, Normal, viewPos, shadow); /* + CalcDirLight(dLight, material, TexCoord, FragPos, Normal, viewPos); + CalcSpotLight(sLight, material, TexCoord, FragPos, Normal, viewPos);*/
  FragColor = vec4(color, 1);
}
