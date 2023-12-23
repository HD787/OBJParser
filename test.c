#include "parser.h"
#include "stdio.h"
int main(){
    int numVertices = 0, numTextures = 0, numNormals = 0;
    vertex* vertices;
    texture* textures;
    normal* normals;
    parse("largeExample.obj", &vertices, &numVertices, &textures, &numTextures, &normals, &numNormals);
    printf("%d", numVertices);
    printf("%f, %f, %f", vertices[1].x, vertices[1].y, vertices[1].z); 
    for(int i = 0; i < 100; i++){
        printf("%f, %f, %f\n", vertices[i].x, vertices[i].y, vertices[i].z);
    }
}