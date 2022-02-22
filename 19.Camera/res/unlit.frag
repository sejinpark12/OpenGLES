#version 300 es
precision mediump float;

in vec3 vert_color;
in vec2 vert_st;

uniform sampler2D sampler;

layout(location = 0) out vec4 frag_color;

void main() {
	frag_color = texture(sampler, vert_st);
}
