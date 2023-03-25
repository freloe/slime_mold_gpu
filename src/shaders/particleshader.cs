#version 450
layout(binding = 0) buffer dcField              { float Field [ ]; };
layout(binding = 2) buffer dcParticleX          { float ParticleX [ ]; };
layout(binding = 3) buffer dcParticleY          { float ParticleY [ ]; };
layout(binding = 4) buffer dcParticleHeading    { float ParticleHeading [ ]; };
layout(binding = 5) buffer dcSettings   { float Settings [ ]; };

layout(local_size_x = 1024) in;

float rand(vec2 pos) {
    return fract(sin(dot(pos,vec2(12.9898,78.233)))*43758.5453123);
}

float sense(uint idx, float angle) {

    float out_ = 0.0f;

    vec2 curPos = vec2(ParticleX[idx],ParticleY[idx]);
    vec2 prevPos = vec2(ParticleX[idx],ParticleY[idx]);

    vec2 d = vec2(cos(radians(ParticleHeading[idx] + angle)),sin(ParticleHeading[idx] + angle));
    d *= 0.5f;

    for(int k = 0; k < Settings[1]*2; ++k) {
        curPos += d;

        if(curPos.x >= Settings[2])
            curPos.x -= Settings[2] - 0.1;
        if(curPos.y >= Settings[3])
            curPos.y -= Settings[3] - 0.1;
        if(curPos.x < 0)
            curPos.x += Settings[2] - 0.1;
        if(curPos.y < 0) 
            curPos.y += Settings[3] - 0.1;



        if((int(curPos.x)) != (int(prevPos.x)) || (int(curPos.y)) != (int(prevPos.y))) {
            prevPos = curPos;

            out_ += Field[int(curPos.y) * int(Settings[2]) + int(curPos.x)];
        }
    }

    return out_;
}

void rotate(uint idx, vec3 amounts) {
    int biggest = 0;
    int smallest = 0;


    if((amounts.y/amounts.x) > 1.15 && (amounts.y/amounts.z) > 1.15)
        biggest = 1;
    if((amounts.z/amounts.y) > 1.15 && (amounts.z/amounts.x) > 1.15)
        biggest = 2;


    if((amounts.y/amounts.x) < 0.85 && (amounts.y/amounts.z) < 0.85)
        smallest = 1;
    if((amounts.z/amounts.y) < 0.85 && (amounts.z/amounts.x) < 0.85)
        smallest = 2;

    if(biggest == 1) {}
    else if(biggest == 0 && smallest == 2) {
        float dir = (rand(vec2(ParticleX[idx],ParticleY[idx])));
        ParticleHeading[idx] -= Settings[0] * dir;
        if(ParticleHeading[idx] < 0)
            ParticleHeading[idx] += 360;
    }
    else if(biggest == 2 && smallest == 0){
        float dir = (rand(vec2(ParticleX[idx],ParticleY[idx])));
        ParticleHeading[idx] += Settings[0];
        if(ParticleHeading[idx] >= 360)
            ParticleHeading[idx] -= 360;
    }
    else {
        float dir = (rand(vec2(ParticleX[idx],ParticleY[idx])) - 0.5) * 2;
        ParticleHeading[idx] += Settings[0] * dir;
        if(ParticleHeading[idx] < 0)
            ParticleHeading[idx] += 360;
        if(ParticleHeading[idx] >= 360)
            ParticleHeading[idx] -= 360;
    }
}

void move(uint idx) {
    vec2 d = vec2(cos(radians(ParticleHeading[idx])),sin(ParticleHeading[idx]));
    d *= Settings[4];

    ParticleX[idx] += d.x;
    ParticleY[idx] += d.y;


    if(ParticleX[idx] >= Settings[2])
        ParticleX[idx] -= Settings[2] - 0.1;
    if(ParticleY[idx] >= Settings[3])
        ParticleY[idx] -= Settings[3] - 0.1;
    if(ParticleX[idx] < 0)
        ParticleX[idx] += Settings[2] - 0.1;
    if(ParticleY[idx] < 0) 
        ParticleY[idx] += Settings[3] - 0.1;
}

void deposit(uint idx) {
    Field[int(ParticleX[idx]) + int(ParticleY[idx]) * int(Settings[2])] += 10.0f;

    if(Field[int(ParticleX[idx]) + int(ParticleY[idx]) * int(Settings[2])] > 255.0f)
        Field[int(ParticleX[idx]) + int(ParticleY[idx]) * int(Settings[2])] = 255.0f;
}

void main(){
    int idx = int(gl_GlobalInvocationID.x);

    vec3 amounts;

    amounts.x = sense(idx,-Settings[0]);
    amounts.y = sense(idx,0.0f);
    amounts.z = sense(idx,Settings[0]);

    rotate(idx,amounts);

    move(idx);

    deposit(idx);
}