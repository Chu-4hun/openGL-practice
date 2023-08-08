#shader vertex
#version 330 core
layout(location = 0) in vec4 position;
layout(location = 1) in vec3 vertex_colour;

out vec3 colour;

void main(){
    colour = vertex_colour;
    gl_Position = position;
}

#shader fragment
#version 330 core
in vec3 colour;
out vec4 frag_colour;

void main(){
    frag_colour = vec4(colour, 1.0);
}