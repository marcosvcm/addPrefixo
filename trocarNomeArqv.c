#include <stdio.h>
#include <dirent.h>//PARA LER O NOME DOS ARQUIVOS
#include <string.h>

// ESSE PROGRAMA ADICIONA UM PREFIXO AO NOME DOS ARQUIVOS EM UMA PASTA

typedef enum { F, T } boolean;

int main(){
    DIR *folder;
    struct dirent *entrada;
    int files = 0;
    char nomea[100], nomen[100];
    char prefixn[]="prefixo";
    char meuNome[]="trocarN";
    boolean jaTem = F;
    boolean euMesmo = F;

    folder = opendir(".");//ABRINDO PASTA
    //PASTA ATUAL "."
    //PASTA ACIMA ".."
    if(folder == NULL){
        perror("Nao foi possivel ler.");
        return(1);
    }

    while((entrada=readdir(folder))){
        files++;
        strcpy(nomea, entrada->d_name);

        jaTem = T;
        euMesmo = T;
        for(int i = 0; i<sizeof(prefixn)-1; i++){
            if(nomea[i] == prefixn[i]){
                continue;
            }
            jaTem = F;
            break;
        }
        for(int i = 0; i<sizeof(meuNome)-1; i++){
            if(nomea[i] == meuNome[i]){
                continue;
            }
            euMesmo = F;
            break;
        }

        if(jaTem == F && euMesmo == F){
            strcpy(nomen, prefixn);
            strcat(nomen, nomea);
            rename(nomea, nomen);
            printf("Troquei de %s para %s\n", nomea, entrada->d_name);
        }
        printf("File %3d: %s\n", files, entrada->d_name);
    }

    closedir(folder);//FECHANDO PASTA

    return(0);
}
