#include <stdio.h>
#include "functions.h"
#include "types.h"
void parse(char* path){
    FILE* file = fopen(path, "r");
    if(file == NULL){
        printf("no file :(");
        fclose(file);
    }
    char buf[100];
    while (fgets(buf, sizeof(buf), file)) {
        char temp[10];
        //this loop identifies the meaning of the line by pulling out the characters that signify the lines purpose
        //temp is the purpose
        for(int i = 0; i < 10; ++i){
            //lines starting with a space and hashtag are to be ignored, the signifier is delimited by a space
            if(buf[i] == ' ' | buf[i] == '#'){
                break;
            }
            temp[i] = buf[i];
        }
        //vertex
        if(temp == "v"){}
        //texture coordinates
        if(temp == "vt"){}
        //normals
        if(temp == "vn"){}
        //face
        if(temp == "f"){}
        //object name
        if(temp == "o"){}
        //group name
        if(temp == "g"){}
        //defnes material to be used until another is specified
        if(temp == "usemtl"){}
        //smooth shading??
        if(temp == "s"){}
        if(temp == "mtllib"){}


        printf("%s", temp);
        //clears buf buffer, same as memset in string.h but wanted to implement it myself
        for(int j=0; j < sizeof(buf); ++j){ buf[j] = 0; }
    }
}



int main(){
    parse("example.obj");
}