#version 300 es

layout(location = 0) in vec3 attr_position;
layout(location = 1) in vec2 attr_st;

uniform mat4 model;
uniform mat4 view;
uniform mat4 projection;

out vec2 vert_st;

void main() {
    gl_Position = projection * view * model * vec4(attr_position, 1.0);
    vert_st = attr_st;
}
