#version 460 core
layout (location = 0) in vec2 v_pos;

uniform mat4 ortho;

void main()
{
    gl_Position = ortho * vec4(v_pos, 0.0f, 1.0f);
}