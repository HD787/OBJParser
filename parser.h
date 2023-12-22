#include <stdio.h>
#include "functions.h"
//#include "types.h"
#include "string.h"

void parse(char* path, vertex** vertices, int* numVertices, texture** textures, int* numTextures, normal** normals, int* numNormals){
    *vertices = malloc(sizeof(vertex) * 10);
    *textures = malloc(sizeof(texture) * 10);
    *normals = malloc(sizeof(normal) * 10);
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
            vertex* vval = makeVertex(buf);
            if(v == vsize){
                vsize *= 2;
                *vertices = realloc(*vertices, sizeof(vertex) * vsize);
            }
            (*vertices)[v] = *vval;
            ++*numVertices;
            ++v;
        }
        //texture coordinates
        if(strcmp(temp, "vt") == 0){
            texture* tval = makeTexture(buf);
            if(t == tsize){
                tsize *= 2;
                *textures = realloc(*textures, sizeof(texture) * tsize);
            }
            (*textures)[t] = *tval;
            ++*numTextures;
            ++t;
        }
        //normals vn
        if(strcmp(temp, "vn") == 0){
            normal* nval = makeNormal(buf);
            if(n == nsize){
                
                nsize *= 2;
                *normals = realloc(*normals, sizeof(normal) * nsize);
            }
            (*normals)[n] = *nval;
            ++*numNormals;
            ++n;
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
    *vertices = realloc(*vertices, *numVertices * sizeof(vertex));
    *textures = realloc(*textures, *numTextures * sizeof(texture));
    *normals = realloc(*normals, *numNormals * sizeof(normal));
    fclose(file);
}