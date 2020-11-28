#version 450 core
in vec3 ourColor;
in vec2 TexCoord;

out vec4 color;

// Texture sampler
uniform sampler2D ourTexture1;
uniform int limiarMeuFiltro;
uniform vec3 novaCorMeuFiltro;


void main()
{
    color = texture(ourTexture1, TexCoord);// * vec4(ourColor, 1.0);

     float mediaPonderada = color.r * 0.2125 + color.g * 0.7154 + color.b * 0.0721;

     // eu sou muito idiota
    // float revMediaR = (mediaPonderada - color.g * 0.7154 - color.b * 0.0721)/0.2125;
    // float revMediaG = (mediaPonderada -color.r * 0.2125 - color.b * 0.0721)/0.7154;
    // float revMediaB = (mediaPonderada -color.r * 0.2125 - color.g * 0.7154)/0.0721;

    //float corR=color.r;
    //float corG=color.g;
   // float corB=color.b;

    color.r = mediaPonderada;
    color.g = mediaPonderada;
    color.b = mediaPonderada;


    float limiarCorrigidoMeuFiltro = limiarMeuFiltro/255.0;

    if(mediaPonderada < limiarCorrigidoMeuFiltro)
    {
    color = vec4(0.0,0.0,0.0,0.9);

    color+= vec4(novaCorMeuFiltro,0.0);
    }
    else
    {
    color = vec4(1.0,1.0,1.0,0.1);
    }
   
}