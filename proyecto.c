#include <stdio.h>
#include <string.h>
#include <stdbool.h>
#include <ctype.h>

char tipoFlag(char* flag);
bool asignarFlag(char* flag, char* value, char** timeN, char** timeF, char** file, char** pipePSC, bool* f, bool* t, bool* p, bool* s);
char encontrarTipo(char* tipo);

int main(int argc, char *argv[]) {
    char tipo, *file = NULL, *pipePSC = NULL, *timeN = NULL, *pipeSSC = NULL, *timeF = NULL;
    bool f = false, t = false, p = false, s = false;

    if (argc < 4) {  // Se ajusta para el mínimo de argumentos
        printf("Numero de argumentos incorrecto\n");
    } else {
        tipo = encontrarTipo(argv[1]);
        if (tipo == 'p') {
            // Convertir variable 'tipo' a minuscula
            tipo = tolower(tipo);
            for (int i = 2; i < argc; i += 2) {
                char flagChar = tipoFlag(argv[i]);

                if (flagChar == 't' || flagChar == 'f' || flagChar == 'p') {
                    if (asignarFlag(argv[i], argv[i + 1], &timeN, &timeF, &file, &pipePSC, &f, &t, &p, &s) == false) {
                        printf("Flag repetida\n");
                        return 1;
                    }
                } else {
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
        } else if (tipo == 's') {
            // Lógica del suscriptor
            for (int i = 2; i < argc; i += 2) {
                char flagChar = tipoFlag(argv[i]);

                if (flagChar == 's') {
                    if (asignarFlag(argv[i], argv[i + 1], &timeN, &timeF, &file, &pipePSC, &f, &t, &p, &s) == false) {
                        printf("Flag repetida\n");
                        return 1;
                    }
                } else {
                    printf("Flag incorrecta para el suscriptor\n");
                    return 1;
                }

                if (flagChar == 's') {
                    printf("Suscriptor escuchando en pipe: %s\n", pipePSC);
                    // Aquí podrías agregar la lógica para leer datos desde la tubería `pipeSSC`
                }
            }
        } else if (tipo == 'c') {
            for (int i = 2; i < argc; i += 2) {
                char flagChar = tipoFlag(argv[i]);

                if (flagChar == 'p' || flagChar == 's' || flagChar == 't') {
                    if (asignarFlag(argv[i], argv[i + 1], &timeN, &timeF, &file, &pipePSC, &f, &t, &p, &s) == false) {
                        printf("Flag repetida\n");
                        return 1;
                    }
                } else {
                    printf("Flag incorrecta\n");
                    return 1;
                }

                if (flagChar == 't') {
                    printf("Flag: %c. Valor: %s\n", flagChar, timeF);
                } else if (flagChar == 'f') {
                    printf("Flag: %c. Valor: %s\n", flagChar, pipePSC);
                } else if (flagChar == 'p') {
                    printf("Flag: %c. Valor: %s\n", flagChar, pipeSSC);
                }
            }
        } else {
            printf("Argumento incorrecto, escoja entre suscriptor y publicador\n");
        }
    }
    return 0;
}

char encontrarTipo(char* tipo) {
    if (strcasecmp(tipo, "publicador") == 0) {
        return 'p';
    } else if (strcasecmp(tipo, "suscriptor") == 0) {
        return 's';
    } else if (strcasecmp(tipo, "sistema") == 0) {
        return 'c';
    } else {
        return 'e';
    }
}

char tipoFlag(char* flag) {
    if (strcmp(flag, "-t") == 0) {
        return 't';
    } else if (strcasecmp(flag, "-f") == 0) {
        return 'f';
    } else if (strcasecmp(flag, "-p") == 0) {
        return 'p';
    } else if (strcasecmp(flag, "-s") == 0) {
        return 's';  // Flag para el suscriptor
    } else {
        return 'e';
    }
}

bool asignarFlag(char* flag, char* value, char** timeN, char** timeF, char** file, char** pipePSC, bool* f, bool* t, bool* p, bool* s) {
    if (strcasecmp(flag, "-t") == 0 && !(*t)) {
        *timeN = value;
        *timeF = value;
        *t = true;
        return true;
    } else if (strcasecmp(flag, "-f") == 0 && !(*f)) {
        *file = value;
        *f = true;
        return true;
    } else if (strcasecmp(flag, "-p") == 0 && !(*p)) {
        *pipePSC = value;
        *p = true;
        return true;
    } else if (strcasecmp(flag, "-s") == 0 && !(*s)) {
        *pipePSC = value;
        *s = true;
        return true;
    } else {
        printf("Flag repetido\n");
        return false;
    }
}
