#include <stdio.h>
#include <stdlib.h>
#include <ctype.h>
#include <string.h>
#include <math.h>
#include <openssl/md5.h>
#include <openssl/hmac.h>

#define TAM_KEY 61
#define TAM_ENTRY 256

void append(char* s, char c)
{
        int len = strlen(s);
        s[len] = c;
        s[len+1] = '\0';
}

unsigned char* generateHexDigits(unsigned char *cadeia, unsigned char *hex[], int tam){
    int i=0, lenght1, lenght2;
    char aux[3];
    char digit[4];
    unsigned char *buffer = "0x";
    
    memset(hex, 0, tam);

    if(strlen(cadeia) != (tam*2)){
        printf("Cadeia de caracteres está incompleta.\n");
        exit(1);
    }
    if(strlen(cadeia) % 2 == 0){
        while(*cadeia !='\0'){
            memset(aux, 0, 3);
            memset(digit, 0, 4);
            strncpy(aux, cadeia, 2);
            strcat(digit, buffer);
            strcat(digit, aux);
            hex[i] = strdup(digit);
            cadeia += 2;
            i += 1;
        }
    }
    
}

void hexTochar(unsigned char *cadeiaHex[], char cadeiaChar[]){
    int i = 0;
    int myChar;
    const char *hex;

    while (i < 20) {
        if(isxdigit(*cadeiaHex[i])){
            hex = cadeiaHex[i];
            myChar = (int)strtol(hex, NULL, 0);
            cadeiaChar[i] = myChar;
            i+=1;
        }else{
         exit(0);
        }
        
    }
}

int iterate(char *str, const char *base[], int idx, int len, unsigned char *md5Key[], int *found, char *chave) {
    unsigned char result[MD5_DIGEST_LENGTH];
    const char *hex;
    char c;
    int i, j, myChar, contB=1;
    
    if (idx < (len - 1)) {
        for (i = 0; i < TAM_KEY; ++i) {
            str[idx] = *base[i];
            if(*found == 0){
                iterate(str, base, idx + 1, len, md5Key, found, chave);
            }else{
                return 1;
            }
        }
    } else {
        for (i = 0; i < TAM_KEY; ++i) {
            str[idx] = *base[i];
            
            MD5(str, strlen(str), result);
            
            for(j = 0; j < MD5_DIGEST_LENGTH; j++){
                
                if(isxdigit(*md5Key[j])){
                    hex = md5Key[j];
                    myChar = (int)strtol(hex, NULL, 0);
                    if(result[j] == myChar){
                        contB += 1;
                        if(contB == MD5_DIGEST_LENGTH){
                            *found = 1;
                            strcpy(chave, str);
                            break;
                        }
                    }else{
                        break;
                    }
                }
            }
        }
    }
    return 0;
}

void keyGenerator(unsigned char *md5[], unsigned int len, char chave[]){
    const char *keysU[TAM_KEY] = {"A","B","C","D","E","F","G","H","I","J","K","L","M","N","O","P","Q","R","S","T","U","V","X","W","Y","Z","a","b","c","d","e","f","g","h","i","j","k","l","m","n","o","p","q","r","s","t","u","v","x","w","y","z", "0","1","2","3","4","5","6","7","8","9"};
    int i, found = 0, search = 0;

    char concat[8];
    
    memset(concat, 0, 8);

    found = iterate(concat, keysU, 0, len, md5, &search, chave);
    
    if(!found){
        printf("Chave Não encontrada.\n");
        exit(1);
    }

}

void xorCipher(char cadeia[], char chave[]){
    int i, j = 0;
    int digit;
    unsigned char buffer[20];
    
    for(i=0; i < 20; i++) {
        if(j >= strlen(chave)){
            j = 0;
        }
        
        digit = cadeia[i] ^ chave[j];
        if(digit < 32){
            digit += 32;
        }
        buffer[i] = digit;
        printf("%c", buffer[i]);
        j++;
    }
    printf("\n");
}

void main(int argc, char *argv[]) {;
    unsigned char *cadeiaHex[20] = {0};
    unsigned char *cadeiaMd5[20] = {0};
    unsigned char *digitHex = malloc(TAM_ENTRY);
    unsigned char *digitMd5 = malloc(TAM_ENTRY);
    char cadeiaChar[20] = {0};
    char cadeiaFinal[] ={0};
    char chave[2];
    int tamCHex = 20;
    unsigned int len;
    int i;
    
    if(argc < 4){
        printf("Entrada incorreta.\n\n");
        fflush(stdout);
        printf("Siga o modelo: ./<nome do programa> <digitos hexadecimais sem espaço> <hash md5> <tamanho da chave>\n");
        fflush(stdout);
        exit(0);
    }
    
    strcpy(digitHex, argv[1]);
    strcpy(digitMd5, argv[2]);
    len = atoi(argv[3]);
    
    memset(chave, 0, 2);
    
    generateHexDigits(digitHex, cadeiaHex, 20);
    generateHexDigits(digitMd5, cadeiaMd5, 16);

    hexTochar(cadeiaHex, cadeiaChar);
    keyGenerator(cadeiaMd5, len, chave);
    
    printf("chave: %s \n", chave);
    
    xorCipher(cadeiaChar, chave);
}
