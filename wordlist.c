#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <dirent.h>
#include <sys/stat.h>
#include <sys/types.h>
#include <unistd.h>
#include <errno.h>
#include <ctype.h>

#define TAM_NAMEF 256
#define TAM_HASH 2048

struct dictionary{
    char *word;
    char *val;
    struct dictionary *nest;
}

void main(int argc, char *argv[]){
    DIR *dir;
    char *path;
    char str[TAM_NAMEF];
    struct dirent *dir_files;
    FILE *entry, *output;
    struct dictionary *dic[HASHSIZE];

    if(argc < 2){
        printf("Entrada incorreta.\n\n");
        printf("Um dos parametros necessários esta ausente, siga o modelo:\n");
        printf("./<nome do programa> <path do diretorio>\n");
        exit(0);
    }

    path = argv[1];

    if((dir = opendir(path)) == NULL){
        fprintf(stderr, "Erro: Nao é possivel abrir este diretorio %s.\n", path);
        exit(0); 
    }

    output = fopen("dicionario.txt", "wb");
    if(output == NULL){ 
        printf("Erro: Nao foi possivel criar o arquivo de saida\n");
        exit(0);
    }
    
    while(dir_files = readdir(dir)){
        if(!strcmp(dir_files->d_name, "."))
            continue;
        if(!strcmp(dir_files->d_name, ".."))
            continue;
        
        strcpy(str, path);
        strcat(str, "/");
        strcat(str, dir_files->d_name);
        
        entry = fopen(str, "r+");
        if(entry == NULL){
            printf("Erro: Nao foi possivel abrir o arquivo\n");
            fclose(output);
            exit(0);
        }

        printf("Abri o arquivo =)\n");
        fclose(entry);
    }    
    fclose(output);
}
