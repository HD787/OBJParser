#include "hashMap/hashMap.h"
#include "types.h"

int size(object* obj){
    int sizeMtl = 0;
    path = obj->mtlPath;
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
        if(strcmp(temp, "newmtl") == 0){
            size++;
        }
        memset(buf, 0, sizeof(buf));
        memset(temp, 0, sizeof(temp));
    }
    return size;
}

void parseThreeFloatArray(float* arr, char* buf){
    char *endptr;
    buf += 3;
    char* tokens = strtok(buf, " ");
    for(int i = 0; i < 3; i++){
        arr[i] = strtof(tokens, &endptr);
        tokens = endptr + 1;
    }
}

void parseFloat(float* val, char* buf){
    char *endptr;
    buf += 3;
    *val = strtof(buf, &endptr);
}

void parseMtl(object* obj, hashMap* hm){
    int size = size()
    FILE* file = fopen(path, "r");
    if(file == NULL){
        printf("no mtl file :(");
        fclose(file);
        return;
    }
    char buf[200];
    tempMtl* material = NULL;
    while(fgets(buf, sizeof(buf), file)) {

        //THIS WONT WORK AS EACH ITERATION ONLY DOES ONE VAL
        
         
        //


        char temp[10];
        for(int i = 0; i < 10; ++i){
            if(buf[i] == ' ' || buf[i] == '#'){
                break;
            }
            temp[i] = buf[i];
        }
        if(strcmp(temp, "newmtl") == 0){
            char* slice = buf+=6;
            if(tempMtl == NULL){
                tempMtl = malloc(sizeof(material));
                tempMtl->name = slice
            }
            else{
                insert(hm, tempMtl->name, tempMtl);
                free(tempMtl);
                tempMtl = malloc(sizeof(material));
                tempMtl->name = slice;
            }

        }
        if(strcmp(temp, "Ka") == 0){
            parseThreeFloatArray(tempMtl->Ka, buf);
        }
        if(strcmp(temp, "Kd") == 0){
           parseThreeFloatArray(tempMtl->Kd, buf);
        }
        if(strcmp(temp, "Ks") == 0){
            parseThreeFloatArray(tempMtl->Ks, buf);
        }
        if(strcmp(temp, "Ke") == 0){
            parseThreeFloatArray(tempMtl->Ke, buf);
        }
        if(strcmp(temp, "Kt") == 0){
            parseThreeFloatArray(tempMtl->Kt, buf);
        }
        if(strcmp(temp, "Ns") == 0){
            parseFloat(&tempMtl->Ns, buf);
        }
        if(strcmp(temp, "Ni") == 0){
            parseFloat(&tempMtl->Ni, buf);
        }
        if(strcmp(temp, "Tf") == 0){
            parseThreeFloatArray(tempMtl->Tf, buf);
        }
        if(strcmp(temp, "d") == 0){
            char* endptr
            buf+=2;
            tempMtl->d = strtof(buf, &endptr); 
        }
        if(strcmp(temp, "illum") == 0){
            char* endptr
            buf += 6;
            tempMtl->d = strtol(buf, &endptr);
        }
        if(strcmp(temp, "map_Kd")){
            char* slice = buf += 6;
            tempMtl->map_KdPath = slice;
        }
        if(strcmp(temp, "map_Ka")){
            char* slice = buf += 6;
            tempMtl->map_KaPath = slice;
        }
        if(strcmp(temp, "map_Ks")){
            char* slice = buf += 6;
            tempMtl->map_KsPath = slice;
        }
        if(strcmp(temp, "map_Ke")){
            char* slice = buf += 6;
            tempMtl->map_KePath = slice;
        }
        if(strcmp(temp, "map_Kt")){
            char* slice = buf += 6;
            tempMtl->map_KtPath = slice;
        }
        if(strcmp(temp, "map_Ns")){
            char* slice = buf += 6;
            tempMtl->map_NsPath = slice;
        }
        if(strcmp(temp, "map_refl")){
            char* slice = buf += 8;
            tempMtl->map_reflPath = slice;
        }
        if(strcmp(temp, "map_Bump")){
            char* slice = buf += 8;
            tempMtl->map_BumpPath = slice;
        }

        memset(buf, 0, sizeof(buf));
        memset(temp, 0, sizeof(temp));
    }
    if(tempMtl != NULL){
        insert(hm, tempMtl->name, tempMtl);
        free(tempMtl);
    }
    fclose(file);
}