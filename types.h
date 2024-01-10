typedef struct{
    float* vertices;
    int vertexCount;

    float* normals;
    int normalCount;

    float* textures;
    int textureCount;

    float* faces;
    int faceCount;
    unsigned int flags;
    
}object;