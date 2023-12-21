#include <stdio.h>
#include "functions.h"
//#include "types.h"
#include "string.h"

void parse(char* path, vertex* vertices, texture* textures, normal* normals){
    vertices = malloc(sizeof(vertex) * 10);
    textures = malloc(sizeof(texture) * 10);
    normals = malloc(sizeof(normal) * 10);
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
            if(buf[i] == ' ' | buf[i] == '#'){
                break;
            }
            temp[i] = buf[i];
        }
        //vertex
        if(strcmp(temp, "v")){
            vertex* temp = makeVertex(buf);
            if(v == vsize){
                vsize *= 2;
                vertices = realloc(vertices, vsize);
            }
            vertices[v] = *temp;
            ++v;
        }
        //texture coordinates
        if(strcmp(temp, "vt")){
            texture* temp = makeTexture(buf);
            if(t == tsize){
                tsize *= 2;
                textures = realloc(textures, tsize);
            }
            textures[t] = *temp;
            ++temp;
        }
        //normals vn
        if(strcmp(temp, "vn")){
            normal* temp = makeNormal(buf);
            if(n == nsize){
                nsize *= 2;
                normals = realloc(normals, nsize);
            }
            normals[n] = *temp;
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


        printf("%s", temp);
        //clears buf buffer, same as memset in string.h but wanted to implement it myself
        for(int j=0; j < sizeof(buf); ++j){ buf[j] = 0; }
    }
}



// int main(){
//     vertex* vertices;
//     texture* textures;
//     normal* normals;
//     parse("example.obj", vertices, textures, normals);
// }