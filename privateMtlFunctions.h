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
    //malloc in some array the value size * sizeof(material)
    FILE* file = fopen(path, "r");
    if(file == NULL){
        printf("no mtl file :(");
        fclose(file);
        return;
    }
    char buf[200];
    while(fgets(buf, sizeof(buf), file)) {

        //THIS WONT WORK AS EACH ITERATION ONLY DOES ONE VAL
        tempMtl* material
        tempMtl = malloc(sizeof(material)); 
        //


        char temp[10];
        for(int i = 0; i < 10; ++i){
            if(buf[i] == ' ' || buf[i] == '#'){
                break;
            }
            temp[i] = buf[i];
        }
        if(strcmp(temp, "newmtl") == 0){}
        if(strcmp(temp, "Ka") == 0){
            parseThreeFloatArray(obj->Ka, buf);
        }
        if(strcmp(temp, "Kd") == 0){
           parseThreeFloatArray(obj->Kd, buf);
        }
        if(strcmp(temp, "Ks") == 0){
            parseThreeFloatArray(obj->Ks, buf);
        }
        if(strcmp(temp, "Ke") == 0){
            parseThreeFloatArray(obj->Ke, buf);
        }
        if(strcmp(temp, "Kt") == 0){
            parseThreeFloatArray(obj->Kt, buf);
        }
        if(strcmp(temp, "Ns") == 0){
            parseFloat(&obj->Ns, buf);
        }
        if(strcmp(temp, "Ni") == 0){
            parseFloat(&obj->Ni, buf);
        }
        if(strcmp(temp, "Tf") == 0){
            parseThreeFloatArray(obj->Tf, buf);
        }
        if(strcmp(temp, "d") == 0){
            char* endptr
            buf+=2;
            obj->d = strtof(buf, &endptr); 
        }
        if(strcmp(temp, "illum") == 0){
            char* endptr
            buf += 6;
            obj->d = strtol(buf, &endptr);
        }
        memset(buf, 0, sizeof(buf));
        memset(temp, 0, sizeof(temp));
    }
    fclose(file);
}