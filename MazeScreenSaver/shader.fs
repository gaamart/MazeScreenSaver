#version 330 core
in vec2 textureCoordinate;
out vec4 fragColor;

uniform sampler2D textureUnit;

void main()
{
	fragColor = texture(textureUnit, textureCoordinate);
}
