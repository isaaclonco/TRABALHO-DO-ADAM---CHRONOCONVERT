#include "../include/platform.h"
#include "../include/util.h"
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <locale.h>
#include <time.h>

void habilitar_ansi_windows(void) {
#ifdef _WIN32
    HANDLE hOut = GetStdHandle(STD_OUTPUT_HANDLE);
    if (hOut != INVALID_HANDLE_VALUE) {
        DWORD dwMode = 0;
        GetConsoleMode(hOut, &dwMode);
        dwMode |= ENABLE_VIRTUAL_TERMINAL_PROCESSING;
        SetConsoleMode(hOut, dwMode);
    }
    SetConsoleOutputCP(CP_UTF8);
    SetConsoleCP(CP_UTF8);
    setlocale(LC_ALL, ".UTF8");
#else
    setlocale(LC_ALL, "");
#endif
}

void desenharLinhaDupla(int largura) {
    printf("  ");
    for(int i = 0; i < largura; i++) printf("═");
    printf("\n");
}
void desenharLinhaSimples(int largura) {
    printf("  ");
    for(int i = 0; i < largura; i++) printf("─");
    printf("\n");
}
void desenharLinhaPontilhada(int largura) {
    printf("  ");
    for(int i = 0; i < largura; i++) printf(i % 2 == 0 ? "·" : " ");
    printf("\n");
}


void exibirCabecalho(void) {
    limparTela();
    printf("\n");
    desenharLinhaDupla(LARGURA_CAIXA);
    printf(BOLD CIANO "\n");
    printf("   ██████╗██████╗  ██████╗ ███╗   ██╗ ██████╗ ███╗   ███╗ █████╗ ██╗  ██╗███████╗██████╗ \n");
    printf("  ██╔════╝██╔══██╗██╔═══██╗████╗  ██║██╔═══██╗████╗ ████║██╔══██╗██║ ██╔╝██╔════╝██╔══██╗\n");
    printf("  ██║     ██████╔╝██║   ██║██╔██╗ ██║██║   ██║██╔████╔██║███████║█████╔╝ █████╗  ██████╔╝\n");
    printf("  ██║     ██╔══██╗██║   ██║██║╚██╗██║██║   ██║██║╚██╔╝██║██╔══██║██╔═██╗ ██╔══╝  ██╔══██╗\n");
    printf("  ╚██████╗██║  ██║╚██████╔╝██║ ╚████║╚██████╔╝██║ ╚═╝ ██║██║  ██║██║  ██╗███████╗██║  ██║\n");
    printf("   ╚═════╝╚═╝  ╚═╝ ╚═════╝ ╚═╝  ╚═══╝ ╚═════╝ ╚═╝     ╚═╝╚═╝  ╚═╝╚═╝  ╚═╝╚══════╝╚═╝  ╚═╝\n");
    printf(RESET);
    desenharLinhaDupla(LARGURA_CAIXA);
                                                                                                     

    char agora[64];
    time_t t = time(NULL);
    struct tm *tm_info = localtime(&t);
    strftime(agora, sizeof(agora), "%d/%m/%Y %H:%M:%S", tm_info);
    printf(BOLD LARANJA "                           CRONOMAKER – Conversor de Tempo   ");
    printf(BOLD CIANO "%s\n" RESET, agora);

    printf(DIM    "                                   Projeto em Linguagem C - 2025\n" RESET);
    desenharLinhaDupla(LARGURA_CAIXA);
}

void exibirMenu(void) {
    printf("\n");
    printf(BOLD VERDE "  ╔════════════════════════════════════════════════════════════════════════════════════════╗\n" RESET);
    printf(BOLD VERDE "  ║" RESET BOLD BRANCO "                                MENU DE OPÇÕES                                          " BOLD VERDE "║\n" RESET);
    printf(BOLD VERDE "  ╠════════════════════════════════════════════════════════════════════════════════════════╣\n" RESET);
    printf(BOLD VERDE "  ║" RESET "   " BOLD AMARELO "[1]" RESET "  Conversões de Tempo (Horas/Minutos/Segundos)                                    " BOLD VERDE "║\n" RESET);
    printf(BOLD VERDE "  ║" RESET "   " BOLD AZUL    "[2]" RESET "  Ver Histórico Completo                                                          " BOLD VERDE "║\n" RESET);
    printf(BOLD VERDE "  ║" RESET "   " BOLD CIANO   "[3]" RESET "  Pesquisar Histórico por Tipo                                                    " BOLD VERDE "║\n" RESET);
    printf(BOLD VERDE "  ║" RESET "   " BOLD ROXO    "[4]" RESET "  Cronômetro                                                                      " BOLD VERDE "║\n" RESET);
    printf(BOLD VERDE "  ║" RESET "   " BOLD LARANJA "[5]" RESET "  Salvar Histórico em Arquivo                                                     " BOLD VERDE "║\n" RESET);
    printf(BOLD VERDE "  ║" RESET "   " BOLD VERMELHO "[6]" RESET "  Apagar/Limpar Histórico                                                         " BOLD VERDE "║\n" RESET);
    printf(BOLD VERDE "  ║" RESET "   " BOLD VERDE   "[0]" RESET "  Sair                                                                            " BOLD VERDE "║\n" RESET);
    printf(BOLD VERDE "  ╚════════════════════════════════════════════════════════════════════════════════════════╝\n" RESET);
}

void exibirRodape(void) {
    desenharLinhaPontilhada(LARGURA_CAIXA);
    printf(DIM "  Desenvolvido por: Isaac, Desmond, Gustavo, Hugo — UCB/2025\n" RESET);
    desenharLinhaPontilhada(LARGURA_CAIXA);
}

double horasParaMinutos(double horas) { return horas * 60.0; }
double minutosParaSegundos(double minutos) { return minutos * 60.0; }
double segundosParaHoras(double segundos) { return segundos / 3600.0; }
double horasParaSegundos(double horas) { return horas * 3600.0; }
double minutosParaHoras(double minutos) { return minutos / 60.0; }
double segundosParaMinutos(double segundos) { return segundos / 60.0; }

void limpar_stdin(void) {
    int c; while ((c = getchar()) != '\n' && c != EOF);
}

void limparTela(void) {
#ifdef _WIN32
    system("cls");
#else
    system("clear");
#endif
}

void pausar(void) {
    printf(DIM "\n  Pressione ENTER para continuar..." RESET);
    getchar();
}

double lerNumeroPositivo(const char *mensagem) {
    double num;
    int valido = 0;
    do {
        printf("%s", mensagem);
        if (scanf("%lf", &num) != 1) {
            printf("\n" BOLD VERMELHO "  ✗ ERRO: Entrada inválida! Digite um número.\n" RESET);
            limpar_stdin();
            continue;
        }
        if (num < 0) {
            printf("\n" BOLD VERMELHO "  ✗ ERRO: O valor deve ser positivo!\n" RESET);
            limpar_stdin();
            continue;
        }
        valido = 1;
        limpar_stdin();
    } while (!valido);

    return num;
}

void caixa(const char *titulo) {
    int len = strlen(titulo);
    int larg = LARGURA_CAIXA;
    int padding = (larg - 2 - len) / 2;
    desenharLinhaDupla(larg);
    printf("  ");
    for (int i = 0; i < padding; i++) printf(" ");
    printf("%s", titulo);
    for (int i = 0; i < larg - 2 - len - padding; i++) printf(" ");
    printf("\n");
    desenharLinhaDupla(larg);
}