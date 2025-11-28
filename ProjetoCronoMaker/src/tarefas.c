#include "../include/platform.h"
#include "../include/tarefas.h"
#include "../include/util.h"
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <ctype.h>
#include <time.h>

#ifdef _WIN32
    #include <conio.h>
#endif

Conversao *historico = NULL;
int totalConversoes = 0;
static int capacidade = 5;

void adicionarNoHistorico(const char *tipo, double original, double convertido) {
    if (totalConversoes >= capacidade)
        expandirHistorico();

    historico[totalConversoes].id = totalConversoes + 1;
    strncpy(historico[totalConversoes].tipo, tipo, sizeof(historico[totalConversoes].tipo) - 1);
    historico[totalConversoes].tipo[sizeof(historico[totalConversoes].tipo) - 1] = '\0';

    historico[totalConversoes].valorOriginal = original;
    historico[totalConversoes].valorConvertido = convertido;

    obterDataAtual(historico[totalConversoes].data);

    totalConversoes++;
    desenharLinhaSimples(LARGURA_CAIXA);
    printf(BOLD VERDE "  ✓ Registrado no histórico com sucesso!\n" RESET);
    desenharLinhaSimples(LARGURA_CAIXA);
}

int removerConversao(void) {
    if (totalConversoes == 0) {
        desenharLinhaSimples(LARGURA_CAIXA);
        printf(BOLD AMARELO "  ℹ️  HISTÓRICO VAZIO\n" RESET);
        desenharLinhaSimples(LARGURA_CAIXA);
        return 0;
    }

    int id;
    desenharLinhaDupla(LARGURA_CAIXA);
    printf(BOLD VERMELHO "  REMOVER ITEM DO HISTÓRICO\n" RESET);
    desenharLinhaDupla(LARGURA_CAIXA);

    printf(AMARELO "  Digite o ID a remover: " RESET);

    if (scanf("%d", &id) != 1) {
        limpar_stdin();
        desenharLinhaSimples(LARGURA_CAIXA);
        printf(BOLD VERMELHO "  ✗ ERRO: ID inválido!\n" RESET);
        desenharLinhaSimples(LARGURA_CAIXA);
        return 0;
    }
    limpar_stdin();

    int pos = -1;
    for (int i = 0; i < totalConversoes; i++) {
        if (historico[i].id == id) {
            pos = i;
            break;
        }
    }

    if (pos == -1) {
        desenharLinhaSimples(LARGURA_CAIXA);
        printf(BOLD VERMELHO "  ✗ ERRO: ID não encontrado!\n" RESET);
        desenharLinhaSimples(LARGURA_CAIXA);
        return 0;
    }

    for (int i = pos; i < totalConversoes - 1; i++)
        historico[i] = historico[i + 1];

    totalConversoes--;

    // Atualiza IDs:
    for (int i = 0; i < totalConversoes; i++)
        historico[i].id = i + 1;

    desenharLinhaSimples(LARGURA_CAIXA);
    printf(BOLD VERDE "  ✓ Removido com sucesso!\n" RESET);
    desenharLinhaSimples(LARGURA_CAIXA);
    return 1;
}

void processarConversao(const char *tipo,
                        double (*funcConversao)(double),
                        const char *unidadeOrigem,
                        const char *unidadeDestino)
{
    limparTela();
    exibirCabecalho();

    desenharLinhaDupla(LARGURA_CAIXA);
    printf(BOLD CIANO "  %s\n" RESET, tipo);
    desenharLinhaPontilhada(LARGURA_CAIXA);

    char prompt[100];
    snprintf(prompt, sizeof(prompt),
        "  ➤ Digite o valor em %s: ", unidadeOrigem);

    double valor = lerNumeroPositivo(prompt);
    double resultado = funcConversao(valor);

    desenharLinhaSimples(LARGURA_CAIXA);
    printf("  " BOLD VERDE "Valor de entrada:  " RESET "%.6lf %s\n", valor, unidadeOrigem);
    printf("  " BOLD VERDE "Valor convertido:  " RESET "%.6lf %s\n\n", resultado, unidadeDestino);
    desenharLinhaSimples(LARGURA_CAIXA);

    adicionarNoHistorico(tipo, valor, resultado);
    printf(BOLD VERDE "  ✓ Conversão registrada no histórico.\n" RESET);
    desenharLinhaDupla(LARGURA_CAIXA);
}

