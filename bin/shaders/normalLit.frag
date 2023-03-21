#version 410

in vec4 vPosition;
in vec3 vNormal;
in vec2 vTexCoord;
in vec3 vTangent;
in vec3 vBiTangent;

out vec4 FragColor;

uniform vec3 CameraPosition;
uniform sampler2D diffuseTexture;
uniform sampler2D specularTexture;
uniform sampler2D normalTexture;

// Model Data
uniform vec3 Ka; // Ambient color -> base color
uniform vec3 Kd; // Diffuse color -> color between light and dark
uniform vec3 Ks; // Specular color -> highlight color
uniform float Ns; // Specular power -> how fast the highlight falls off

// Light Data
uniform vec3 AmbientColor;
uniform vec3 LightColor;
uniform vec3 LightDirection;

void main()
{
    // Set the normal and light direction
    vec3 N = normalize(vNormal);
    vec3 T = normalize(vTangent);
    vec3 B = normalize(vBiTangent);
    vec3 L = normalize(LightDirection);

    mat3 TBN = mat3(T, B, N);

    // Get the diffuse, specular and normal maps at the texture coordinate
    vec3 texDiffuse = texture(diffuseTexture, vTexCoord).rgb;
    vec3 texSpecular = texture(specularTexture, vTexCoord).rgb;
    vec3 texNormal = texture(normalTexture, vTexCoord).rgb;

    N = TBN * (texNormal * 2 - 1);

    // Calculate the negative light direction (Lambert Term)
    float lambertTerm = max(0, min(1, dot(N, -L)));

    // Calculate the view vector ...
    vec3 V = normalize(CameraPosition - vPosition.xyz);

    // ... and the reflection vector
    vec3 R = reflect(L, N);

    // Calculate the specular term
    float specularTerm = pow(max(0, dot(R, V)), Ns);
    
    // Calculate the properties of each color type
    vec3 ambient = AmbientColor * Ka * texDiffuse;
    vec3 diffuse = LightColor * Kd * texDiffuse * lambertTerm;
    vec3 specular = LightColor * Ks * texSpecular * specularTerm;

    FragColor = vec4(ambient + diffuse + specular, 1);
}