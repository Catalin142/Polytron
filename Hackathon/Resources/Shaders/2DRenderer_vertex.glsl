#version 460 core
layout (location = 0) in vec2 v_pos;
layout (location = 1) in vec2 v_VS;

out vec2 fsPos;

uniform mat4 ortho;
uniform mat4 model;

void main()
{
	fsPos = v_VS;
	gl_Position = ortho * model * vec4(v_pos / 2.0f, 0.0, 1.0);
}