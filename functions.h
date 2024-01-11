#include "types.h"
#include "stdlib.h"
#include "stdio.h"
#include <string.h>

#define TEXTURES (1 << 0)
#define NORMALS (1 << 1)


void size(char* path, object** obj){
    (*obj)->vertexCount = 0;
    (*obj)->textureCount = 0;
    (*obj)->normalCount = 0;
    (*obj)->faceCount = 0;
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
            if(buf[i] == ' ' || buf[i] == '#')
                break;
            temp[i] = buf[i];
        }
        if(strcmp(temp, "v") == 0)
            (*obj)->vertexCount++;

        if(strcmp(temp, "vt") == 0)
            (*obj)->textureCount++;

        if(strcmp(temp, "vn") == 0)
            (*obj)->normalCount++;

        if(strcmp(temp, "f") == 0){
            int prev = 0;
            int count = 0;
            for(int i = 2; i < 100; i++){
                if(buf[i] != ' '){
                    prev = 0;
                    continue;
                }
                if(buf[i] == ' ' && prev == 0){
                    ++count;
                    prev = 1;
                }
                if(buf[i] == ' ' && prev == 1) 
                    break;
            }
            if(count == 4)
                (*obj)->faceCount += 2;
            else 
                (*obj)->faceCount++;
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
    free((*obj)->faces);
    free((*obj));
}

void makeVertex(char* str, int* v, object** obj){
    char * endptr;
    str += 2; 
    while(*str != '\0'){
        float val;
        (*obj)->vertices[*v] = val = strtof(str, &endptr);
        //printf(" %f ", val);
        (*v)++;
        if(*endptr != '\0')
            str = endptr + 1;
        else break;
    }
}

void makeTexture(char* str, int* t, object** obj){
    char * endptr;
    str += 3; 
    while(*str != '\0'){
        (*obj)->textures[*t] = strtof(str, &endptr);
        (*t)++;
        if(*endptr != '\0')
            str = endptr + 1;
        else break;
    }
}

void makeNormal(char* str, int* n, object** obj){
    char * endptr;
    str += 3; 
    while(*str != '\0'){
        (*obj)->normals[*n] = strtof(str, &endptr);
        (*n)++;
        if(*endptr != '\0') 
            str = endptr + 1;
        else break;
    }
}


void makeQuad(char* str, int* f, object** obj){
    if((*obj)->flags == 0){}
    if((*obj)->flags == 1){}
    if((*obj)->flags == 2){}
    if((*obj)->flags == 3){}
}

void makeTri(char* str, int* f, object** obj){
    //no normals, no textures
    if((*obj)->flags == 0){
        int arr[3];
        int index = 0;
        str += 2;
        char * endptr;
        while(*str != '\0'){
            unsigned int val;
            val = strtoul(str, &endptr, 10);
            if(val == 0){ 
                ;
            }
            else{
               arr[index] = val;
               index++; 
            }
            if(*endptr != '\0'){
                str = endptr + 1;
            } else break;
        }
        for(int i = 0; i < 3; i++){
            (*obj)->faces[(*f)++] = (*obj)->vertices[arr[i] - 1];
            //printf("%c", arr[i]);
        }
    }
    //textures only
    if((*obj)->flags == 1){
        int arr[6];
        int index = 0;
        str += 2;
        char * endptr;
        while(*str != '\0'){
            unsigned int val;
            val = strtoul(str, &endptr, 10);
            if(val == 0){ 
                ;
            }
            else{
               arr[index] = val;
               index++; 
            }
            if(*endptr != '\0'){
                str = endptr + 1;
            } else break;
        }
        for(int i = 0; i < 6; i++){
            (*obj)->faces[(*f)++] = (*obj)->vertices[arr[i] - 1];
            //printf("%c", arr[i]);
        }
    }
    //normals only
    if((*obj)->flags == 2){
        unsigned long arr[6];
        int index = 0;
        str += 2;
        char * endptr;
        while(*str != '\0'){
            unsigned int val;
            val = strtoul(str, &endptr, 10);
            //printf("%i", val);
            if(val == 0){ 
                ;
            }
            else{
               arr[index] = val;
               index++; 
            }
            if(*endptr != '\0'){
                str = endptr + 1;
                if(*str == '/'){
                    str++;
                }
                //printf("%c\n", *endptr);
            } else break;
        }
        for(int i = 0; i < 6; i+=2){
            (*obj)->faces[(*f)++] = (*obj)->vertices[arr[i] - 1];
            (*obj)->faces[(*f)++] = (*obj)->normals[arr[i + 1] - 1];
            //printf(" %i\n ", i);
        }
    } 
    //normals and textures
    if((*obj)->flags == 3){
        int arr[9];
        int index = 0;
        str += 2;
        char * endptr;
        while(*str != '\0'){
            unsigned int val;
            val = strtoul(str, &endptr, 10);
            if(val == 0){ 
                ;
            }
            else{
               arr[index] = val;
               index++; 
            }
            if(*endptr != '\0'){
                str = endptr + 1;
                printf("%c\n", *endptr);
            } else break;
        }
        for(int i = 0; i < 9; i++){
            (*obj)->faces[(*f)++] = (*obj)->vertices[arr[i] - 1];
            printf("%c", arr[i]);
        }
    }
}
// void makeFace(char* str, int* f, object** obj){
//     int arr[12];
//     int index = 0;
//     int space = 0;
//     char * endptr;
//     str += 2;
//     while(*str != '\0'){
//         int val;
//         val = strtoul(str, &endptr, 10);
//         if(val == 0){
//             ;
//         }

