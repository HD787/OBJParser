#include "types.h"
#include "mtlParser.c"
#include <stdlib.h>
#include <stdio.h>
#include <string.h>

#define TEXTURES (1 << 0)
#define NORMALS (1 << 1)
#define TRIPLETEXTURE (1 << 2)

void size(char* path, object* obj){
    //instantiate vertex vals
    obj->vertexCount = 0;
    obj->vertexElementCount = 3;

    //instantiate texture vals
    obj->textureCount = 0;
    obj->textureElementCount = 0;
    if(obj->flags & TRIPLETEXTURE){
        obj->textureElementCount = 3;
    }
    else if(obj->flags & TEXTURES) obj->textureElementCount = 2; 

    //instantiate normal vals
    obj->normalCount = 0;
    if(obj->flags & TEXTURES)
        obj->normalElementCount = 3;
    else obj->normalElementCount = 0; 

    //instantiate face vals
    obj->faceCount = 0;
    obj->faceElementCount = 9;
    if(obj->flags & NORMALS) obj->faceElementCount += 9;
    if(obj->flags & TRIPLETEXTURE) obj->faceElementCount += 9;
    if(!(obj->flags & TRIPLETEXTURE) && obj->flags & TEXTURES) obj->faceElementCount += 6;

    //instantiate face index for materials vals
    obj->materialIndexCount = 0;

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
            if(buf[i] == ' ' || buf[i] == '#') break;
            temp[i] = buf[i];
        }
        if(strcmp(temp, "v") == 0)
            obj->vertexCount += 3;

        if(strcmp(temp, "vt") == 0){
            obj->textureCount++;
            if(obj->flags & TRIPLETEXTURE){
                obj->textureElementCount += 3;
            }else obj->textureCount += 2; 
        }
        if(strcmp(temp, "vn") == 0)
            obj->normalCount += 3;

        if(strcmp(temp, "f") == 0){
            int count = 0;
            for(int i = 2; i < 100; i++){
                if(buf[i] != ' '){
                    continue;
                }
                if(buf[i] == ' ' ){
                    ++count;
                }
                if(buf[i] == '\n') 
                    break;
            }
            if(count == 2) obj->faceCount++;
            if(count == 3) obj->faceCount += 2;
        }
        if(strcmp(temp, "usemtl") == 0){
            obj->materialIndexCount++;
        }
        memset(temp, 0, sizeof(temp));
        memset(buf, 0, sizeof(buf));
    }
   
}

void delete(object* obj){
    free(obj->vertices);
    free(obj->textures);
    free(obj->normals);
    free(obj->faces);
    for(int i = 0; i < obj->materialIndexCount; i++){
        free(obj->materialIndices[i].materialName);
    }
    free(obj->materialIndices);
    free(obj);
}

void makeVertex(char* str, int* v, object* obj){
    char * endptr;
    str += 2; 
    while(*str != '\0'){
        float val;
        obj->vertices[*v] = val = strtof(str, &endptr);
        //printf(" %f ", val);
        (*v)++;
        if(*endptr != '\0')
            str = endptr + 1;
        else break;
    }
}

void makeTexture(char* str, int* t, object* obj){
    char * endptr;
    str += 3; 
    while(*str != '\0'){
        obj->textures[*t] = strtof(str, &endptr);
        (*t)++;
        if(*endptr != '\0')
            str = endptr + 1;
        else break;
    }
}

void makeNormal(char* str, int* n, object* obj){
    char * endptr;
    str += 3; 
    while(*str != '\0'){
        obj->normals[*n] = strtof(str, &endptr);
        (*n)++;
        if(*endptr != '\0') 
            str = endptr + 1;
        else break;
    }
}

