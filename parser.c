#include <stdio.h>
#include "functions.h"
#include "types.h"

void parse(char* path, vertex* vertices, normal* normals, texture* textures){
    vertices = malloc(sizeof(vertex) * 10);
    normals = malloc(sizeof(normal) * 10);
    textures = malloc(sizeof(textures) * 10);
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
        if(temp == "v"){
            vertex* temp = makeVertex(buf);
            if(v == vsize){
                vsize *= 2;
                realloc(vertices, vsize);
            }
            vertices[v] = *temp;
            ++v;
        }
        //texture coordinates
        if(temp == "vt"){
            texture* temp = makeTexture(buf);
            if(t == tsize){
                tsize *= 2;
                realloc(textures, tsize);
            }
            textures[t] = *temp;
            ++temp;
        }
        //normals
        if(temp == "vn"){
            normal* temp = makeNormal(buf);
            if(n == nsize){
                nsize *= 2;
                realloc(normals, nsize);
            }
            normals[n] = *temp;
            ++n;
        }
        //face
        if(temp == "f"){}
        //object name
        if(temp == "o"){}
        //group name
        if(temp == "g"){}
        //defnes material to be used until another is specified
        if(temp == "usemtl"){}
        //smooth shading??
        if(temp == "s"){}
        if(temp == "mtllib"){}


        printf("%s", temp);
        //clears buf buffer, same as memset in string.h but wanted to implement it myself
        for(int j=0; j < sizeof(buf); ++j){ buf[j] = 0; }
    }
}



int main(){
    //parse("example.obj");
}