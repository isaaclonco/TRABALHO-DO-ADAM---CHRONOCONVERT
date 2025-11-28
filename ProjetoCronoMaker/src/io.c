#include "../include/platform.h"
#include "../include/io.h"
#include "../include/tarefas.h"
#include "../include/util.h"
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <errno.h>

static int obterCaminhoDados(char *buffer, size_t size) {
    snprintf(buffer, size, "..%cdata", DIR_SEPARATOR);
    return 1;
}

void salvarArquivo(void) {
    char caminhoDados[512];
    char caminhoArquivo[600];

    if (!obterCaminhoDados(caminhoDados, sizeof(caminhoDados))) {
        desenharLinhaSimples(LARGURA_CAIXA);
        printf(BOLD VERMELHO "\n  ✗ ERRO: Não foi possível determinar o diretório de dados\n" RESET);
        desenharLinhaSimples(LARGURA_CAIXA);
        return;
    }

    snprintf(caminhoArquivo, sizeof(caminhoArquivo), "%s%chistorico.txt", 
             caminhoDados, DIR_SEPARATOR);

    FILE *fp = fopen(caminhoArquivo, "w");
    if (!fp) {
        desenharLinhaSimples(LARGURA_CAIXA);
        printf(BOLD VERMELHO "\n  ✗ ERRO ao abrir '%s': %s\n" RESET, caminhoArquivo, strerror(errno));
        desenharLinhaSimples(LARGURA_CAIXA);
        return;
    }

    fprintf(fp, "%d\n", totalConversoes);

    for (int i = 0; i < totalConversoes; i++) {
        fprintf(fp, "%d\n%s\n%.10lf\n%.10lf\n%s\n",
                historico[i].id,
                historico[i].tipo,
                historico[i].valorOriginal,
                historico[i].valorConvertido,
                historico[i].data);
    }

    fclose(fp);
    desenharLinhaDupla(LARGURA_CAIXA);
    printf(BOLD VERDE "\n  ✓ Histórico salvo em arquivo: %s\n" RESET, caminhoArquivo);
    desenharLinhaDupla(LARGURA_CAIXA);
}

void carregarArquivo(void) {
    char caminhoDados[512];
    char caminhoArquivo[600];

    if (!obterCaminhoDados(caminhoDados, sizeof(caminhoDados))) {
        totalConversoes = 0;
        return;
    }

    snprintf(caminhoArquivo, sizeof(caminhoArquivo), "%s%chistorico.txt",
             caminhoDados, DIR_SEPARATOR);

    FILE *fp = fopen(caminhoArquivo, "r");
    if (!fp) {
        totalConversoes = 0;
        return;
    }

    if (fscanf(fp, "%d\n", &totalConversoes) != 1) {
        desenharLinhaSimples(LARGURA_CAIXA);
        printf(BOLD AMARELO "\n  [!] Arquivo corrompido. Histórico vazio.\n" RESET);
        desenharLinhaSimples(LARGURA_CAIXA);
        totalConversoes = 0;
        fclose(fp);
        return;
    }

    if (totalConversoes > 0) {
        historico = malloc(totalConversoes * sizeof(Conversao));
        if (historico == NULL) {
            desenharLinhaSimples(LARGURA_CAIXA);
            printf(BOLD VERMELHO "\n  ✗ Erro ao alocar histórico!\n" RESET);
            desenharLinhaSimples(LARGURA_CAIXA);
            totalConversoes = 0;
            fclose(fp);
            return;
        }

        for (int i = 0; i < totalConversoes; i++) {
            fscanf(fp, "%d\n", &historico[i].id);

            fgets(historico[i].tipo, sizeof(historico[i].tipo), fp);
            historico[i].tipo[strcspn(historico[i].tipo, "\n")] = '\0';

            fscanf(fp, "%lf\n", &historico[i].valorOriginal);
            fscanf(fp, "%lf\n", &historico[i].valorConvertido);

            fgets(historico[i].data, sizeof(historico[i].data), fp);
            historico[i].data[strcspn(historico[i].data, "\n")] = '\0';
        }
    }

    fclose(fp);
}