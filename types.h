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
    


    materialIndex* materialIndices;
    int materialIndexCount;
    //the number of face objects denoted by a usemtl tag
    int faceObjectCount;
    


    unsigned int flags;
    
}object;

typedef struct{
    char* name;
    //Ka
    float ambient[3];
    //Kd
    float diffuse[3];
    //Ks
    float specular[3];
    //Ns
    float specularExponent;
    //d
    float dissolve;
    //illum
    int illuminationModel;
    //Ni
    float opticalDensity;
    //Ke
    float emmisiveColor[3];

}material;

