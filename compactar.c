#include <stdlib.h>
#include <stdio.h>
#include <string.h>

int compactar(char *filename);

int main(int argc, char *argv[]){
    compactar(argv[1]);
    return 1;
}

int compactar(char *filename){
    FILE *file = fopen(filename, "r+");
    if (file == NULL){
        perror("Error");
        return (-1);
    }
    int i = 0;
    int j = 0;
    fseek(file, 0 , SEEK_END);
    int sizeBytes = ftell(file);
    int nlines = sizeBytes/20;
    char z;
    while (1){
        char *buff = malloc(20 + 1);
        if (i == nlines){
            free(buff);
            break;
        }
        fseek(file, i*20, SEEK_SET);
        z = getc(file);
        if (z == ' '){
            i++;
        }
        if (z != ' ' && z!= -1){
            fseek(file, i*20, SEEK_SET);
            fread(buff, 20, 1, file);
            fseek(file, j*20, SEEK_SET);
            fwrite(buff, 20, 1, file);
            i++;
            j++;
        }
        free(buff);
    }
    char *nada= malloc(20 + 1);
    strcpy(nada, "                   \n");
    for(;;){
        if (j == nlines){
            break;
        }
        fseek(file, j*20, SEEK_SET);
        fwrite(nada, 20, 1, file);
        j++;
    }
    free(nada);
    fclose(file);
    return 1;
}
