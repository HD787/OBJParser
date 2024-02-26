typedef struct{
    char* name;
    float Ka[3]; //ambient
    float Kd[3]; //diffuse
    float Ks[3]; //specular   
    float Ke[3];  //emisive color
    float Kt[3]; //transmittence
    float Ns; //specularExponent
    float Ni; //optical density
    float Tf[3]; //transmission filter
    float d; //dissolve
    int illum; //illuminamtionModel
    char* map_KdPath;
    char* map_KaPath;
    char* map_KsPath;
    char* map_KePath;
    char* map_KtPath;
    char* map_NsPath;
    char* map_reflPath;
    char* map_BumpPath;

}material;

typedef struct{
    int index;
    char* materialName;
    material* materialObject;

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
    char* mtlPath;

    //bounding box values
    float minX;
    float minY;
    float minZ;

    float maxX;
    float maxY;
    float maxZ;
}object;



