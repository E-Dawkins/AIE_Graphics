#version 410

in vec4 vPosition;
in vec3 vNormal;

out vec4 FragColor;

uniform vec3 CameraPosition;

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
    vec3 L = normalize(LightDirection);

    // Calculate the negative light direction (Lambert Term)
    float lambertTerm = max(0, min(1, dot(N, -L)));

    // Calculate the view vector ...
    vec3 V = normalize(CameraPosition - vPosition.xyz);

    // ... and the reflection vector
    vec3 R = reflect(L, N);

    // Calculate the specular term
    float specularTerm = pow(max(0, dot(R, V)), Ns);
    
    // Calculate the properties of each color type
    vec3 ambient = AmbientColor * Ka;
    vec3 diffuse = LightColor * Kd * lambertTerm;
    vec3 specular = LightColor * Ks * specularTerm;

    FragColor = vec4(ambient + diffuse + specular, 1);
}