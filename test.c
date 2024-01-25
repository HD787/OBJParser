#include "parser.h"
#include "stdio.h"

void printBinary(unsigned int num) {
    for (int i = (sizeof(unsigned int) * 8) - 1; i >= 0; i--) {
        putchar((num & (1u << i)) ? '1' : '0');
    }
}

int main(){
    object* obj = malloc(sizeof(object));
    parse("cube.obj", obj);
    //parse("../copengl/pirate_gold_copy.obj", obj);
    //printf("%f, %f, %f", vertices[1], vertices[1], vertices[1]);

    //printf("\n%i\n", obj->faceElementCount);
    // printf("%i\n", obj->normalCount);
    // printf("%i\n", obj->textureCount);
    // printf("%i\n", obj->faceCount);
    //printf("%d, here", obj->flags);
    //printBinary(obj->flags);

    int test = 0;
    // for(int i = 0; i < obj->faceObjectIndexCount ; i++){
    //     printf("%s", (obj->faceObjectIndices[i]).materialName);
    // }
    
    //printf("\n%f", obj->faces[300]);
    delete(obj);
} 