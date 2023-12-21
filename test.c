#include "parser.h"
#include "stdio.h"
int main(){
    int numVertices = 0, numTextures = 0, numNormals = 0;
    vertex* vertices;
    texture* textures;
    normal* normals;
    parse("example.obj", &vertices, numVertices, &textures, numTextures, &normals, numNormals);
    printf("here");
    printf("%f, %f, %f", vertices[0].x, vertices[0].y, vertices[0].z); 
    // for(int i = 0; i < numVertices; i++){
    //     printf("%f, %f, %f", vertices[i].x, vertices[i].y, vertices[i].z);
    // }
}