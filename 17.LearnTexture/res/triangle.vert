#version 300 es

layout(location = 0) in vec3 attr_position;
layout(location = 1) in vec2 attr_st;

out vec2 vert_st;

void main() {
    gl_Position = vec4(attr_position, 1.0);
    vert_st = attr_st;
}
