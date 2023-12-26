#include <stdio.h>
#include "functions.h"
//#include "types.h"
#include "string.h"

void parse(char* path, object** obj){
    size(path, obj);
    printf("%i", (*obj)->textureCount);
    //(*obj)->vertices = malloc(sizeof(float) * ((*obj)->vertexCount + 1));
    (*obj)->vertices = malloc(sizeof(float) * 1000);
    //(*obj)->textures = malloc(sizeof(float) * ((*obj)->textureCount + 1));
    (*obj)->textures = malloc(sizeof(float) * 1000);
    //(*obj)->normals = malloc(sizeof(float) * ((*obj)->normalCount + 1));
    (*obj)->normals = malloc(sizeof(float) * 1000);
    int vsize = 10, nsize = 10, tsize = 10;
    int v = 0, n = 0, t = 0;
    FILE* file = fopen(path, "r");
    if(file == NULL){
        printf("no file :(");
        fclose(file);
    }
    char buf[100];
    while (fgets(buf, sizeof(buf), file)) {
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
        if(strcmp(temp, "f")){}
        //object name
        if(strcmp(temp, "o")){}
        //group name
        if(strcmp(temp, "g")){}
        //defnes material to be used until another is specified
        if(strcmp(temp, "usemtl")){}
        //smooth shading??
        if(strcmp(temp, "s")){}
        if(strcmp(temp, "mtllib")){}


        //printf("%s", temp);
        memset(buf, 0, sizeof(buf));
        memset(temp, 0, sizeof(temp));
    }
    fclose(file);
}