//         else{
//             arr[index] = val;
//             index++;
//         }
//         //printf("%li\n", strtol(str, &endptr, 10));
//         if(*endptr != '\0'){
//             str = endptr + 1;
//             //printf("%c\n", *endptr);
//         }
//         else break; 
//     }
//     printf(" %i spaces", space);
//     if(index < 9){
//         for(int i = 0; i < 9; i += 3){
//             //(*obj)->faces[(*f)++] = (*obj)->vertices[arr[i] - 1];
//             //printf("%i\n", arr[i] - 1);
//         }
//         for(int j = 1; j < 9; j += 3){
//             //(*obj)->faces[(*f)++] = (*obj)->textures[arr[j] - 1];
//             //printf("%f\n", (*obj)->textures[arr[j] - 1]);
//         }
//         for(int k = 2; k < 9; k += 3){
//             //(*obj)->faces[(*f)++] = (*obj)->normals[arr[k] - 1]; 
//         }
//     }
//     int arr1[9];
//     int arr2[9];
//     if(index > 9){
//         //this could easily be made more concise but look at all the typing i did
//         //triangle one is made of the first second and third elements
//         //triangle two is make for first third and fourth
//         arr1[0] = arr[0];
//         arr1[1] = arr[1];
//         arr1[2] = arr[2];
//         arr1[3] = arr[3];
//         arr1[4] = arr[4];
//         arr1[5] = arr[5];
//         arr1[6] = arr[6];
//         arr1[7] = arr[7];
//         arr1[8] = arr[8];

//         arr2[0] = arr[0];
//         arr2[1] = arr[1];
//         arr2[2] = arr[2];
//         arr2[3] = arr[6];
//         arr2[4] = arr[7];
//         arr2[5] = arr[8];
//         arr2[6] = arr[9];
//         arr2[7] = arr[10];
//         arr2[8] = arr[11];
//         for(int i = 0; i < 9; i += 3){
//             //(*obj)->faces[(*f)++] = (*obj)->vertices[arr1[i] - 1];
//         }
//         for(int j = 1; j < 9; j += 3){
//             //(*obj)->faces[(*f)++] = (*obj)->textures[arr1[j] - 1];
//         }
//         for(int k = 2; k < 9; k += 3){
//             //(*obj)->faces[(*f)++] = (*obj)->normals[arr1[k] - 1]; 
//         }
//         //arr2
//         for(int i = 0; i < 9; i += 3){
//             //(*obj)->faces[(*f)++] = (*obj)->vertices[arr2[i] - 1];
//         }
//         for(int j = 1; j < 9; j += 3){
//             //(*obj)->faces[(*f)++] = (*obj)->textures[arr2[j] - 1];
//         }
//         for(int k = 2; k < 9; k += 3){
//             //(*obj)->faces[(*f)++] = (*obj)->normals[arr2[k] - 1]; 
//         }
//     }
// }
void makeFace(char* str, int* f, object** obj){
    int faceCount = 0;
    for(int i = 2; i < 100; i++){
        if(str[i] == '\n'){
            faceCount++;
            break;
        } 
        if(str[i] == ' '){
            faceCount++;
            if(str[i+1] == ' ' || str[i+1] == '\n') break;
        }
    }
    if(faceCount == 3) makeTri(str, f, obj);
    if(faceCount == 4) makeQuad(str, f, obj);
}

void setFlags(char* path, object** obj){
    (*obj)->flags = 0;
    FILE* file = fopen(path, "r");
    if(file == NULL){
        printf("no file :(");
        fclose(file);
        return;
    }
    char buf[100];
    while(fgets(buf, sizeof(buf), file)){
        if(buf[0] != 'f') continue;
        else break;
    }
    fclose(file);
    //this will check to see what values are present.
    int seenFirstSlash = 0; 
    for(int i = 2; i < sizeof(buf); i++){
        if(buf[i] == ' ') break;
        if(buf[i] == '/' && seenFirstSlash == 0){
            if(buf[i+1] == '/'){
                (*obj)->flags |= NORMALS;
                 break;
            }
            else {
                seenFirstSlash = 1;
                (*obj)->flags |= TEXTURES;
                continue;
            }
        }
        if(buf[i] == '/' && seenFirstSlash == 1){
            (*obj)->flags |= (NORMALS);
        }

    }
}