#version 330 core
in vec3 vWorldPos;
in vec3 vNormal;
in vec2 vTexCoords;

out vec4 FragColor;

uniform sampler2D uTextures[3];  // 0:基础色, 1:金属粗糙度, 2:法线
uniform vec3 uLightPos;

// PBR核心函数（简化版）
vec3 fresnelSchlick(float cosTheta, vec3 F0) {
    return F0 + (1.0 - F0) * pow(1.0 - cosTheta, 5.0);
}

float DistributionGGX(vec3 N, vec3 H, float roughness) {
    float a = roughness * roughness;
    float a2 = a * a;
    float NdotH = max(dot(N, H), 0.0);
    float NdotH2 = NdotH * NdotH;
    float denom = (NdotH2 * (a2 - 1.0) + 1.0);
    return a2 / (3.14159 * denom * denom);
}

float GeometrySchlickGGX(float NdotV, float roughness) {
    float r = (roughness + 1.0);
    float k = (r * r) / 8.0;
    return NdotV / (NdotV * (1.0 - k) + k);
}

float GeometrySmith(vec3 N, vec3 V, vec3 L, float roughness) {
    float NdotV = max(dot(N, V), 0.0);
    float NdotL = max(dot(N, L), 0.0);
    float ggx2 = GeometrySchlickGGX(NdotV, roughness);
    float ggx1 = GeometrySchlickGGX(NdotL, roughness);
    return ggx1 * ggx2;
}

void main() {
    // 采样纹理
    vec3 albedo = pow(texture(uTextures[0], vTexCoords).rgb, vec3(2.2));  // 伽马校正
    float metallic = texture(uTextures[1], vTexCoords).r;
    float roughness = texture(uTextures[1], vTexCoords).g;
    vec3 normal = texture(uTextures[2], vTexCoords).rgb * 2.0 - 1.0;  // 法线贴图解码

    // 计算光照方向
    vec3 N = normalize(normal);
    vec3 V = normalize(-vWorldPos);  // 视角方向
    vec3 L = normalize(uLightPos - vWorldPos);  // 光源方向
    vec3 H = normalize(V + L);  // 半程向量

    // PBR光照计算
    vec3 F0 = mix(vec3(0.04), albedo, metallic);  // 反射率
    vec3 F = fresnelSchlick(max(dot(H, V), 0.0), F0);
    float D = DistributionGGX(N, H, roughness);
    float G = GeometrySmith(N, V, L, roughness);

    vec3 numerator = D * G * F;
    float denominator = 4.0 * max(dot(N, V), 0.0) * max(dot(N, L), 0.0) + 0.0001;
    vec3 specular = numerator / denominator;

    vec3 kS = F;
    vec3 kD = vec3(1.0) - kS;
    kD *= 1.0 - metallic;  // 金属无漫反射

    float NdotL = max(dot(N, L), 0.0);
    vec3 radiance = vec3(3.0);  // 简化光源强度

    vec3 diffuse = albedo / 3.14159;
    vec3 color = (kD * diffuse + specular) * radiance * NdotL;

    // 环境光
    color += albedo * 0.03;
    // 伽马校正输出
    color = color / (color + vec3(1.0));
    color = pow(color, vec3(1.0/2.2));

    FragColor = vec4(color, 1.0);
}