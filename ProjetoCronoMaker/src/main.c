// src/main.c (unchanged, but references the updated header)
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <time.h>
#include "tarefas.h"
#include "util.h"
#include "io.h"

#ifdef _WIN32
#include <windows.h>
#define SLEEP_MS(ms) Sleep(ms)
#else
#include <unistd.h>
#define SLEEP_MS(ms) usleep((ms) * 1000)
#endif

// Function to display a simple loading animation (ASCII spinner)
void loadingAnimation() {
    printf(CIANO "\nIniciando CRONOMAKER" RESET);
    const char *spinner[4] = {
        "|", "/", "-", "\\"
    };
    for(int i = 0; i < 20; i++) {
        printf("\r%s", spinner[i % 4]);
        fflush(stdout);
        SLEEP_MS(100);
    }
    printf("\r" VERDE "Pronto!\n" RESET);
}

int main() {
    habilitar_ansi_windows();
    loadingAnimation();  // Startup animation
    inicializarHistorico();
    carregarArquivo();

    int opcao;
    double valor, resultado;

    do {
        limparTela();
        exibirCabecalho();
        printf("\n  " MAGENTA "Escolha uma opcao: " RESET);
        scanf("%d", &opcao);
        while(getchar() != '\n');

        switch(opcao) {
            case 1: // Horas -> Minutos
                limparTela();
                printf("\n" BOLD AZUL "=== HORAS PARA MINUTOS ===" RESET "\n\n");
                valor = lerNumeroPositivo("Digite o valor em HORAS: ");
                resultado = horasParaMinutos(valor);
                printf("\n" VERDE "Resultado: %.2f horas = %.2f minutos\n" RESET, valor, resultado);
                adicionarNoHistorico("Horas -> Minutos", valor, resultado);
                pausar();
                break;
                
            case 2: // Minutos -> Segundos
                limparTela();
                printf("\n" BOLD AZUL "=== MINUTOS PARA SEGUNDOS ===" RESET "\n\n");
                valor = lerNumeroPositivo("Digite o valor em MINUTOS: ");
                resultado = minutosParaSegundos(valor);
                printf("\n" VERDE "Resultado: %.2f minutos = %.2f segundos\n" RESET, valor, resultado);
                adicionarNoHistorico("Minutos -> Segundos", valor, resultado);
                pausar();
                break;
                
            case 3: // Segundos -> Horas
                limparTela();
                printf("\n" BOLD AZUL "=== SEGUNDOS PARA HORAS ===" RESET "\n\n");
                valor = lerNumeroPositivo("Digite o valor em SEGUNDOS: ");
                resultado = segundosParaHoras(valor);
                printf("\n" VERDE "Resultado: %.2f segundos = %.6f horas\n" RESET, valor, resultado);
                adicionarNoHistorico("Segundos -> Horas", valor, resultado);
                pausar();
                break;
                
            case 4: // Horas -> Segundos
                limparTela();
                printf("\n" BOLD AZUL "=== HORAS PARA SEGUNDOS ===" RESET "\n\n");
                valor = lerNumeroPositivo("Digite o valor em HORAS: ");
                resultado = horasParaSegundos(valor);
                printf("\n" VERDE "Resultado: %.2f horas = %.2f segundos\n" RESET, valor, resultado);
                adicionarNoHistorico("Horas -> Segundos", valor, resultado);
                pausar();
                break;
                
            case 5: // Minutos -> Horas
                limparTela();
                printf("\n" BOLD AZUL "=== MINUTOS PARA HORAS ===" RESET "\n\n");
                valor = lerNumeroPositivo("Digite o valor em MINUTOS: ");
                resultado = minutosParaHoras(valor);
                printf("\n" VERDE "Resultado: %.2f minutos = %.6f horas\n" RESET, valor, resultado);
                adicionarNoHistorico("Minutos -> Horas", valor, resultado);
                pausar();
                break;
                
            case 6: // Segundos -> Minutos
                limparTela();
                printf("\n" BOLD AZUL "=== SEGUNDOS PARA MINUTOS ===" RESET "\n\n");
                valor = lerNumeroPositivo("Digite o valor em SEGUNDOS: ");
                resultado = segundosParaMinutos(valor);
                printf("\n" VERDE "Resultado: %.2f segundos = %.2f minutos\n" RESET, valor, resultado);
                adicionarNoHistorico("Segundos -> Minutos", valor, resultado);
                pausar();
                break;
                
            case 7: // Ver historico
                listarHistorico();
                pausar();
                break;
                
            case 8: // Pesquisar historico
                menuPesquisar();
                pausar();
                break;
                
            case 9: // Limpar historico
                limparHistorico();
                pausar();
                break;
                
            case 10: // Salvar
                salvarArquivo();
                printf("\n" VERDE "Historico salvo com sucesso!\n" RESET);
                pausar();
                break;
                
            case 0:
                salvarArquivo();
                printf("\n" CIANO "Salvando e saindo...\n" RESET);
                break;
                
            default:
                printf("\n" VERMELHO "Opcao invalida!\n" RESET);
                pausar();
        }
        
    } while(opcao != 0);
    
    // Libera memoria
    liberarMemoria();
    
    return 0;
}