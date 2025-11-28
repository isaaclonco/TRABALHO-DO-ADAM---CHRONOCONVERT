#ifndef TAREFAS_H
#define TAREFAS_H

#include <time.h>

typedef struct {
    int id;                    
    char tipo[30];            
    double valorOriginal;       
    double valorConvertido;    
    char data[20];              
} Conversao;

extern Conversao *historico;
extern int totalConversoes;

void adicionarNoHistorico(const char *tipo, double original, double convertido);
void listarHistorico(void);
void limparHistorico(void);
void menuPesquisar(void);
int removerConversao(void);
void cronometro(void);
void inicializarHistorico(void);
void expandirHistorico(void);
void liberarMemoria(void);
void obterDataAtual(char *buffer);

void processarConversao(const char *tipo,
                        double (*funcConversao)(double),
                        const char *unidadeOrigem,
                        const char *unidadeDestino);

double horasParaMinutos(double horas);
double minutosParaSegundos(double minutos);
double segundosParaHoras(double segundos);
double horasParaSegundos(double horas);
double minutosParaHoras(double minutos);
double segundosParaMinutos(double segundos);

#endif