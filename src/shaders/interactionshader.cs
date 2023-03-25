#version 440
layout(binding = 0) buffer dcField  { float Field [ ]; };
layout(binding = 7) buffer dcPos    { float Pos [ ]; };

layout(local_size_x = 20, local_size_y = 20, local_size_z = 1) in;

void main() {

}