void cronometro(void) {
    limparTela();
    exibirCabecalho();

    desenharLinhaSimples(LARGURA_CAIXA);
    printf(BOLD VERDE "  Pressione ENTER para iniciar o cronômetro..." RESET "\n");
    desenharLinhaSimples(LARGURA_CAIXA);
    getchar();

    limparTela();
    exibirCabecalho();

    clock_t inicio = clock();

    desenharLinhaSimples(LARGURA_CAIXA);
    printf(BOLD ROXO "  Cronômetro em execução... Pressione ENTER para parar!\n" RESET);
    desenharLinhaSimples(LARGURA_CAIXA);

    const char *frames[] = {"|", "/", "-", "\\", "|", "/", "-", "\\"};
    int frame_idx = 0;

    printf(BOLD CIANO "    Tempo: 00:00.000  %s", frames[frame_idx]);
    fflush(stdout);

    while (1) {
        clock_t atual = clock();
        double tempo = (double)(atual - inicio) / CLOCKS_PER_SEC;

        frame_idx = (frame_idx + 1) % 8;
        printf("\r" BOLD CIANO "    Tempo: %02d:%02d.%03d  %s" RESET,
            (int)tempo / 60,
            (int)tempo % 60,
            (int)((tempo - (int)tempo) * 1000),
            frames[frame_idx]
        );
        fflush(stdout);

    #ifdef _WIN32
        if (_kbhit()) {
            int ch = _getch();
            if (ch == 13 || ch == 10) break;
        }
    #else
        struct timeval tv;
        fd_set fds;
        tv.tv_sec = 0;
        tv.tv_usec = 100000;
        FD_ZERO(&fds);
        FD_SET(STDIN_FILENO, &fds);

        if (select(STDIN_FILENO + 1, &fds, NULL, NULL, &tv) > 0) {
            int ch = getchar();
            if (ch == '\n') break;
        }
    #endif
        SLEEP_MS(100);
    }
    printf("\n"); // pular para próxima linha ao terminar

    double tempoFinal = (double)(clock() - inicio) / CLOCKS_PER_SEC;

    desenharLinhaDupla(LARGURA_CAIXA);
    printf(BOLD AZUL "   CRONÔMETRO FINALIZADO\n" RESET);
    desenharLinhaPontilhada(LARGURA_CAIXA);
    printf(BOLD VERDE "    TEMPO: %02d:%02d.%03d\n" RESET,
             (int)tempoFinal / 60,
             (int)tempoFinal % 60,
             (int)((tempoFinal - (int)tempoFinal) * 1000));
    desenharLinhaSimples(LARGURA_CAIXA);

    printf(AMARELO "  Salvar esse tempo no histórico? (S/N): " RESET);
    char salvar;
    scanf(" %c", &salvar);
    limpar_stdin();

    if (salvar == 'S' || salvar == 's') {
        adicionarNoHistorico("Cronômetro", 0.0, tempoFinal);
        printf(BOLD VERDE "\n  ✓ Salvo no histórico.\n" RESET);
    } else {
        printf(BOLD CIANO "\n  ℹ️  Tempo NÃO salvo no histórico.\n" RESET);
    }
    desenharLinhaDupla(LARGURA_CAIXA);
}

void listarHistorico(void) {
    if (totalConversoes == 0) {
        desenharLinhaSimples(LARGURA_CAIXA);
        printf(BOLD AMARELO "  ℹ️  HISTÓRICO VAZIO\n" RESET);
        desenharLinhaSimples(LARGURA_CAIXA);
        return;
    }

    desenharLinhaDupla(LARGURA_CAIXA);
    printf(BOLD AZUL "                              HISTÓRICO DE CONVERSÕES\n" RESET);
    desenharLinhaPontilhada(LARGURA_CAIXA);

    printf(BOLD CIANO "  ID  | TIPO             | ORIGINAL   →   CONVERTIDO   | DATA\n" RESET);
    desenharLinhaSimples(LARGURA_CAIXA);

    for (int i = 0; i < totalConversoes; i++) {
        printf(BOLD "%4d " RESET "| %-16s | %9.3lf → %9.3lf | %s\n",
               historico[i].id,
               historico[i].tipo,
               historico[i].valorOriginal,
               historico[i].valorConvertido,
               historico[i].data);
    }

    desenharLinhaDupla(LARGURA_CAIXA);
    printf(BOLD VERDE "  Total de conversões armazenadas: %d\n" RESET, totalConversoes);
    desenharLinhaDupla(LARGURA_CAIXA);
}

