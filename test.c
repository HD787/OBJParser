#include "parser.h"
#include "stdio.h"
int main(){
    object* obj = malloc(sizeof(object));
    parse("example.obj", &obj);
    //printf("%d", obj->vertexCount);
    //printf("%f, %f, %f", vertices[1], vertices[1], vertices[1]); 
    // for(int i = 0; i < 100; i++){
    //     printf("%f\n", obj->vertices[i]);
    // }
}