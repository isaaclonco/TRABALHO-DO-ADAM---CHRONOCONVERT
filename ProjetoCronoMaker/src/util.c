// src/util.c (fully ASCII-safe: no box-drawing, simple borders)
#include "util.h"
#include <stdio.h>
#include <stdlib.h>
#include <ctype.h>
#include <time.h>      // For time() and ctime()
#include <string.h>    // For strlen()

#ifdef _WIN32
#include <windows.h>
#define SLEEP_MS(ms) Sleep(ms)
#else
#include <unistd.h>
#define SLEEP_MS(ms) usleep((ms) * 1000)
#endif

void habilitar_ansi_windows() {
#ifdef _WIN32
    HANDLE hOut = GetStdHandle(STD_OUTPUT_HANDLE);
    DWORD dwMode;
    GetConsoleMode(hOut, &dwMode);
    dwMode |= ENABLE_VIRTUAL_TERMINAL_PROCESSING;
    SetConsoleMode(hOut, dwMode);
#endif
}

double horasParaMinutos(double horas) { return horas * 60; }
double minutosParaSegundos(double minutos) { return minutos * 60; }
double segundosParaHoras(double segundos) { return segundos / 3600; }
double horasParaSegundos(double horas) { return horas * 3600; }
double minutosParaHoras(double minutos) { return minutos / 60; }
double segundosParaMinutos(double segundos) { return segundos / 60; }

void limpar_stdin() {
    int c;
    while ((c = getchar()) != '\n' && c != EOF);
}

void limparTela() {
#ifdef _WIN32
    system("cls");
#else
    system("clear");
#endif
}

void pausar() {
    printf(AMARELO "\nPressione ENTER para continuar..." RESET);
    while(getchar() != '\n');
    getchar();
}

double lerNumeroPositivo(char *mensagem) {
    double num;
    do {
        printf("%s", mensagem);
        if (scanf("%lf", &num) != 1 || num < 0) {
            printf(VERMELHO "Valor invalido! Digite um numero positivo.\n" RESET);
            limpar_stdin();
        } else {
            break;
        }
    } while(1);
    return num;
}

void exibirCabecalho() {
    time_t now = time(NULL);
    char *time_str = ctime(&now);
    time_str[strlen(time_str)-1] = '\0';  // Remove newline

    // Simple ASCII Art Title: CRONOMAKER (clean and aligned)
    printf(BOLD AZUL);
    printf("  ___           _    _   _            ___  _           _     \n");
    printf(" / _ \\         | |  | | (_)          / _ \\| |         | |    \n");
    printf("| | | | ___  ___| |_ | |_ _  ___    | | | | |__   ___ | |_   \n");
    printf("| | | |/ _ \\/ __| __|| __| |/ _ \\   | | | | '_ \\ / _ \\| __|  \n");
    printf("| |_| |  __/\\__ \\ |_ | |_| |  __/   | |_| | | | | (_) | |_   \n");
    printf(" \\___/ \\___||___/\\__| \\__|_|\\___|   \\___/|_| |_|\\___/ \\__|  \n");
    printf(RESET);

    // Simple ASCII borders
    printf(CIANO "\n" RESET);
    for(int i = 0; i < 63; i++) printf("-");
    printf("\n" CIANO "| " RESET AZUL "   Tempo em Suas Mao   " CIANO " |" RESET "\n");
    for(int i = 0; i < 63; i++) printf("-");
    printf("\n" CIANO "| " RESET VERDE "Conversoes de Tempo" CIANO "                 |" RESET "\n");
    for(int i = 0; i < 63; i++) printf("-");
    printf("\n" VERDE "| [1] Horas -> Minutos     [4] Horas -> Segundos |" RESET "\n");
    printf(VERDE "| [2] Minutos -> Segundos  [5] Minutos -> Horas  |" RESET "\n");
    printf(AMARELO "| [3] Segundos -> Horas    [6] Segundos -> Minutos |" RESET "\n");
    for(int i = 0; i < 63; i++) printf("-");
    printf("\n" CIANO "| " RESET MAGENTA "Gerenciamento de Historico" CIANO "       |" RESET "\n");
    for(int i = 0; i < 63; i++) printf("-");
    printf("\n" MAGENTA "| [7] Ver Historico       [8] Pesquisar     |" RESET "\n");
    printf(VERMELHO "| [9] Limpar Todo         [10] Salvar       |" RESET "\n");
    for(int i = 0; i < 63; i++) printf("-");
    printf("\n" CIANO "| [0] Sair                                        |" RESET "\n");
    for(int i = 0; i < 63; i++) printf("-");
    printf("\n" RESET);

    printf(CIANO "Agora: %s\n" RESET, time_str);
}