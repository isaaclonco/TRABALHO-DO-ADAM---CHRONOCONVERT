#include "../include/platform.h"
#include "../include/tarefas.h"
#include "../include/util.h"
#include "../include/io.h"
#include <stdio.h>
#include <stdlib.h>

typedef struct {
    const char *titulo;
    double (*func)(double);
    const char *origem;
    const char *destino;
} ConversaoOption;

int main(void) {
    habilitar_ansi_windows();

    carregarArquivo();
    if (historico == NULL) {
        inicializarHistorico();
    }

    ConversaoOption opcoes[] = {
        {"Horas → Minutos",       horasParaMinutos,      "HORAS", "MINUTOS"},
        {"Minutos → Segundos",    minutosParaSegundos,   "MINUTOS", "SEGUNDOS"},
        {"Segundos → Horas",      segundosParaHoras,     "SEGUNDOS", "HORAS"},
        {"Horas → Segundos",      horasParaSegundos,     "HORAS", "SEGUNDOS"},
        {"Minutos → Horas",       minutosParaHoras,      "MINUTOS", "HORAS"},
        {"Segundos → Minutos",    segundosParaMinutos,   "SEGUNDOS", "MINUTOS"}
    };
    const int nOpcoesConversao = sizeof(opcoes) / sizeof(opcoes[0]);

    int sair = 0;

    while (!sair) {
        exibirCabecalho();
        exibirMenu();
        exibirRodape();

        printf("\n" BOLD AMARELO "➤ Digite sua opção: " RESET);

        int opcao;
        if (scanf("%d", &opcao) != 1) {
            limpar_stdin();
            printf(BOLD VERMELHO "  ✗ ERRO: Entrada inválida!\n" RESET);
            pausar();
            continue;
        }
        limpar_stdin();

        switch (opcao) {
            case 1:
                while (1) {
                    exibirCabecalho();
                    printf(BOLD BRANCO "  ╔═══════════════════════════════════════╗\n");
                    printf("  ║         OPÇÕES DE CONVERSÃO           ║\n");
                    printf("  ╠═══════════════════════════════════════╣\n");
                    for (int i = 0; i < nOpcoesConversao; i++) {
                        printf("  ║  [%d]  %s\n", i+1, opcoes[i].titulo);
                    }
                    printf("  ╚═══════════════════════════════════════╝\n");
                    printf("  [7] Voltar ao Menu Principal\n");

                    int escolha;
                    printf("\n" BOLD AMARELO "➤ Digite o número da conversão desejada: " RESET);
                    if (scanf("%d", &escolha) != 1 || escolha < 1 || escolha > nOpcoesConversao + 1) {
                        limpar_stdin();
                        printf(BOLD VERMELHO "  ✗ ERRO: Opção inválida!\n" RESET);
                        pausar();
                        continue;
                    }
                    limpar_stdin();
                    if (escolha == nOpcoesConversao + 1) break;
                    ConversaoOption *opt = &opcoes[escolha-1];
                    processarConversao(opt->titulo, opt->func, opt->origem, opt->destino);
                    pausar();
                }
                break;
            case 2:
                exibirCabecalho();
                listarHistorico();
                pausar();
                break;
            case 3:
                exibirCabecalho();
                menuPesquisar();
                pausar();
                break;
            case 4:
                exibirCabecalho();
                cronometro();
                pausar();
                break;
            case 5:
                salvarArquivo();
                printf(BOLD VERDE "  ✓ Histórico salvo com sucesso!\n" RESET);
                pausar();
                break;
            case 6:
                limparHistorico();
                printf(BOLD VERDE "  ✓ Histórico APAGADO!\n" RESET);
                pausar();
                break;
            case 0:
                salvarArquivo();
                printf(BOLD VERDE "  Até a próxima!\n" RESET);
                sair = 1;
                break;
            default:
                printf(BOLD VERMELHO "  ✗ ERRO: Opção inválida!\n" RESET);
                pausar();
        }
    }

    liberarMemoria();
    return EXIT_SUCCESS;
}