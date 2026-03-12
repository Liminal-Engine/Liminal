#version 330 core

#ifdef VERTEX
layout (location = 0) in vec3 aLocalPos;

uniform mat4 uMVP;

void main() {
    gl_Position = uMVP * vec4(aLocalPos, 1.0);
}
#endif

#ifdef FRAGMENT
out vec4 FragColor;

uniform vec3 uColor = vec3(1.0);

void main() {
    FragColor = vec4(uColor, 1.0);
}
#endif