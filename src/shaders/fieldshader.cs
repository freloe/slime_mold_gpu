#version 440
layout(binding = 0) buffer dcField              { float Field [ ]; };
layout(binding = 1) buffer dcFieldTemp          { float FieldTemp [ ]; };
layout(binding = 2) buffer dcParticleX          { float ParticleX [ ]; };
layout(binding = 3) buffer dcParticleY          { float ParticleY [ ]; };
layout(binding = 5) buffer dcSettings   { float Settings [ ]; };
layout(rgba8,binding=6) uniform writeonly image2D img;

layout(local_size_x = 20, local_size_y = 20, local_size_z = 1) in;

void diffusion(uint idx) {
    FieldTemp[idx] = 0.0f;
    
    for(int i = -1; i < 2; ++i) 
        for(int j = -1; j < 2; ++j) {
            if(!((gl_GlobalInvocationID.y+j) < 0 || (gl_GlobalInvocationID.y+j) >= Settings[3]) && !((gl_GlobalInvocationID.x+i) < 0 || (gl_GlobalInvocationID.x+i) >= Settings[2]))
                FieldTemp[idx] += Settings[5] * Field[(int(gl_GlobalInvocationID.x + i + (gl_GlobalInvocationID.y + j) *Settings[2]))];
        }
}

void decay(uint idx) {
    FieldTemp[idx] *= Settings[6];
}

vec4 color(float t)
{
 float coltab[]={0.5, 0.5, 0.5	,	0.5, 0.5, 0.5	,2.0, 1.0, 0.0	,0.50, 0.20, 0.25};
 vec4 col;
 col.r = coltab[0]+coltab[3]*cos(2*3.1416*(coltab[6]*t+coltab[9]));
 col.g = coltab[1]+coltab[4]*cos(2*3.1416*(coltab[7]*t+coltab[10]));
 col.b = coltab[2]+coltab[5]*cos(2*3.1416*(coltab[8]*t+coltab[11]));
 col.a = 1;
 return col;
}

void main() {
    int idx = int(gl_GlobalInvocationID.x) + int(Settings[2] * gl_GlobalInvocationID.y);

    diffusion(idx);
    decay(idx);


    vec4 col = vec4(0.0f,0.0f,0.0f,1.0f); 
    if(FieldTemp[idx]/255.0f > 0.01)
        col = color(FieldTemp[idx]/255.0f); 
    imageStore(img,ivec2(gl_GlobalInvocationID.xy),col);
}