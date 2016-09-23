#include <stdio.h>
#include <stdlib.h>
#include <ctype.h>
#include <string.h>
#include <openssl/md5.h>
#include <openssl/hmac.h>

void append(char* s, char c)
{
        int len = strlen(s);
        s[len] = c;
        s[len+1] = '\0';
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
           // printf("char: %c\n", cadeiaChar[i]);
            i+=1;
        }else{
         exit(0);
        }
        
    }
}


char* iterate(char *str, const char *base[], int idx, int len, int *getKey) {
    unsigned char *md5Key[MD5_DIGEST_LENGTH] = {"0x8d","0x7b","0x35","0x6e","0xae","0x43","0xad","0xcd","0x6a","0xd3","0xee","0x12","0x4c","0x3d","0xcf","0x1e"};
    unsigned char result[MD5_DIGEST_LENGTH];
    const char *hex;
    char c;
    int i, j, myChar, contB=1;
    
    if (idx < (len - 1)) {
        for (i = 0; i < 61; ++i) {
            str[idx] = *base[i];

            iterate(str, base, idx + 1, len, getKey);
        }
    } else {
        for (i = 0; i < 61; ++i) {
            str[idx] = *base[i];
            MD5(str, strlen(str), result);
            
            for(j = 0; j < MD5_DIGEST_LENGTH; j++){
                if(isxdigit(*md5Key[j])){
                    hex = md5Key[j];
                    myChar = (int)strtol(hex, NULL, 0);
                    if(result[j] == myChar){
                        contB += 1;
                        if(contB == MD5_DIGEST_LENGTH){
                            *getKey = 1;
                            return str;
                        }
                    }else{
                        break;
                    }
                }
           }
        }
    }
}

void keyGenerator(){
    const char *keysU[61] = {"a","b","c","d","e","f","g","h","i","j","k","l","m","n","o","p","q","r","s","t","u","v","x","w","y","z","A","B","C","D","E","F","G","H","I","J","K","L","M","N","O","P","Q","R","S","T","U","V","X","W","Y","Z","1","2","3","4","5","6","7","8","9"};
    //const char teste[] = "FACIL";
    int i, getKey = 0;
    const char *keysC;

    char *chave;
    char concat[8];
    
    for(i = 0; i < 8; i++){
        memset(concat, 0, 8);
        chave = iterate(concat, keysU, 0, i, &getKey);
        if(getKey){
            break;
        }
    }

    printf("%s\n", chave);
    // for (j = 0; j < 61; j++){
    //     MD5(keysU[j], strlen(keysU[j]), result);
     
    //     for(i = 0; i < MD5_DIGEST_LENGTH; i++){
    //         if(isxdigit(*md5Key[i])){
    //             hex = md5Key[i];
    //             myChar = (int)strtol(hex, NULL, 0);
    //             if(result[i] == myChar){
    //                 //printf("oi\n");
    //             }else{
    //               //  printf("naodeu\n");
    //                 break;
    //             }
    //         }
    //     }
    // }
}

int main(int argc, char *argv[]) {
    unsigned char *cadeiaHex[20] = {"0x0b", "0x34", "0x30", "0x20", "0x2f", "0x27", "0x05", "0x22", "0x05", "0x29", "0x21", "0x28", "0x22", "0x26", "0x19", "0x34", "0x23", "0x22", "0x27", "0x2d"};
    char cadeiaChar[20] = {0};
    char cadeiaFinal[] ={0};
    int tamCHex = 20;
    int i;
    
    hexTochar(cadeiaHex, cadeiaChar);
    keyGenerator();
    
    
    // // write
    // for (i = 0 ; i < 20; i++){
    //     //sprintf(cadeiaFinal, "%c", cadeiaChar[i]);
    //     append(cadeiaFinal, cadeiaChar[i]);
    // }
    // printf("%s, \n", cadeiaFinal);

}
