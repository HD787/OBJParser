typedef struct{
    float* vertices;
    int vertexCount;

    float* normals;
    int normalCount;

    float* textures;
    int textureCount;

    float* faces;
    int faceCount;
    int faceElementCount;
    unsigned int flags;
    
}object;