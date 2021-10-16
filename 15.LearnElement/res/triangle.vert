#version 300 es

layout(location = 0) in vec3 attr_position;
layout(location = 1) in vec3 attr_color;

out vec3 vert_color;

void main() {
    gl_Position = vec4(attr_position, 1.0);
    vert_color = attr_color;
}
