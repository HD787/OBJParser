typedef struct{
    float x,y,x,w;
}vec3;

typedef struct{
    float u,v,w;
}texture;

typedef struct{
    float x,y,z;
}normals;

typedef struct{
    int vertexIndex;
    int textureIndex;
    int normalIndex;
}faceVertex;

typedef struct{
    faceVertex * vertices;
    int numVertices;
}face;