void makeQuad(char* str, int* f, int* fc, object* obj){
    *fc += 2;
    if(obj->flags == 0){
        //1 element per face
        int arr[4];
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
        //make two triangles;
        unsigned int arr1[3];
        unsigned int arr2[3];

        arr1[0] = arr[0];
        arr1[1] = arr[1];
        arr1[2] = arr[2];

        arr2[0] = arr[0];
        arr2[1] = arr[2];
        arr2[2] = arr[3];

        for(int i = 0; i < 3; i += 1){
            unsigned long vertexIndex = (arr1[i] - 1) * 3;
            obj->faces[(*f)++] = obj->vertices[vertexIndex];
            obj->faces[(*f)++] = obj->vertices[vertexIndex + 1];
            obj->faces[(*f)++] = obj->vertices[vertexIndex + 2];  
        }
        for(int i = 0; i < 3; i += 1){
            unsigned long vertexIndex = (arr2[i] - 1) * 3;
            obj->faces[(*f)++] = obj->vertices[vertexIndex];
            obj->faces[(*f)++] = obj->vertices[vertexIndex + 1];
            obj->faces[(*f)++] = obj->vertices[vertexIndex + 2];  
        }
        return;
    }
    //textures only, two values
    if(obj->flags == 1){
        //2 elements per face
        int arr[8];
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
        unsigned int arr1[6];
        unsigned int arr2[6];

        arr1[0] = arr[0];
        arr1[1] = arr[1];
        arr1[2] = arr[2];
        arr1[3] = arr[3];
        arr1[4] = arr[4];
        arr1[5] = arr[5];

        arr2[0] = arr[0];
        arr2[1] = arr[1];
        arr2[2] = arr[4];
        arr2[3] = arr[5];
        arr2[4] = arr[6];
        arr2[5] = arr[7];

        for(int i = 0; i < 6; i += 2){
            unsigned long vertexIndex = (arr1[i] - 1) * 3;
            unsigned long textureIndex = (arr1[i + 1] - 1) * 2;
            obj->faces[(*f)++] = obj->vertices[vertexIndex];
            obj->faces[(*f)++] = obj->vertices[vertexIndex + 1];
            obj->faces[(*f)++] = obj->vertices[vertexIndex + 2];

            obj->faces[(*f)++] = obj->textures[textureIndex];
            obj->faces[(*f)++] = obj->textures[textureIndex + 1];
        }
        for(int i = 0; i < 6; i += 2){
            unsigned long vertexIndex = (arr2[i] - 1) * 3;
            unsigned long textureIndex = (arr2[i + 1] - 1) * 2;
            obj->faces[(*f)++] = obj->vertices[vertexIndex];
            obj->faces[(*f)++] = obj->vertices[vertexIndex + 1];
            obj->faces[(*f)++] = obj->vertices[vertexIndex + 2];

            obj->faces[(*f)++] = obj->textures[textureIndex];
            obj->faces[(*f)++] = obj->textures[textureIndex + 1];
        }
        return;
    }

    // only normals
    if(obj->flags == 2){
        int arr[8];
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
        unsigned int arr1[6];
        unsigned int arr2[6];

        arr1[0] = arr[0];
        arr1[1] = arr[1];
        arr1[2] = arr[2];
        arr1[3] = arr[3];
        arr1[4] = arr[4];
        arr1[5] = arr[5];

        arr2[0] = arr[0];
        arr2[1] = arr[1];
        arr2[2] = arr[4];
        arr2[3] = arr[5];
        arr2[4] = arr[6];
        arr2[5] = arr[7];
        for(int i = 0; i < 6; i+=2){
            unsigned long vertexIndex = (arr1[i] - 1) * 3;
            unsigned long normalIndex = (arr1[i + 1] - 1) * 3;
            obj->faces[(*f)++] = obj->vertices[vertexIndex];
            obj->faces[(*f)++] = obj->vertices[vertexIndex + 1];
            obj->faces[(*f)++] = obj->vertices[vertexIndex + 2];

            obj->faces[(*f)++] = obj->normals[normalIndex];
            obj->faces[(*f)++] = obj->normals[normalIndex + 1];
            obj->faces[(*f)++] = obj->normals[normalIndex + 2];
        }
        for(int i = 0; i < 6; i+=2){
            unsigned long vertexIndex = (arr2[i] - 1) * 3;
            unsigned long normalIndex = (arr2[i + 1] - 1) * 3;
            obj->faces[(*f)++] = obj->vertices[vertexIndex];
            obj->faces[(*f)++] = obj->vertices[vertexIndex + 1];
            obj->faces[(*f)++] = obj->vertices[vertexIndex + 2];

            obj->faces[(*f)++] = obj->normals[normalIndex];
            obj->faces[(*f)++] = obj->normals[normalIndex + 1];
            obj->faces[(*f)++] = obj->normals[normalIndex + 2];
        }
        return;
    }

    //all three, 2 values for texture
    if(obj->flags == 3){
        int arr[12];
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
        unsigned int arr1[9];
        unsigned int arr2[9];

        arr1[0] = arr[0];
        arr1[1] = arr[1];
        arr1[2] = arr[2];
        arr1[3] = arr[3];
        arr1[4] = arr[4];
        arr1[5] = arr[5];
        arr1[6] = arr[6];
        arr1[7] = arr[7];
        arr1[7] = arr[8];

        arr2[0] = arr[0];
        arr2[1] = arr[1];
        arr2[2] = arr[2];
        arr2[3] = arr[6];
        arr2[4] = arr[7];
        arr2[5] = arr[8];
        arr2[6] = arr[9];
        arr2[7] = arr[10];
        arr2[8] = arr[11];  
        for(int i = 0; i < 9; i += 3){
            unsigned long vertexIndex = (arr1[i] - 1) * 3;
            unsigned long textureIndex = (arr1[i + 1] - 1) * 2;
            unsigned long normalIndex = (arr1[i + 2] - 1) * 3;
            obj->faces[(*f)++] = obj->vertices[vertexIndex];
            obj->faces[(*f)++] = obj->vertices[vertexIndex + 1];
            obj->faces[(*f)++] = obj->vertices[vertexIndex + 2];

            obj->faces[(*f)++] = obj->textures[textureIndex];
            obj->faces[(*f)++] = obj->textures[textureIndex + 1];

            obj->faces[(*f)++] = obj->normals[normalIndex];
            obj->faces[(*f)++] = obj->normals[normalIndex + 1];
            obj->faces[(*f)++] = obj->normals[normalIndex + 2];
        }
        for(int i = 0; i < 9; i += 3){
            unsigned long vertexIndex = (arr2[i] - 1) * 3;
            unsigned long textureIndex = (arr2[i + 1] - 1) * 2;
            unsigned long normalIndex = (arr2[i + 2] - 1) * 3;
            obj->faces[(*f)++] = obj->vertices[vertexIndex];
            obj->faces[(*f)++] = obj->vertices[vertexIndex + 1];
            obj->faces[(*f)++] = obj->vertices[vertexIndex + 2];

            obj->faces[(*f)++] = obj->textures[textureIndex];
            obj->faces[(*f)++] = obj->textures[textureIndex + 1];

            obj->faces[(*f)++] = obj->normals[normalIndex];
            obj->faces[(*f)++] = obj->normals[normalIndex + 1];
            obj->faces[(*f)++] = obj->normals[normalIndex + 2];
        }
        return;
    }
    //only textures, 3 values
    if(obj->flags == 4 || obj->flags == 5){
        int arr[8];
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
        unsigned int arr1[6];
        unsigned int arr2[6];

        arr1[0] = arr[0];
        arr1[1] = arr[1];
        arr1[2] = arr[2];
        arr1[3] = arr[3];
        arr1[4] = arr[4];
        arr1[5] = arr[5];

        arr2[0] = arr[0];
        arr2[1] = arr[1];
        arr2[2] = arr[4];
        arr2[3] = arr[5];
        arr2[4] = arr[6];
        arr2[5] = arr[7];
        for(int i = 0; i < 6; i += 2){
            unsigned long vertexIndex = (arr1[i] - 1) * 3;
            unsigned long textureIndex = (arr1[i + 1] - 1) * 3;
            obj->faces[(*f)++] = obj->vertices[vertexIndex];
            obj->faces[(*f)++] = obj->vertices[vertexIndex + 1];
            obj->faces[(*f)++] = obj->vertices[vertexIndex + 2];

            obj->faces[(*f)++] = obj->textures[textureIndex];
            obj->faces[(*f)++] = obj->textures[textureIndex + 1];
            obj->faces[(*f)++] = obj->textures[textureIndex + 2];
        }
        for(int i = 0; i < 6; i += 2){
            unsigned long vertexIndex = (arr2[i] - 1) * 3;
            unsigned long textureIndex = (arr2[i + 1] - 1) * 3;
            obj->faces[(*f)++] = obj->vertices[vertexIndex];
            obj->faces[(*f)++] = obj->vertices[vertexIndex + 1];
            obj->faces[(*f)++] = obj->vertices[vertexIndex + 2];

            obj->faces[(*f)++] = obj->textures[textureIndex];
            obj->faces[(*f)++] = obj->textures[textureIndex + 1];
            obj->faces[(*f)++] = obj->textures[textureIndex + 2];
        }
        return;
    }

    //6 should be impossible
    //all three, three value textures
    if(obj->flags == 7){
        int arr[12];
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
        unsigned int arr1[9];
        unsigned int arr2[9];

        arr1[0] = arr[0];
        arr1[1] = arr[1];
        arr1[2] = arr[2];
        arr1[3] = arr[3];
        arr1[4] = arr[4];
        arr1[5] = arr[5];
        arr1[6] = arr[6];
        arr1[7] = arr[7];
        arr1[7] = arr[8];

        arr2[0] = arr[0];
        arr2[1] = arr[1];
        arr2[2] = arr[2];
        arr2[3] = arr[6];
        arr2[4] = arr[7];
        arr2[5] = arr[8];
        arr2[6] = arr[9];
        arr2[7] = arr[10];
        arr2[8] = arr[11];  
        for(int i = 0; i < 9; i += 3){
            unsigned long vertexIndex = (arr1[i] - 1) * 3;
            unsigned long textureIndex = (arr1[i + 1] - 1) * 3;
            unsigned long normalIndex = (arr1[i + 2] - 1) * 3;
            obj->faces[(*f)++] = obj->vertices[vertexIndex];
            obj->faces[(*f)++] = obj->vertices[vertexIndex + 1];
            obj->faces[(*f)++] = obj->vertices[vertexIndex + 2];

            obj->faces[(*f)++] = obj->textures[textureIndex];
            obj->faces[(*f)++] = obj->textures[textureIndex + 1];
            obj->faces[(*f)++] = obj->textures[textureIndex + 2];

            obj->faces[(*f)++] = obj->normals[normalIndex];
            obj->faces[(*f)++] = obj->normals[normalIndex + 1];
            obj->faces[(*f)++] = obj->normals[normalIndex + 2];
        }
        for(int i = 0; i < 9; i += 3){
            unsigned long vertexIndex = (arr2[i] - 1) * 3;
            unsigned long textureIndex = (arr2[i + 1] - 1) * 3;
            unsigned long normalIndex = (arr2[i + 2] - 1) * 3;
            obj->faces[(*f)++] = obj->vertices[vertexIndex];
            obj->faces[(*f)++] = obj->vertices[vertexIndex + 1];
            obj->faces[(*f)++] = obj->vertices[vertexIndex + 2];

            obj->faces[(*f)++] = obj->textures[textureIndex];
            obj->faces[(*f)++] = obj->textures[textureIndex + 1];
            obj->faces[(*f)++] = obj->textures[textureIndex + 2];

            obj->faces[(*f)++] = obj->normals[normalIndex];
            obj->faces[(*f)++] = obj->normals[normalIndex + 1];
            obj->faces[(*f)++] = obj->normals[normalIndex + 2];
        }
        return;
    }
}

