int size(){
    int size = 0;
    FILE* file = fopen(path, "r");
    if(file == NULL){
        printf("no file :(");
        fclose(file);
        return;
    }
    char buf[100];
    while(fgets(buf, sizeof(buf), file)) {
        char temp[10];
        for(int i = 0; i < 10; ++i){
            if(buf[i] == ' ' || buf[i] == '#'){
                break;
            }
            temp[i] = buf[i];
        }
        //vertex
        if(strcmp(temp, "newmtl") == 0){
            size++;
        }
        memset(buf, 0, sizeof(buf));
        memset(temp, 0, sizeof(temp));
    }
    return size;
}