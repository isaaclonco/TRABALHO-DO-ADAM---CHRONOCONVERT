#ifndef UTIL_H
#define UTIL_H

#define RESET       "\033[0m"
#define BOLD        "\033[1m"
#define DIM         "\033[2m"
#define AZUL        "\033[38;5;33m"
#define VERDE       "\033[38;5;46m"
#define AMARELO     "\033[38;5;226m"
#define VERMELHO    "\033[38;5;196m"
#define CIANO       "\033[38;5;51m"
#define MAGENTA     "\033[38;5;201m"
#define LARANJA     "\033[38;5;214m"
#define ROXO        "\033[38;5;129m"
#define BRANCO      "\033[97m"

#define LARGURA_CAIXA 100

void habilitar_ansi_windows(void);
void desenharLinhaDupla(int largura);
void desenharLinhaSimples(int largura);
void desenharLinhaPontilhada(int largura);
void exibirCabecalho(void);
void exibirMenu(void);
void exibirRodape(void);

double horasParaMinutos(double horas);
double minutosParaSegundos(double minutos);
double segundosParaHoras(double segundos);
double horasParaSegundos(double horas);
double minutosParaHoras(double minutos);
double segundosParaMinutos(double segundos);

void limpar_stdin(void);
void limparTela(void);
void pausar(void);
double lerNumeroPositivo(const char *mensagem);

void caixa(const char *titulo);

#endif