//better names in this function signature, consider doing this elsewhere.
int test = -1;
void makeMaterialIndex(char* str, int faceCountCurrentIndex, int* materialIndicesCurrentIndex, object* obj){
    //printf("%s : %i\n", (obj->materialIndices[test]).materialName, obj->materialIndices[test++].index);
    materialIndex* temp = malloc(sizeof(materialIndex));
    temp->index = faceCountCurrentIndex;
    char* slice = str + 6;
    temp->materialName = malloc(strlen(slice) + 1);
    strcpy(temp->materialName, slice);
    obj->materialIndices[(*materialIndicesCurrentIndex)++] = *temp;
    //printf("%s : %i\n", (obj->materialIndices[*materialIndicesCurrentIndex - 1]).materialName, obj->materialIndices[*materialIndicesCurrentIndex - 1].index);
}

void makeTri(char* str, int* f, int* fc, object* obj){
    *fc += 1;
    //no normals, no textures
    if(obj->flags == 0){
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
        for(int i = 0; i < 3; i += 2){
            unsigned long vertexIndex = (arr[i] - 1) * 3;
            obj->faces[(*f)++] = obj->vertices[vertexIndex];
            obj->faces[(*f)++] = obj->vertices[vertexIndex + 1];
            obj->faces[(*f)++] = obj->vertices[vertexIndex + 2]; 
            //printf("%c", arr[i]);   
        }
        return;
    }

    //textures only, two values
    if(obj->flags == 1){
        const unsigned int valueCount = 6;
        int arr[valueCount];
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
        for(int i = 0; i < valueCount; i += 2){
            unsigned long vertexIndex = (arr[i] - 1) * 3;
            unsigned long textureIndex = (arr[i + 1] - 1) * 2;
            obj->faces[(*f)++] = obj->vertices[vertexIndex];
            obj->faces[(*f)++] = obj->vertices[vertexIndex + 1];
            obj->faces[(*f)++] = obj->vertices[vertexIndex + 2];

            obj->faces[(*f)++] = obj->textures[textureIndex];
            obj->faces[(*f)++] = obj->textures[textureIndex + 1];
        }
        return;
    }

    //normals only
    if(obj->flags == 2){
        //printf("%i\n", test++);
        const unsigned int valueCount = 6;
        int arr[valueCount];
        int index = 0;
        str += 2;
        char * endptr;
        while(*str != '\0'){
            unsigned int val;
            val = strtoul(str, &endptr, 10);
            //printf(" %i ", val);
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
            } else break;
        }
        for(int i = 0; i < valueCount; i+=2){
            unsigned long vertexIndex = (arr[i] - 1) * 3;
            unsigned long normalIndex = (arr[i + 1] - 1) * 3;
            //printf("%lu v\n", vertexIndex);
            //printf("%lu n\n", normalIndex);
            //printf(" %i ", test++);
            obj->faces[(*f)++] = obj->vertices[vertexIndex];
            // printf("v1: %f ", obj->vertices[vertexIndex]);
            obj->faces[(*f)++] = obj->vertices[vertexIndex + 1];
            // printf("v2: %f ", obj->vertices[vertexIndex + 1]);
            obj->faces[(*f)++] = obj->vertices[vertexIndex + 2];
            // printf("v3: %f ", obj->vertices[vertexIndex + 2]);

            obj->faces[(*f)++] = obj->normals[normalIndex];
            // printf("n1: %f ", obj->normals[normalIndex]);
            obj->faces[(*f)++] = obj->normals[normalIndex + 1];
            // printf("n2: %f ", obj->normals[normalIndex + 1]);
            obj->faces[(*f)++] = obj->normals[normalIndex + 2];
            // printf("n3: %f\n", obj->normals[normalIndex + 2]);
        }
        return;
    } 

    //normals and textures, two texture values
    if(obj->flags == 3){
        const unsigned int valueCount = 9;
        int arr[valueCount];
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
        for(int i = 0; i < valueCount; i += 3){
            unsigned long vertexIndex = (arr[i] - 1) * 3;
            unsigned long textureIndex = (arr[i + 1] - 1) * 2;
            unsigned long normalIndex = (arr[i + 2] - 1) * 3;
            obj->faces[(*f)++] = obj->vertices[vertexIndex];
            obj->faces[(*f)++] = obj->vertices[vertexIndex + 1];
            obj->faces[(*f)++] = obj->vertices[vertexIndex + 2];

            obj->faces[(*f)++] = obj->textures[textureIndex];
            obj->faces[(*f)++] = obj->textures[textureIndex + 1];

            obj->faces[(*f)++] = obj->normals[normalIndex];
            obj->faces[(*f)++] = obj->normals[normalIndex + 1];
            obj->faces[(*f)++] = obj->normals[normalIndex + 2];
        }
        return;
    }
    //4 should be impossible as if the third bit is a 1, so will the first bit
    //so im folding them in together, think this will be fine
    //vertices and textures with three values
    if(obj->flags == 4 || obj->flags == 5){
        const unsigned int valueCount = 6;
        int arr[valueCount];
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
        for(int i = 0; i < valueCount; i += 2){
            unsigned long vertexIndex = (arr[i] - 1) * 3;
            unsigned long textureIndex = (arr[i + 1] - 1) * 3;
            obj->faces[(*f)++] = obj->vertices[vertexIndex];
            obj->faces[(*f)++] = obj->vertices[vertexIndex + 1];
            obj->faces[(*f)++] = obj->vertices[vertexIndex + 2];

            obj->faces[(*f)++] = obj->textures[textureIndex];
            obj->faces[(*f)++] = obj->textures[textureIndex + 1];
            obj->faces[(*f)++] = obj->textures[textureIndex + 2];
        }
        return;
    }
    //6 also should be impossible as the binary representation of 6 is 110, again meaning triple values is present but textures is not

    //normals and textures are present with triple values
    if(obj->flags == 7){
        const unsigned int valueCount = 9;
        int arr[valueCount];
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
        for(int i = 0; i < valueCount; i += 3){
            unsigned long vertexIndex = (arr[i] - 1) * 3;
            unsigned long textureIndex = (arr[i + 1] - 1) * 3;
            unsigned long normalIndex = (arr[i + 2] - 1) * 3;
            obj->faces[(*f)++] = obj->vertices[vertexIndex];
            obj->faces[(*f)++] = obj->vertices[vertexIndex + 1];
            obj->faces[(*f)++] = obj->vertices[vertexIndex + 2];

            obj->faces[(*f)++] = obj->textures[textureIndex];
            obj->faces[(*f)++] = obj->textures[textureIndex + 1];
            obj->faces[(*f)++] = obj->textures[textureIndex + 2];

            obj->faces[(*f)++] = obj->normals[normalIndex];
            obj->faces[(*f)++] = obj->normals[normalIndex + 1];
            obj->faces[(*f)++] = obj->normals[normalIndex + 2];
        }
        return;
    }
}
void makeFace(char* str, int* f, int* fc, object* obj){
    int faceCountInLine = 0;
    for(int i = 2; i < 100; i++){
        if(str[i] == '\n' || str[i] == '\0'){
            faceCountInLine++;
            break;
        } 
        if(str[i] == ' '){
            faceCountInLine++;
            if(str[i+1] == ' ' || str[i+1] == '\n') break;
        }
    }
    if(faceCountInLine == 3) makeTri(str, f, fc, obj);
    if(faceCountInLine == 4) makeQuad(str, f, fc, obj);
}

