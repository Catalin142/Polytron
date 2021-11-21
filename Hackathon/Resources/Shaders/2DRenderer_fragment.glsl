#version 460 core
out vec4 FragColor;

in vec2 fsPos;
uniform sampler2D tex;
uniform vec4 color;

void main()
{
	FragColor = texture(tex, fsPos) * color;
}