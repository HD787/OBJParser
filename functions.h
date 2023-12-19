#include "types.h"
#include "stdlib.h"
#include "stdio.h"
void makeVertex(char* str){
    int i = 2;
    float vals[4];
    int valcounter = 0;
    char * endptr;
    str += 2; 
    while(*str != '\0' && valcounter < 4){
        vals[valcounter] = strtof(str, &endptr);
        ++valcounter;
        if(*endptr != '\0'){
            str = endptr + 1;
        }
        else{
            break;
        }
    }
}
//this is done, vals contains the float, figure out what you gotta do
int main(){
    char* str = "v 8 0 11.0";
    makeVertex(str);
}