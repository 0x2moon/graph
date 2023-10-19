#include <stdio.h>
#include <stdlib.h>
#include <string.h>

int main() {
    int ctrlName = 0;
    char name;
    char *nname = NULL;
    FILE *file = fopen("text.dot", "r"); // Substitua "seuarquivo.txt" pelo nome do seu arquivo.

    if (file == NULL) {
        perror("Erro ao abrir o arquivo");
        return 1;
    }

    while (fread(&name, sizeof(char), 1, file)) {
        if (name != '\n') {
            ctrlName++;
            char temp[2] = {name, '\0'};
            if (nname == NULL) {
                nname = strdup(temp); // Aloca memória e copia o primeiro caractere
            } else {
                char *new_name = malloc(strlen(nname) + 2); // Aloca memória para o novo tamanho
                strcpy(new_name, nname); // Copia a string atual para o novo espaço
                strcat(new_name, temp); // Concatena o novo caractere
                free(nname); // Libera a memória da string anterior
                nname = new_name; // Aponta para a nova string
            }
        } else {
            break;
        }
    }

    fclose(file);

    // Agora você tem a string nname com os caracteres lidos.
    if (nname != NULL) {
        printf("String lida: %s\n", nname);
        free(nname); // Libera a memória alocada para a string
    }

    return 0;
}