void limparHistorico(void) {
    totalConversoes = 0;
    desenharLinhaSimples(LARGURA_CAIXA);
    printf(BOLD VERDE "  ℹ️ Histórico limpo.\n" RESET);
    desenharLinhaSimples(LARGURA_CAIXA);
}

void menuPesquisar(void) {
    if (totalConversoes == 0) {
        desenharLinhaSimples(LARGURA_CAIXA);
        printf(BOLD AMARELO "  ℹ️  HISTÓRICO VAZIO\n" RESET);
        desenharLinhaSimples(LARGURA_CAIXA);
        return;
    }

    desenharLinhaDupla(LARGURA_CAIXA);
    printf(BOLD CIANO "  PESQUISAR REGISTROS (por tipo)\n" RESET);
    desenharLinhaPontilhada(LARGURA_CAIXA);

    char termo[30];
    printf(AMARELO "  Digite o termo para buscar: " RESET);

    if (!fgets(termo, sizeof(termo), stdin)) {
        desenharLinhaSimples(LARGURA_CAIXA);
        printf(BOLD VERMELHO "  ✗ ERRO: Falha na leitura do termo!\n" RESET);
        desenharLinhaSimples(LARGURA_CAIXA);
        return;
    }
    termo[strcspn(termo, "\n")] = 0;

    printf(CIANO "\n  Buscando por tipo \"%s\"...\n" RESET, termo);
    SLEEP_MS(400);

    int encontrados = 0;
    char tlower[30];

    for (int i = 0; termo[i]; i++) tlower[i] = tolower(termo[i]);
    tlower[strlen(termo)] = '\0';

    desenharLinhaPontilhada(LARGURA_CAIXA);

    for (int i = 0; i < totalConversoes; i++) {
        char tipoLower[30];
        for (int j = 0; historico[i].tipo[j]; j++)
            tipoLower[j] = tolower(historico[i].tipo[j]);
        tipoLower[strlen(historico[i].tipo)] = '\0';

        if (strstr(tipoLower, tlower)) {
            printf(BOLD "  ID: %d | %-13s | %.3lf → %.3lf (%s)\n" RESET,
                   historico[i].id,
                   historico[i].tipo,
                   historico[i].valorOriginal,
                   historico[i].valorConvertido,
                   historico[i].data);
            encontrados++;
        }
    }

    desenharLinhaSimples(LARGURA_CAIXA);

    if (!encontrados)
        printf(BOLD VERMELHO "  ✗ Nenhum resultado encontrado!\n" RESET);
    else
        printf(BOLD VERDE "  ✓ %d resultado(s) localizado(s)\n" RESET, encontrados);

    desenharLinhaSimples(LARGURA_CAIXA);
}

void inicializarHistorico(void) {
    capacidade = 5;
    historico = malloc(capacidade * sizeof(Conversao));
    if (!historico) {
        desenharLinhaSimples(LARGURA_CAIXA);
        printf(BOLD VERMELHO "\n  ✗ ERRO ao alocar memória!\n" RESET);
        desenharLinhaSimples(LARGURA_CAIXA);
        exit(1);
    }
}

void expandirHistorico(void) {
    capacidade *= 2;
    Conversao *novo = realloc(historico, capacidade * sizeof(Conversao));
    if (!novo) {
        desenharLinhaSimples(LARGURA_CAIXA);
        printf(BOLD VERMELHO "\n  ✗ ERRO ao expandir memória!\n" RESET);
        desenharLinhaSimples(LARGURA_CAIXA);
        free(historico);
        exit(1);
    }
    historico = novo;
}

void liberarMemoria(void) {
    free(historico);
    historico = NULL;
    totalConversoes = 0;
    capacidade = 5;
}

void obterDataAtual(char *buffer) {
    time_t now = time(NULL);
    struct tm *local = localtime(&now);
    strftime(buffer, 20, "%Y-%m-%d %H:%M", local);
}