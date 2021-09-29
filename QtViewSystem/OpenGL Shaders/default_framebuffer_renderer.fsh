// input
uniform sampler2D screenTexture;
in highp vec2 TexCoords;

// output
out highp vec4 FragColor;

// code
void main()
{
    FragColor = texture(screenTexture, TexCoords);
}
