// input
uniform sampler2DMS screenTexture;
in highp vec2 TexCoords;

// output
out highp vec4 FragColor;

// code

vec4 textureMultisample(sampler2DMS sampler, vec2 uv)
{
    int texSamples = 8;
    ivec2 texCoord = ivec2(TexCoords.x, TexCoords.y);
    vec4 color = vec4(0.0);

    for (int i = 0; i < texSamples; i++) {
        color += texelFetch(sampler, texCoord, i);
    }

    color /= float(texSamples);

    return color;
}

void main()
{
    FragColor = textureMultisample(screenTexture, TexCoords);
}
