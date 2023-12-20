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
    int vertexIndex;
    int textureIndex;
    int normalIndex;
}faceVertex;

typedef struct{
    faceVertex * indices;
    int numVertices;
}face;

typedef struct{
    char* name;
    vertex* one,two,three;
}object;