#version 460 core

layout(location = 0) in vec2 v_pos;

uniform mat4 model;
uniform mat4 ortho;

uniform vec4 color;
uniform float thicknes;

out Circle
{
	vec2 localPosition;
	vec4 Color;
	float Thickness;
} vs_out;

void main()
{
	vs_out.localPosition = v_pos;
	vs_out.Color = color;
	vs_out.Thickness = thicknes;

	gl_Position = ortho * model * vec4(v_pos, 0.0, 1.0);
}