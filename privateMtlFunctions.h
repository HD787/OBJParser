#include "types.h"
void parseThreeFloatArray(float* arr, char* buf){
    char* endptr;
    char* slice = buf + 3;
    char* tokens = strtok(slice, " ");
    for(int i = 0; i < 3; i++){
        arr[i] = strtof(tokens, &endptr);
        tokens = endptr + 1;
    }
}

void parseFloat(float* val, char* buf){
    char* endptr;
    char* slice = buf + 3;
    *val = strtof(slice, &endptr);
}

void parseMtl(object* obj, hashMap* hm){
    FILE* file = fopen(obj->mtlPath, "r");
    if(file == NULL){
        printf("no mtl file :(");
        return;
    }
    char buf[200];
    material* tempMtl = NULL;
    while(fgets(buf, sizeof(buf), file)) {
        char temp[10];
        for(int i = 0; i < 10; ++i){
            if(buf[i] == ' ' || buf[i] == '#'){
                break;
            }
            temp[i] = buf[i];
        }
        if(strcmp(temp, "newmtl") == 0){
            char* slice = buf + 7;
            char* p = strchr(slice, '\n');
            if (p) *p = '\0';
            if(tempMtl == NULL){
                tempMtl = malloc(sizeof(material));
                tempMtl->name = malloc(strlen(slice) + 1);
                strcpy(tempMtl->name, slice);
            }
            else{
                printf("%s : %s \n", tempMtl->name, tempMtl->map_BumpPath);
                insert(hm, tempMtl->name, tempMtl, sizeof(material));
                free(tempMtl);
                tempMtl = malloc(sizeof(material));
                tempMtl->name = malloc(strlen(slice) + 1);
                strcpy(tempMtl->name, slice);
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
            char* endptr;
            char* slice = buf+ 2;
            char* p = strchr(slice, '\n');
            if (p) *p = '\0';
            tempMtl->d = strtof(slice, &endptr); 
        }
        if(strcmp(temp, "illum") == 0){
            char* endptr;
            char* slice = buf + 6;
            char* p = strchr(slice, '\n');
            if (p) *p = '\0';
            tempMtl->d = strtol(slice, &endptr, 10);
        }
        if(strcmp(temp, "map_Kd") == 0){
            char* slice = buf + 6;
            char* p = strchr(slice, '\n');
            if (p) *p = '\0';
            tempMtl->map_KdPath = malloc(strlen(slice) + 1);
            strcpy(tempMtl->map_KdPath, slice);
        }
        if(strcmp(temp, "map_Ka") == 0){
            char* slice = buf + 6;
            char* p = strchr(slice, '\n');
            if (p) *p = '\0';
            tempMtl->map_KdPath = malloc(strlen(slice) + 1);
            strcpy(tempMtl->map_KaPath, slice);
        }
        if(strcmp(temp, "map_Ks") == 0){
            char* slice = buf + 6;
            char* p = strchr(slice, '\n');
            if (p) *p = '\0';
            tempMtl->map_KdPath = malloc(strlen(slice) + 1);
            strcpy(tempMtl->map_KsPath, slice);
        }
        if(strcmp(temp, "map_Ke") == 0){
            char* slice = buf + 6;
            char* p = strchr(slice, '\n');
            if (p) *p = '\0';
            tempMtl->map_KePath = malloc(strlen(slice) + 1);
            strcpy(tempMtl->map_KdPath, slice);
        }
        if(strcmp(temp, "map_Kt") == 0){
            char* slice = buf + 6;
            char* p = strchr(slice, '\n');
            if (p) *p = '\0';
            tempMtl->map_KtPath = malloc(strlen(slice) + 1);
            strcpy(tempMtl->map_KdPath, slice);
        }
        if(strcmp(temp, "map_Ns") == 0){
            char* slice = buf + 6;
            char* p = strchr(slice, '\n');
            if (p) *p = '\0';
            tempMtl->map_NsPath = malloc(strlen(slice) + 1);
            strcpy(tempMtl->map_KdPath, slice);
        }
        if(strcmp(temp, "map_refl") == 0){
            char* slice = buf + 8;
            char* p = strchr(slice, '\n');
            if (p) *p = '\0';
            tempMtl->map_reflPath = malloc(strlen(slice) + 1);
            strcpy(tempMtl->map_KdPath, slice);
        }
        if(strcmp(temp, "map_Bump") == 0){
            char* slice = buf + 8;
            char* p = strchr(slice, '\n');
            if (p) *p = '\0';
            tempMtl->map_BumpPath = malloc(strlen(slice) + 1);
            strcpy(tempMtl->map_BumpPath, slice);
        }
        memset(buf, 0, sizeof(buf));
        memset(temp, 0, sizeof(temp));
    }
    if(tempMtl != NULL){
        printf("%s", tempMtl->name);
        insert(hm, tempMtl->name, tempMtl, sizeof(material));
        //value* val = lookUp(hm, tempMtl->name);
        free(tempMtl);
    }
    fclose(file);
}