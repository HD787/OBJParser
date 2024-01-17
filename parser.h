#include <stdio.h>
#include "functions.h"
//#include "types.h"
#include "string.h"
void parse(char* path, object* obj){
    setFlags(path, obj);
    size(path, obj);
    // printf("%i\n", obj->faceCount);
    // printf("%i", obj->faceElementCount);
    obj->vertices = malloc(sizeof(float) * obj->vertexCount * obj->vertexElementCount);
    obj->textures = malloc(sizeof(float) * obj->textureCount * obj->textureElementCount);
    obj->normals = malloc(sizeof(float) * obj->normalCount * obj->normalElementCount);
    obj->faces = malloc(sizeof(float) * obj->faceCount * obj->faceElementCount);
    //obj->faces = malloc(sizeof(float) * 1000);

    int v = 0, n = 0, t = 0, f = 0;
    FILE* file = fopen(path, "r");
    if(file == NULL){
        printf("no file :(");
        fclose(file);
        return;
    }
    char buf[100];
    while(fgets(buf, sizeof(buf), file)) {
        char temp[10];
        for(int i = 0; i < 10; ++i){
            if(buf[i] == ' ' || buf[i] == '#'){
                break;
            }
            temp[i] = buf[i];
        }
        //vertex
        if(strcmp(temp, "v") == 0){
            makeVertex(buf, &v, obj);
        }
        //texture coordinates
        if(strcmp(temp, "vt") == 0){
            makeTexture(buf, &t, obj);
        }
        //normals vn
        if(strcmp(temp, "vn") == 0){
            makeNormal(buf, &n, obj);
        }
        //face
        if(strcmp(temp, "f") == 0){
            //printf(" %i ", test++);
            makeFace(buf, &f, obj);
        }
        //object name
        if(strcmp(temp, "o")){}

        //group name
        if(strcmp(temp, "g")){}

        //defines material to be used until another is specified
        if(strcmp(temp, "usemtl")){}

        //smooth shading??
        if(strcmp(temp, "s")){}

        if(strcmp(temp, "mtllib")){}
        //printf("%s\n", buf);
        memset(buf, 0, sizeof(buf));
        memset(temp, 0, sizeof(temp));
    }
    fclose(file);
}