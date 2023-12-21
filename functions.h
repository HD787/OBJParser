#include "types.h"
#include "stdlib.h"
#include "stdio.h"

vertex* makeVertex(char* str){
    int i = 2;
    float vals[4];
    int valcounter = 0;
    char * endptr;
    str += 2; 
    while(*str != '\0' && valcounter < 4){
        vals[valcounter] = strtof(str, &endptr);
        if(*endptr != '\0'){
            str = endptr + 1;
            ++valcounter;
        }
        else{
            break;
        }
    }
    vertex* vert = malloc(sizeof(vertex));
    *vert = (vertex){vals[0], vals[1], vals[2], (valcounter < 4) ? 1.0 : vals[3]};
    return vert;
}

texture* makeTexture(char* str){
    int i = 2;
    float vals[3];
    int valcounter = 0;
    char * endptr;
    str += 2; 
    while(*str != '\0' && valcounter < 3){
        vals[valcounter] = strtof(str, &endptr);
        if(*endptr != '\0'){
            str = endptr + 1;
            ++valcounter;
        }
        else{
            break;
        }
    }
    texture* text = malloc(sizeof(texture));
    *text = (texture){vals[0], vals[1], (valcounter < 3) ? 1.0 : vals[3]};
    return text;
}

normal* makeNormal(char* str){
   int i = 2;
    float vals[3];
    int valcounter = 0;
    char * endptr;
    str += 2; 
    while(*str != '\0' && valcounter < 3){
        vals[valcounter] = strtof(str, &endptr);
        if(*endptr != '\0'){
            str = endptr + 1;
            ++valcounter;
        }
        else{
            break;
        }
    }
    normal* norm = malloc(sizeof(normal));
    *norm = (normal){vals[0], vals[1], vals[2]};
    return norm;
}

// int main(){
//     char* str = "v 8 0 11.0";
//     vertex* vert = makeVertex(str);
//     printf("%f , %f , %f, %f", vert->x, vert->y, vert->z, vert->w);
// }