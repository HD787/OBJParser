#include "types.h"
#include "stdlib.h"
#include "stdio.h"
#include <string.h>


void size(char* path, object** obj){
    (*obj)->vertexCount = 0;
    (*obj)->textureCount = 0;
    (*obj)->normalCount = 0;
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
        if(strcmp(temp, "v") == 0){
            (*obj)->vertexCount++;
        }
        if(strcmp(temp, "vt") == 0){
            (*obj)->textureCount++;
        }
        if(strcmp(temp, "vn") == 0){
            (*obj)->normalCount++;
        }
    }
    (*obj)->vertexCount *= 3;
    (*obj)->textureCount *= 3;
    (*obj)->normalCount *= 3;

}

void makeVertex(char* str, int* v, object** obj){
    char * endptr;
    str += 2; 
    while(*str != '\0'){
        (*obj)->vertices[*v] = strtof(str, &endptr);
        (*v)++;
        if(*endptr != '\0'){
            str = endptr + 1;
        }
        else{
            break;
        }
    }
}

void makeTexture(char* str, int* t, object** obj){
    char * endptr;
    str += 3; 
    while(*str != '\0'){
        (*obj)->textures[*t] = strtof(str, &endptr);
        (*t)++;
        if(*endptr != '\0'){
            str = endptr + 1;
        }
        else{
            break;
        }
    }
}

void makeNormal(char* str, int* n, object** obj){
   char * endptr;
    str += 3; 
    while(*str != '\0'){
        (*obj)->normals[*n] = strtof(str, &endptr);
        (*n)++;
        if(*endptr != '\0'){
            str = endptr + 1;
        }
        else{
            break;
        }
    }
}