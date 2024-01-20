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

    int* faceObjectIndices;
    //posible idea
    int* indexedMaterialList;
    //
    int* faceObjectCount;
    int faceCount;
    int faceElementCount;


    unsigned int flags;
    
}object;