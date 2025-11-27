// include/util.h
#ifndef UTIL_H
#define UTIL_H

// Enhanced ANSI Colors
#define RESET       "\033[0m"
#define BOLD        "\033[1m"
#define AZUL        "\033[94m"
#define VERDE       "\033[92m"
#define AMARELO     "\033[93m"
#define VERMELHO    "\033[91m"
#define CIANO       "\033[96m"
#define MAGENTA     "\033[95m"
#define YELLOW      AMARELO
#define GREEN       VERDE
#define BLUE        AZUL
#define RED         VERMELHO
#define CYAN        CIANO

void habilitar_ansi_windows();

double horasParaMinutos(double horas);
double minutosParaSegundos(double minutos);
double segundosParaHoras(double segundos);
double horasParaSegundos(double horas);
double minutosParaHoras(double minutos);
double segundosParaMinutos(double segundos);

void limpar_stdin();
void limparTela();
void pausar();
double lerNumeroPositivo(char *mensagem);
void exibirCabecalho();

#endif