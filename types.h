typedef struct{
    int index;
    char* materialName;
}materialIndices;


typedef struct{
    float* vertices;
    int vertexCount;
    int vertexElementCount;

    float* normals;
    int normalCount;
    int normalElementCount;

    float* textures;
    int textureCount;
    int textureElementCount;

    float* faces;
    //posible idea, the other is to use a list of structs containing the index and the name of the material
    int* faceObjectIndices;
    
    //char** indexedMaterialList;
    


    //other idea array of structs
    //materialIndices* faceObjectIndices;
    int faceObjectCount;
    int faceCount;
    int faceElementCount;


    unsigned int flags;
    
}object;

