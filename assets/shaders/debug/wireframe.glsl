#version 330 core

#ifdef VERTEX
layout (location = 0) in vec3 aLocalPos;
out vec3 vLocalPosVS;
uniform mat4 uMVP;

void main() {
    gl_Position = uMVP * vec4(aLocalPos, 1.0);
    vLocalPosVS = aLocalPos;
}
#endif

#ifdef GEOMETRY
layout (triangles) in;
layout (triangle_strip, max_vertices = 3) out;

in vec3 vLocalPosVS[];
out vec3 vLocalPos;
out vec3 vBarycentric;

void main() {
    for(int i = 0; i < 3; i++) {
        gl_Position = gl_in[i].gl_Position;
        vLocalPos = vLocalPosVS[i];
        
        // On assigne (1,0,0), (0,1,0), (0,0,1) selon l'index du sommet
        vBarycentric = vec3(0.0);
        vBarycentric[i] = 1.0;
        
        EmitVertex();
    }
    EndPrimitive();
}
#endif

#ifdef FRAGMENT
out vec4 FragColor;
in vec3 vLocalPos;
in vec3 vBarycentric;

uniform float uThickness = 0.02;

void main() {
    float minBary = min(min(vBarycentric.x, vBarycentric.y), vBarycentric.z);
    
    if (minBary > uThickness) {
        discard;
    }

    // --- COULEURS ÉDITEUR ---
    vec3 colorCyan = vec3(0.0, 1.0, 0.8); // Cyan type Unreal/Unity
    
    // ASTUCE : On assombrit légèrement selon la profondeur (Z local)
    // pour donner un effet de volume naturel.
    float shadow = mix(0.5, 1.0, (vLocalPos.z + 1.0) * 0.5);
    
    FragColor = vec4(colorCyan * shadow, 1.0);
}
#endif