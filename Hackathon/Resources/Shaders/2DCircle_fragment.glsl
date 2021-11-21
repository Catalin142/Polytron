#version 460 core

out vec4 FragColor;

in Circle
{
	vec2 localPosition;
	vec4 Color;
	float Thickness;
} fs_in;

void main()
{
    float distance = 1.0 - length(fs_in.localPosition);
    float circle = smoothstep(0.0, 0.005, distance);
    circle *= smoothstep(fs_in.Thickness + 0.005, fs_in.Thickness, distance);

	if (circle == 0.0)
		discard;

    FragColor = fs_in.Color;
	FragColor.a *= circle;
}