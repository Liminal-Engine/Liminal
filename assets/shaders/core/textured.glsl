#version 330 core

#ifdef VERTEX
layout (location = 0) in vec3 aLocalPos;
layout(location = 1) in vec2 aUV;
layout(location = 2) in vec3 aNormal;

uniform mat4 uMVP;

out vec2 vUV;

void main() {
    gl_Position = uMVP * vec4(aLocalPos, 1.0);
    vUV = aUV;
}
#endif

#ifdef FRAGMENT
in vec2 vUV;

uniform vec3 uColor = vec3(1.0);
uniform sampler2D uTexture;

out vec4 FragColor;

void main() {
    // FragColor = texture(uTexture, vUV) * vec4(uColor, 1.0);
    FragColor = vec4(uColor, 1.0);
}
#endif