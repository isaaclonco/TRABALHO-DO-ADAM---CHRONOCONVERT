// include/tarefas.h
#ifndef TAREFAS_H
#define TAREFAS_H

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
void listarHistorico();
void limparHistorico();
void menuPesquisar();
void inicializarHistorico();
void expandirHistorico();
void liberarMemoria();
void obterDataAtual(char *buffer);

#endif