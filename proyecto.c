#include <stdio.h>
#include <string.h>
#include <stdbool.h>
#include <ctype.h>

char tipoFlag(char* flag);
bool asignarFlag(char* flag, char* value, char** timeN, char** file, char** pipePSC, bool* f, bool* t, bool* p);
char encontrarTipo(char* tipo);

int main(int argc, char *argv[]) {
    char tipo, *file = NULL, *pipePSC = NULL, *timeN = NULL;
    bool f = false, t = false, p = false;

    if (argc != 8) {
        printf("Numero de argumentos incorrecto\n");
    } else {
        /* Print all arguments for debugging
        for (int i = 0; i < argc; i++) {
            printf("argv[%d]: %s\n", i, argv[i]);
        }
        printf("--------------------\n");*/

        tipo = encontrarTipo(argv[1]);
        if (tipo == 'p' || tipo == 's') {
            // Convertir variable 'tipo' a minuscula
            tipo = tolower(tipo);
            
            for(int i = 2; i < argc; i += 2){
                char flagChar = tipoFlag(argv[i]);
    
                if (flagChar == 't' || flagChar == 'f' || flagChar == 'p') {
                    if (asignarFlag(argv[i], argv[i+1], &timeN, &file, &pipePSC, &f, &t, &p) == false) {
                        printf("Flag repetida\n");
                        return 1;
                    }                    
                }else{
                    printf("Flag incorrecta\n");
                    return 1;
                }
                if (flagChar == 't') {
                    printf("Flag: %c. Valor: %s\n", flagChar, timeN);
                } else if (flagChar == 'f') {
                    printf("Flag: %c. Valor: %s\n", flagChar, file);
                } else if (flagChar == 'p') {
                    printf("Flag: %c. Valor: %s\n", flagChar, pipePSC);
                }
            }
        } else {
            printf("Argumento incorrecto, escoja entre suscriptor y publicador\n");
        }
    }
    return 0;
}

char encontrarTipo(char* tipo){
    if(strcasecmp(tipo, "publicador") == 0){
        return 'p';
    }else if(strcasecmp(tipo, "suscriptor") == 0){
        return 's';
    } else{
        return 'e';
    }
}

char tipoFlag(char* flag){
    if(strcmp(flag, "-t") == 0){
        return 't';
    }else if(strcasecmp(flag, "-f") == 0){
        return 'f';
    }else if(strcasecmp(flag, "-p") == 0){
        return 'p';
    } else{
        return 'e';
    }
}

bool asignarFlag(char* flag, char* value, char** timeN, char** file, char** pipePSC, bool* f, bool* t, bool* p){
    if(strcasecmp(flag, "-t") == 0 && !(*t)){
        *timeN = value;
        *t = true;
        return true;
    }else if(strcasecmp(flag, "-f") == 0 && !(*f)){
        *file = value;
        *f = true;
        return true;
    }else if(strcasecmp(flag, "-p") == 0 && !(*p)){
        *pipePSC = value;
        *p = true;
        return true;
    }
    else{
        printf("Flag repetido\n");
        return false;
    }
}