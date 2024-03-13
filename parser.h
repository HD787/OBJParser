#include <stdio.h>
#include <string.h>
#include "privateFunctions.h"
object* parse(char* path){
    object* obj = malloc(sizeof(object));
    setFlags(path, obj);
    size(path, obj);
    obj->vertices = malloc(sizeof(float) * obj->vertexCount * obj->vertexElementCount);
    obj->textures = malloc(sizeof(float) * obj->textureCount * obj->textureElementCount);
    obj->normals = malloc(sizeof(float) * obj->normalCount * obj->normalElementCount);
    obj->faces = malloc(sizeof(float) * obj->faceCount * obj->faceElementCount);
    obj->materialIndices = malloc(sizeof(materialIndex) * obj->materialIndexCount);

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
        return NULL;
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
            makeFace(buf, &faceCurrentIndex, &faceCountCurrentIndex, obj);
        }
        //object name
        if(strcmp(temp, "o") == 0){}

        //group name
        if(strcmp(temp, "g") == 0){}

        //defines material to be used until another is specified

        if(strcmp(temp, "usemtl") == 0){
            //faceCurrentIndex can be passed in directly as it's not modified
            char* temp = buf;
            char* p = strchr(temp, '\n');
            if (p) *p = '\0';
            temp += 7;
            //printf("%s\n", temp);
            makeMaterialIndex(temp, faceCountCurrentIndex, &materialIndexCurrentIndex, obj);
        }

        //smooth shading??
        if(strcmp(temp, "s") == 0){}

        if(strcmp(temp, "mtllib") == 0){
            char* slice = buf + 7;
            obj->mtlPath = malloc(strlen(slice));
            strcpy(obj->mtlPath, slice);
            char* p = strchr(obj->mtlPath, '\n');
            if (p) *p = '\0';
        }
        memset(buf, 0, sizeof(buf));
        memset(temp, 0, sizeof(temp));
    }
    fclose(file);
    hashMap* hm = createHashMap(obj->materialIndexCount);
    parseMtl(obj, hm);
    printf("%i", hm->bucketCount);
    obj->materialObjects = hm;
    for(int i = 0; i < obj->materialIndexCount; i++){
        //printf("%s", obj->materialIndices[i].materialName);
        value* tempVal = lookUp(hm, obj->materialIndices[i].materialName);
        //printf("%s", tempVal->plainKey);
        obj->materialIndices[i].materialObject = (material*)tempVal->data;
    }
    return obj;
}

void delete(object* obj){
    free(obj->vertices);
    free(obj->textures);
    free(obj->normals);
    free(obj->faces);
    for(int i = 0; i < obj->materialIndexCount; i++){
        free(obj->materialIndices[i].materialName);
    }
    free(obj->materialIndices);
    free(obj);
}

material* getMaterial(object* obj, char* name){
    value* val = lookUp(obj->materialObjects, name);
    return (material*)val->data;
}

//consider a using gettter like functions for better organization, all public functions will be here