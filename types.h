typedef struct{
    float x,y,z,w;
}vertex;

typedef struct{
    float u,v,w;
}texture;

typedef struct{
    float x,y,z;
}normal;

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
    char* name;
    vertex* one,two,three;
}object;