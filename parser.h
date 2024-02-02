#include <stdio.h>
#include <string.h>
#include "privateFunctions.h"
#include "types.h"
#include "mtlParser.h"
object* parse(char* path){
    object* obj = malloc(sizeof(object));
    setFlags(path, obj);
    size(path, obj);
    // printf("%i\n", obj->faceCount);
    obj->vertices = malloc(sizeof(float) * obj->vertexCount * obj->vertexElementCount);
    obj->textures = malloc(sizeof(float) * obj->textureCount * obj->textureElementCount);
    obj->normals = malloc(sizeof(float) * obj->normalCount * obj->normalElementCount);
    obj->faces = malloc(sizeof(float) * obj->faceCount * obj->faceElementCount);
    obj->materialIndices = malloc(sizeof(materialIndex) * obj->materialIndexCount);
    //obj->faces = malloc(sizeof(float) * 1000);

    //wrap this in a struct??
    int vectorCurrentIndex = 0, 
        normalCurrentIndex = 0, 
        textureCurrentIndex = 0,
        //keeps track of place in face array 
        faceCurrentIndex = 0, 
        materialIndexCurrentIndex = 0,
        //this is keeps track of a full face object, so a tri is one and a quad is two
        //so if you multiply this number by the length of faceElementCount you'll get the right index
        faceCountCurrentIndex = 0;


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
        if(strcmp(temp, "v") == 0){
            makeVertex(buf, &vectorCurrentIndex, obj);
        }
        //texture coordinates
        if(strcmp(temp, "vt") == 0){
            makeTexture(buf, &textureCurrentIndex, obj);
        }
        //normals vn
        if(strcmp(temp, "vn") == 0){
            makeNormal(buf, &normalCurrentIndex, obj);
        }
        //face
        if(strcmp(temp, "f") == 0){
            //printf(" %i ", test++);
            makeFace(buf, &faceCurrentIndex, &faceCountCurrentIndex, obj);
        }
        //object name
        if(strcmp(temp, "o")){}

        //group name
        if(strcmp(temp, "g")){}

        //defines material to be used until another is specified
        if(strcmp(temp, "usemtl") == 0){
            //printf("this should happen once");
            //faceCurrentIndex can be passed in directly as it's not modified
            makeMaterialIndex(buf, faceCountCurrentIndex, &materialIndexCurrentIndex, obj);
        }

        //smooth shading??
        if(strcmp(temp, "s")){}

        if(strcmp(temp, "mtllib")){
            char* slice = buf + 5;
            obj->mtlPath = silce;
        }
        //printf("%s\n", buf);
        memset(buf, 0, sizeof(buf));
        memset(temp, 0, sizeof(temp));
    }
    fclose(file);
}