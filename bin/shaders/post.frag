#version 410

in vec2 vTexCoord;

uniform sampler2D colorTarget;
uniform int postProcessTarget;
uniform int windowWidth;
uniform int windowHeight;
uniform float time;

out vec4 FragColor;

vec4 Default(vec2 _texCoord)
{
    return texture(colorTarget, _texCoord);
}

vec4 BoxBlur(vec2 _texCoord)
{
    vec2 texel = 1.0f / textureSize(colorTarget, 0);
    
    vec4 color = texture(colorTarget, _texCoord);
    color += texture(colorTarget, _texCoord + texel * vec2(-1,  1));
    color += texture(colorTarget, _texCoord + texel * vec2(-1,  0));
    color += texture(colorTarget, _texCoord + texel * vec2(-1, -1));
    
    color += texture(colorTarget, _texCoord + texel * vec2( 0,  1));
    color += texture(colorTarget, _texCoord + texel * vec2( 0, -1));
    
    color += texture(colorTarget, _texCoord + texel * vec2( 1,  1));
    color += texture(colorTarget, _texCoord + texel * vec2( 1,  0));
    color += texture(colorTarget, _texCoord + texel * vec2( 1, -1));
    
    return color / 9;
}

vec4 Distort(vec2 _texCoord)
{
    vec2 mid = vec2(0.5f);
    float distanceFromCenter = distance(_texCoord, mid);
    vec2 normalizeCoord = normalize(_texCoord - mid);
    float bias = distanceFromCenter + sin(distanceFromCenter * 15) * 0.05;
    vec2 newCoord = mid + bias * normalizeCoord;
    
    return texture(colorTarget, newCoord);
}

vec4 EdgeDetection(vec2 _texCoord)
{
    float w = 1.0f / windowWidth;
    float h = 1.0f / windowHeight;
    
    vec4 k[9];
    
    k[0] = texture(colorTarget, _texCoord + vec2(-w, -h));
    k[1] = texture(colorTarget, _texCoord + vec2( 0, -h));
    k[2] = texture(colorTarget, _texCoord + vec2( w, -h));
    k[3] = texture(colorTarget, _texCoord + vec2(-w,  0));
    k[4] = texture(colorTarget, _texCoord);
    k[5] = texture(colorTarget, _texCoord + vec2( w,  0));
    k[6] = texture(colorTarget, _texCoord + vec2(-w,  h));
    k[7] = texture(colorTarget, _texCoord + vec2( 0,  h));
    k[8] = texture(colorTarget, _texCoord + vec2( w,  h));
    
    vec4 sobelEdgeH = k[2] + (2.0f * k[5]) + k[8] - (k[0] + (2.0f * k[3]) + k[6]);
    vec4 sobelEdgeV = k[0] + (2.0f * k[1]) + k[2] - (k[6] + (2.0f * k[7]) + k[8]);
    
    vec4 sobel = sqrt((sobelEdgeH * sobelEdgeH) + (sobelEdgeV * sobelEdgeV));
    
    return vec4(1.0f - sobel.rgb, 1.0f);
}

vec4 Sepia(vec2 _texCoord)
{
    vec4 origColor = texture(colorTarget, _texCoord);
    
    float newR = origColor.r * 0.393 + origColor.g * 0.769 + origColor.b * 0.189;
    float newG = origColor.r * 0.349 + origColor.g * 0.686 + origColor.b * 0.168;
    float newB = origColor.r * 0.272 + origColor.g * 0.534 + origColor.b * 0.131;
    
    return vec4(newR, newG, newB, 1);
}

vec4 Scanlines(vec2 _texCoord)
{
    vec4 color = texture(colorTarget, _texCoord);

    float lineCount = windowHeight * 1.3f;
    
    float scaledY = (_texCoord.y + time * 0.1f);
    vec2 s1 = vec2(sin(scaledY * lineCount), cos(scaledY * lineCount));
    vec4 scanLines = vec4(s1.x, s1.y, s1.x, 1);
    
    color += color * scanLines * 0.3f;
    color += color * sin(110.0f * time) * 0.02f;
    
    return color;
}

vec4 Grayscale(vec2 _texCoord)
{
    vec4 origColor = texture(colorTarget, _texCoord);
    
    vec3 grayColor = vec3(0.299 * origColor.r, 0.587 * origColor.g, 0.114 * origColor.b);
    
    float gray = grayColor.r + grayColor.g + grayColor.b;

    return vec4(gray, gray, gray, 1);
}

vec4 Invert(vec2 _texCoord)
{
    return vec4(1 - texture(colorTarget, _texCoord).rgb, 1);
}

vec4 Pixelizer(vec2 _texCoord)
{
    return vec4(1);
}

vec4 Posterization(vec2 _texCoord)
{
    return vec4(1);
}

vec4 DistanceFog(vec2 _texCoord)
{
    return vec4(1);
}

vec4 DepthOfField(vec2 _texCoord)
{
    return vec4(1);
}

void main()
{
    // This will calculate the texel size
    vec2 texSize = textureSize(colorTarget, 0);
    vec2 texelSize = 1.0f / texSize;
    
    // Then we will adjust the coordinate
    vec2 scale = (texSize - texelSize) / texSize;
    vec2 texCoord = vTexCoord / scale + texelSize * 0.5f;
    
    switch(postProcessTarget)
    {
        default: // Default
        {
            // Output post process effect here
            FragColor = Default(texCoord);
            break;
        }
        case 0: // Box Blur
        {
            FragColor = BoxBlur(texCoord);
            break;
        }
        case 1: // Distort
        {
            FragColor = Distort(texCoord);
            break;
        }
        case 2: // Edge Detection
        {
            FragColor = EdgeDetection(texCoord);
            break;
        }
        case 3: // Sepia
        {
            FragColor = Sepia(texCoord);
            break;
        }
        case 4: // Scanlines
        {
            FragColor = Scanlines(texCoord);
            break;
        }
        case 5: // Grayscale
        {
            FragColor = Grayscale(texCoord);
            break;
        }
        case 6: // Invert
        {
            FragColor = Invert(texCoord);
            break;
        }
        case 7: // Pixelizer
        {
            FragColor = Pixelizer(texCoord);
            break;
        }
        case 8: // Posterization
        {
            FragColor = Posterization(texCoord);
            break;
        }
        case 9: // Distance Fog
        {
            FragColor = DistanceFog(texCoord);
            break;
        }
        case 10: // Depth of Field
        {
            FragColor = DepthOfField(texCoord);
            break;
        }
    }
}