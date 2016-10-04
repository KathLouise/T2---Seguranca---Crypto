//-------------------------------------------------------------------//
// UNIVERSIDADE FEDERAL DO PARANÁ                                    //
// KATHERYNE LOUISE GRAF     GRR:20120706   IDENTIFICADOR: KLG12     //
// CI301 - INTRODUÇÃO À SEGURANÇA COMPUTACIONAL                      //
//-------------------------------------------------------------------//
// BIBLIOTECAS
//-------------------------------------------------------------------//

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <dirent.h>
#include <sys/stat.h>
#include <sys/types.h>
#include <unistd.h>
#include <errno.h>
#include <ctype.h>

//-------------------------------------------------------------------//
// DEFINES
//-------------------------------------------------------------------//

#define TAM_NAMEF 256
#define TAM_HASH 30000

//-------------------------------------------------------------------//
// ESTRUTURA DA HASH DO DICIONARIO
//-------------------------------------------------------------------//

struct dictionary{
    char *word;
    struct dictionary *next;
};

//-------------------------------------------------------------------//
// VARIAVEL ESTÁTICA
//-------------------------------------------------------------------//

static struct dictionary *hash[TAM_HASH];

//-------------------------------------------------------------------//
// FUNÇÕES
//-------------------------------------------------------------------//
// Esta função calcula o valor o valor hash da palavra passada como
// parametro
// 
// Parametros
// word: palavra que está sendo adicionada ou procurada no dicionario

unsigned value(char *word){
    unsigned hashVal;
    
    for(hashVal = 0; *word != '\0'; word++){
        hashVal = *word + (31 * hashVal);
    }
    return (hashVal % TAM_HASH);
}
//-------------------------------------------------------------------//
// Esta função procura se uma dada palavra, passada como parametro
// esta inserida ou não dentro do dicionario. Se a palavra já estiver
// no dicionario, retorna 1, senão retorna 0
//
// Parametros:
// word: palavra que será verificada se já esta contida ou não no 
//       dicionario

int search(char *word){
    struct dictionary *temp;
    
    for(temp = hash[value(word)]; temp != NULL; temp = temp->next){
        if(strcmp(word, temp->word) == 0){
            return 1;         
        }
    }
    return 0;
}
//-------------------------------------------------------------------//
// Esta função adiciona a palavra passada como paramentro dentro do 
// dicionario, e retorna esste dicionario para que ele fique atualizado
// e seja marcado como existente.
//
// Parametros: 
// word: palavra a ser adicionada ao dicionario

struct dictionary *add(char *word){
    struct dictionary *temp;
    unsigned hashVal;

    temp = (struct dictionary *) malloc(sizeof(*temp));
    if(temp == NULL || (temp->word = strdup(word)) == NULL)
        return NULL;
    hashVal = value(word);
    temp->next = hash[hashVal];
    hash[hashVal] = temp;

    return temp;
}
//-------------------------------------------------------------------//
// Esta função faz a checagem e retirada de caracteres especiais 
// ([,]["][?][!], etc) das palavras.
//
// Parametros:
// word: palavra de entrada para ser feita checagem e retirada de 
//       caracteres especiais, se houver
// wordS: palavra de saida, se caracteres especiais

void particionate(char *word,  char *wordS){
    int i, c = 0;
    
    for(i = 0; i < strlen(word); i++){
        if(!((word[i] >=32) && (word[i] <= 44) || (word[i] >= 46) && (word[i] <= 64) || (word[i] >= 91) && (word[i] <= 95) || (word[i] >= 123) && (word[i] <= 126))){ 
            wordS[c] = word[i];
            c++;
        }
    }
    wordS[c] = '\0';
}
//-------------------------------------------------------------------//
// Função Main
// Dado um path como argumento, checa se o diretorio pode ser acessado,
// se puder, cria um arquivo de saida e tenta acessar todos os arquivos
// .txt, para em cada um deles pegar todas as palavras e tentar 
// adicionar a um dicionario, sem repetir. Se a palavra não for repetida
// já escreve no arquivo de saida, que é um arquivo com todas as 
// palavras contidas no .txt daquele diretorio passado.

void main(int argc, char *argv[]){
    DIR *dir;
    char *path;
    char str[TAM_NAMEF];
    struct dirent *dir_files;
    FILE *entry, *output;
    struct dictionary *dic;
    char word[20];
    char wordF[20];

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

        while(!feof(entry)){
            fscanf(entry, "%s", word);
            particionate(word,  wordF);
                       
            if(dic == NULL || search(wordF) == 0){
                dic = add(wordF);
                fprintf(output, "%s\n", wordF);
            }
        }
        fclose(entry);
    }    
    fclose(output);
}
//-------------------------------------------------------------------//