void setFlags(char* path, object* obj){
    obj->flags = 0;
    FILE* file = fopen(path, "r");
    if(file == NULL){
        printf("no file :(");
        fclose(file);
        return;
    }
    char buf[100];
    char textureBuffer[100];
    int foundTexture = 0;
    while(fgets(buf, sizeof(buf), file)){
        if(buf[1] == 't' && foundTexture == 0){ 
            foundTexture = 1;  
            memcpy(textureBuffer, buf, sizeof(buf));}
        if(buf[0] != 'f') continue;
        else break;
    }
    fclose(file);

    unsigned short textureCount = 0;
    if(foundTexture == 1){
        for(int i = 3; i < 100; i++){
            if(textureBuffer[i] == ' ')textureCount++;
        }
    }
    if(textureCount == 2) obj->flags |= TRIPLETEXTURE;

    //this will check to see what values are present.
    int seenFirstSlash = 0; 
    for(int i = 2; i < sizeof(buf); i++){
        if(buf[i] == ' ') break;
        if(buf[i] == '/' && seenFirstSlash == 0){
            if(buf[i+1] == '/'){
                obj->flags |= NORMALS;
                 break;
            }
            else {
                seenFirstSlash = 1;
                obj->flags |= TEXTURES;
                continue;
            }
        }
        if(buf[i] == '/' && seenFirstSlash == 1){
            obj->flags |= (NORMALS);
        }

    }
}