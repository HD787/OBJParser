#include "parser.h"
#include "stdio.h"

void printBinary(unsigned int num) {
    for (int i = (sizeof(unsigned int) * 8) - 1; i >= 0; i--) {
        putchar((num & (1u << i)) ? '1' : '0');
    }
}

int main(){
    object* obj = malloc(sizeof(object));
    parse("cube.obj", &obj);
    //printf("%f, %f, %f", vertices[1], vertices[1], vertices[1]);
    // printf("%i\n", obj->vertexCount);
    // printf("%i\n", obj->normalCount);
    // printf("%i\n", obj->textureCount);
    // printf("%i\n", obj->faceCount);
    printf("%d, here", obj->flags);
    //printBinary(obj->flags);
    // for(int i = 0; i < obj->vertexCount; i++){
    //     printf("%f\n", obj->vertices[i]);
    // }
    delete(&obj);
} 