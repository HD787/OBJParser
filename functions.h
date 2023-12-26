#include "types.h"
#include "stdlib.h"
#include "stdio.h"


void size(char* path, object** obj){
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
            *object->vertexCount++;
        }
        if(strcmp(temp, "vt") == 0){
            *object->textureCount++
        }
        if(strcmp(temp, "vn") == 0){
            *object->normalCount++
        }
    }
}

void makeVertex(char* str, int* v, object** obj){
    char * endptr;
    str += 2; 
    while(*str != '\0'){
        (*obj)->vertices[v] = strtof(str, &endptr);
        *v++;
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
        (*obj)->textures[t] = strtof(str, &endptr);
        *v++;
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
        (*obj)->normals[n] = strtof(str, &endptr);
        *v++;
        if(*endptr != '\0'){
            str = endptr + 1;
        }
        else{
            break;
        }
    }
}