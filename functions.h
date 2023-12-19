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
//this is done, vals contains the float, figure out what you gotta do
int main(){
    char* str = "v 8 0 11.0";
    vertex* vert = makeVertex(str);
    printf("%f , %f , %f, %f", vert->x, vert->y, vert->z, vert->w);
}