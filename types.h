typedef struct{
    int *vertexIndices;
    int *textureIndices;
    int *normalIndices;
    int numVertices;
} face;

// typedef struct{
//     faceVertex * indices;
//     int numVertices;
// }face;

typedef struct{
    float* vertices;
    int vertexCount = 0;
    float* normals;
    int normalCount = 0;
    float* textures;
    int textureCount = 0;
}object;