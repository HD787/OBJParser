#include "parser.h"
#include "stdio.h"
int main(){
    object* obj = malloc(sizeof(object));
    parse("cube.obj", &obj);
    //printf("%f, %f, %f", vertices[1], vertices[1], vertices[1]);
    printf("%i\n", obj->vertexCount);
    printf("%i\n", obj->normalCount);
    printf("%i\n", obj->textureCount);
    printf("%i", obj->faceCount);
    // for(int i = 0; i < obj->vertexCount; i++){
    //     printf("%f\n", obj->vertices[i]);
    // }
    delete(&obj);
} 