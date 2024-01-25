typedef struct{
    int index;
    char* materialName;
}materialIndex;


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
    int faceCount;
    int faceElementCount;
    


    materialIndex* faceObjectIndices;
    int faceObjectIndexCount;
    //the number of face objects denoted by a usemtl tag
    int faceObjectCount;
    


    unsigned int flags;
    
}object;

