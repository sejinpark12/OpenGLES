#version 300 es

out vec3 vert_color;

struct Vertex {
    vec3 position;
    vec3 color;
};

void main() {
    Vertex vertices[3];
    vertices[0] = Vertex(vec3(-0.5, -0.5, 0.0), vec3(1.0, 0.0, 0.0));
    vertices[1] = Vertex(vec3( 0.5, -0.5, 0.0), vec3(0.0, 1.0, 0.0));
    vertices[2] = Vertex(vec3( 0.0,  0.5, 0.0), vec3(0.0, 0.0, 1.0));

    gl_Position = vec4(vertices[gl_VertexID].position, 1.0);
    vert_color = vertices[gl_VertexID].color;
}
