#version 450 core
in vec3 ourColor;
in vec2 TexCoord;

out vec4 color;

// Texture sampler
uniform sampler2D ourTexture1;
uniform int limiar;


void main()
{
    color = texture(ourTexture1, TexCoord);// * vec4(ourColor, 1.0);

     float mediaPonderada = color.r * 0.2125 + color.g * 0.7154 + color.b * 0.0721;

    color.r = mediaPonderada;
    color.g = mediaPonderada;
    color.b = mediaPonderada;

    float limiarCorrigido = limiar/255.0;

    if(mediaPonderada < limiarCorrigido)
    {
    color = vec4(0.0,0.0,0.0,color.a);
    }
    else
    {
    color = vec4(1.0,1.0,1.0,color.a);
    }
   
}