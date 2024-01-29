#include "types.h"

//
void parseMtl(object* obj, char path){
    FILE* file = fopen(path, "r");
    if(file == NULL){
        printf("no mtl file :(");
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
        if(strcmp(temp, "newmtl") == 0){}
        if(strcmp(temp, "Ka") == 0){}
        if(strcmp(temp, "Ks") == 0){}
        if(strcmp(temp, "Ke") == 0){}
        if(strcmp(temp, "Ni") == 0){}
        if(strcmp(temp, "d") == 0){}
        if(strcmp(temp, "illum") == 0){}
        memset(buf, 0, sizeof(buf));
        memset(temp, 0, sizeof(temp));
    }
    fclose(file);
}

