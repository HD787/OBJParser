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
        memset(temp, 0, sizeof(temp));
        memset(buf, 0, sizeof(buf));
    }
    (*obj)->vertexCount *= 3;
    (*obj)->textureCount *= 3;
    (*obj)->normalCount *= 3;
}

void delete(object** obj){
    free((*obj)->vertices);
    free((*obj)->textures);
    free((*obj)->normals);
    free((*obj));
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
//faces are going to represent your triangles (maybe quads??)
//so parse out 3 vertices, then 3 textures, then 3 normals all into one array (maybe 4 of each??) 
//this will be your VBO, make VAOs accordingly
//this parser will be able to handle up to quads, nothing more
void makeFace(char* str, int* f, object** obj){
    int arr[12];
    int index = 0;
    char * endptr;
    str += 2;
    while(*str != '\0'){
        arr[index] = strtol(str, &endptr, 10);
        if(*endptr != '\0'){
            str = endptr + 1;
        }
        else { break; }
    }
    if(index < 9){
        for(int i = 0; i < 9; i += 3){
            obj->faceArray[(*f)++] = obj->vertexArray[arr[i] - 1];
        }
        for(int j = 1; j < 9; j += 3){
            obj->faceArray[(*f)++] = obj->textureArray[arr[j] - 1];
        }
        for(int k = ; k < 9; k += 3){
            obj->faceArray[(*f)++] = obj->normaArray[arr[k] - 1]; 
        }
    }
    int arr1[9];
    int arr2[9]
    if(index > 9){
        //this could easily be made more concise but look at all the typing i did
        //triangle one is made of the first second and third ele
        arr1[0] = arr[0]
        arr1[1] = arr[1]
        arr1[2] = arr[2]
        arr1[3] = arr[3]
        arr1[4] = arr[4]
        arr1[5] = arr[5]
        arr1[6] = arr[6]
        arr1[7] = arr[7]
        arr1[8] = arr[8]

        arr2[0] = arr[0]
        arr2[1] = arr[1]
        arr2[2] = arr[2]
        arr2[3] = arr[6]
        arr2[4] = arr[7]
        arr2[5] = arr[8]
        arr2[6] = arr[9]
        arr2[7] = arr[10]
        arr2[8] = arr[11]
        //arr1
        for(int i = 0; i < 9; i += 3){
            obj->faceArray[(*f)++] = obj->vertexArray[arr1[i] - 1];
        }
        for(int j = 1; j < 9; j += 3){
            obj->faceArray[(*f)++] = obj->textureArray[arr1[j] - 1];
        }
        for(int k = ; k < 9; k += 3){
            obj->faceArray[(*f)++] = obj->normaArray[arr1[k] - 1]; 
        }
        //arr2
        for(int i = 0; i < 9; i += 3){
            obj->faceArray[(*f)++] = obj->vertexArray[arr2[i] - 1];
        }
        for(int j = 1; j < 9; j += 3){
            obj->faceArray[(*f)++] = obj->textureArray[arr2[j] - 1];
        }
        for(int k = ; k < 9; k += 3){
            obj->faceArray[(*f)++] = obj->normaArray[arr2[k] - 1]; 
        }
    }
    //gotta do this for two arrays, consider more concise code plz

}

void insertVals(object* obj, float* arr, int* f){
    
}