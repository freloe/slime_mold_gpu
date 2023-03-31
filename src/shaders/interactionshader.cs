#version 440
layout(binding = 0) buffer dcField    { float Field [ ]; };
layout(binding = 5) buffer dcSettings { float Settings[ ]; };
layout(binding = 7) buffer dcMouse      { int Mouse [ ]; };

//Mouse[0] = x, Mouse[1] = y, Mouse[2] = amount, Mouse[3] = button, Mouse[4] = radius

layout(local_size_x = 20, local_size_y = 20, local_size_z = 1) in;

void clearRadius(float x, float y, float radius) {
    if(sqrt((x-Mouse[0])*(x-Mouse[0])+(y-Mouse[1])*(y-Mouse[1])) < radius){
        Field[int(x)+int(Settings[2]*y)] = Mouse[2] * (Mouse[3]-1);
    }
}

void main() {
    float x = gl_GlobalInvocationID.x;
    float y = gl_GlobalInvocationID.y;

    clearRadius(x,y,Mouse[4]);
}