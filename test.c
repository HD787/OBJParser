#include "parser.h"
#include "stdio.h"

void printBinary(unsigned int num) {
    for (int i = (sizeof(unsigned int) * 8) - 1; i >= 0; i--) {
        putchar((num & (1u << i)) ? '1' : '0');
    }
}

int main(){
    char* val = "cube.obj";
    object* obj = parse("pirate-chest-with-gold-coins.obj");
    //parse("../copengl/pirate_gold_copy.obj", obj);
    //printf("%f, %f, %f", vertices[1], vertices[1], vertices[1]);

    //printf("\n%i\n", obj->faceElementCount);
    // printf("%i\n", obj->normalCount);
    // printf("%i\n", obj->textureCount);
    // printf("%i\n", obj->faceCount);
    //printf("%d, here", obj->flags);
    //printBinary(obj->flags);
    //printf("%s : %i\n", (obj->materialIndices[0]).materialName, obj->materialIndices[0].index);
    // int test = 0;
    // for(int i = 0; i < obj->faceCount; i++){
    //     printf("%f\n", obj->faces[i]);
    // }
    //printf("%f\n", obj->faces[10]);
    // printf("%i\n", obj->materialIndexCount);
    // printf("%i\n", obj->faceCount);
    // printf("%i\n",obj->faceElementCount);
    // printf("%i\n", obj->materialIndices[1].index);
    // printf("%i", obj->materialIndices[1].index * obj->faceElementCount);
    //printf("\n%f", obj->faces[300]);
    int test = 0;
    //printf("%i", obj->materialIndexCount);
    for(int i = 0; i < obj->materialIndexCount; i++){
        //material* mat = getMaterial(obj, obj->materialIndices[i].materialName);
        //printf("%s", mat->map_BumpPath);
        //printf("%s : %i : %i\n", obj->materialIndices[i].materialName,obj->materialIndices[i].index,test++);
    }
    
    delete(obj);

    // hashMap* hm = createHashMap(17);
    // object* obj;
    // obj->mtlPath = "example.obj";
    // parseMtl(obj, hm);


} 