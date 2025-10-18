#version 330 core
out vec4 FragColor;

in vec2 TexCoord;

uniform sampler2D spriteTexture;
uniform vec4 spriteColor;

void main() {
    FragColor = texture(spriteTexture, TexCoord) * spriteColor;
}
