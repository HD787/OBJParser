#include "parser.h"
#include "stdio.h"
int main(){
    object* obj = malloc(sizeof(object));
    parse("largeExample.obj", &obj);
    //printf("%f, %f, %f", vertices[1], vertices[1], vertices[1]);
    printf("\n%i", obj->vertexCount);
    // for(int i = 0; i < 10; i++){
    //     printf("%f\n", obj->vertices[i]);
    // }
}