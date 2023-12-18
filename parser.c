#include <stdio.h>
void parse(char* path){
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
        printf("%s", temp);
        for(int j=0; j < sizeof(buf); ++j){ buf[j] = 0; }
    }
}

typedef struct{
    float x,y,x,w;
}vec3;

typedef struct{
    float u,v,w;
}texture_coords;

int main(){
    parse("example.obj");
}