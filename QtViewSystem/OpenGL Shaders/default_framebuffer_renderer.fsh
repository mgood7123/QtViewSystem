// input
uniform sampler2D ourTexture;
in highp vec2 TexCoord;

// output
out highp vec4 FragColor;

// code
void main() {
    FragColor = texture(ourTexture, TexCoord);
}
