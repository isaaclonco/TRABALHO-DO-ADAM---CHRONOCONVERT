// src/io.c (updated with better error reporting)
#include "tarefas.h"
#include "util.h"
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <errno.h>  // For errno and perror

#ifdef _WIN32
#include <windows.h>
#include <direct.h>  // For _mkdir
#include <io.h>      // For access()
#define ACCESS_MODE F_OK  // Check if file exists
#else
#include <sys/stat.h>  // For mkdir
#include <unistd.h>    // For access()
#define ACCESS_MODE F_OK
#endif

// Helper function to create directory if needed
static void criarDiretorio(const char* dir) {
#ifdef _WIN32
    if (_mkdir(dir) == -1 && errno != EEXIST) {
        printf(RED "\nErro ao criar diretorio %s: %s\n" RESET, dir, strerror(errno));
    }
#else
    if (mkdir(dir, 0755) == -1 && errno != EEXIST) {
        printf(RED "\nErro ao criar diretorio %s: %s\n" RESET, dir, strerror(errno));
    }
#endif
}

void salvarArquivo() {
    // Create 'data' directory if it doesn't exist
    criarDiretorio("data");

    // Check if directory exists and is writable
    if (access("data", W_OK) != 0) {
        printf(RED "\nDiretorio 'data' nao existe ou nao tem permissao de escrita!\n" RESET);
        return;
    }

    FILE *fp = fopen("data/historico.txt", "w");
    if (!fp) {
        printf(RED "\nErro ao abrir 'data/historico.txt' para escrita: %s\n" RESET, strerror(errno));
        return;
    }

    fprintf(fp, "%d\n", totalConversoes);
    for(int i=0; i<totalConversoes; i++) {
        fprintf(fp, "%d\n%s\n%lf\n%lf\n%s\n",
                historico[i].id,
                historico[i].tipo,
                historico[i].valorOriginal,
                historico[i].valorConvertido,
                historico[i].data);
    }
    fclose(fp);
    printf(GREEN "\nSalvo no arquivo!\n" RESET);
}

void carregarArquivo() {
    // Create 'data' directory if it doesn't exist (for consistency)
    criarDiretorio("data");

    FILE *fp = fopen("data/historico.txt", "r");
    if (!fp) {
        // No error message for load if file doesn't exist yet
        totalConversoes = 0;
        return;
    }

    fscanf(fp, "%d\n", &totalConversoes);
    if(totalConversoes > 0) {
        inicializarHistorico();  // Ensure allocated
        for(int i=0; i<totalConversoes; i++) {
            fscanf(fp, "%d\n", &historico[i].id);
            fgets(historico[i].tipo, 30, fp);
            historico[i].tipo[strcspn(historico[i].tipo, "\n")] = 0;
            fscanf(fp, "%lf\n", &historico[i].valorOriginal);
            fscanf(fp, "%lf\n", &historico[i].valorConvertido);
            fgets(historico[i].data, 20, fp);
            historico[i].data[strcspn(historico[i].data, "\n")] = 0;
        }
    }
    fclose(fp);
}