// src/tarefas.c (updated table with simple ASCII borders)
#include "tarefas.h"
#include "util.h"
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <ctype.h>  // For tolower

#ifdef _WIN32
#include <windows.h>
#define SLEEP_MS(ms) Sleep(ms)
#else
#include <unistd.h>
#define SLEEP_MS(ms) usleep((ms) * 1000)
#endif

#include <time.h>      // For time(), localtime(), strftime()

Conversao *historico = NULL;
int totalConversoes = 0;
int capacidade = 5;

void adicionarNoHistorico(const char *tipo, double original, double convertido) {
    if (totalConversoes >= capacidade) {
        expandirHistorico();
    }
    
    historico[totalConversoes].id = totalConversoes + 1;
    strcpy(historico[totalConversoes].tipo, tipo);
    historico[totalConversoes].valorOriginal = original;
    historico[totalConversoes].valorConvertido = convertido;
    obterDataAtual(historico[totalConversoes].data);
    
    totalConversoes++;
    printf(GREEN "\nConversao salva no historico!\n" RESET);
}

void listarHistorico() {
    if(totalConversoes == 0) {
        printf(YELLOW "\nHistorico vazio. Faca uma conversao primeiro!\n" RESET);
        return;
    }
    printf(BLUE "\n" RESET);
    for(int i = 0; i < 55; i++) printf("-");
    printf("\n" BLUE "| " RESET "                     Historico de Conversoes                  " BLUE "|" RESET "\n");
    for(int i = 0; i < 55; i++) printf("-");
    printf("\n" BLUE "| ID | Tipo                              | Original -> Convertido |" RESET "\n");
    for(int i = 0; i < 55; i++) printf("-");
    for(int i = 0; i < totalConversoes; i++) {
        printf(BLUE "|" RESET " %2d " BLUE "| %-30s | %10.2f -> %10.2f |" RESET "\n",
               historico[i].id,
               historico[i].tipo,
               historico[i].valorOriginal,
               historico[i].valorConvertido);
    }
    for(int i = 0; i < 55; i++) printf("-");
    printf("\n" RESET);
}

void limparHistorico() {
    totalConversoes = 0;
    printf(GREEN "\nHistorico limpo! Tudo zerado.\n" RESET);
}

void menuPesquisar() {
    if(totalConversoes == 0) {
        printf(YELLOW "\nNada para pesquisar. Historico vazio!\n" RESET);
        return;
    }

    char termo[30];
    printf(YELLOW "\nDigite o termo para buscar (no tipo): " RESET);
    scanf(" %[^\n]", termo);

    // Simple animation: dots growing (ASCII)
    printf(BLUE "\nProcurando" RESET);
    for(int i = 0; i < 5; i++) {
        for(int j = 0; j <= i; j++) printf(".");
        fflush(stdout);
        SLEEP_MS(300);
        for(int j = 0; j < i; j++) printf("\b \b");
    }
    printf("\b \b" RESET);  // Clear

    int encontrados = 0;
    printf(GREEN "\nResultados:\n" RESET);
    for(int i = 0; i < 55; i++) printf("=");
    printf("\n");
    for(int i = 0; i < totalConversoes; i++) {
        // Simple case-insensitive search (lowercase compare)
        char tipo_lower[30], termo_lower[30];
        strcpy(tipo_lower, historico[i].tipo);
        strcpy(termo_lower, termo);
        for(int j=0; tipo_lower[j]; j++) tipo_lower[j] = tolower(tipo_lower[j]);
        for(int j=0; termo_lower[j]; j++) termo_lower[j] = tolower(termo_lower[j]);
        if(strstr(tipo_lower, termo_lower) != NULL) {
            printf(GREEN "- ID:%d | %s | %.2f -> %.2f (%s)\n" RESET,
                   historico[i].id,
                   historico[i].tipo,
                   historico[i].valorOriginal,
                   historico[i].valorConvertido,
                   historico[i].data);
            encontrados++;
        }
    }
    for(int i = 0; i < 55; i++) printf("=");
    printf("\n" RESET);

    if(encontrados == 0) {
        printf(RED "\nNenhum resultado para '%s'.\n" RESET, termo);
    } else {
        printf(GREEN "\n%d resultado(s) encontrado(s)!\n" RESET, encontrados);
    }
}

void inicializarHistorico() {
    historico = (Conversao*)malloc(capacidade * sizeof(Conversao));
    
    if(historico == NULL) {
        printf("ERRO: Nao foi possivel alocar memoria!\n");
        exit(1);
    }
}

void expandirHistorico() {
    capacidade = capacidade * 2;
    Conversao *novo = (Conversao*)realloc(historico, capacidade * sizeof(Conversao));
    
    if(novo == NULL) {
        printf("ERRO: Nao foi possivel expandir historico!\n");
        exit(1);
    }
    
    historico = novo;
}

void liberarMemoria() {
    free(historico);
    historico = NULL;
}

void obterDataAtual(char *buffer) {
    time_t now = time(NULL);
    struct tm *local = localtime(&now);
    strftime(buffer, 20, "%Y-%m-%d %H:%M", local);
}