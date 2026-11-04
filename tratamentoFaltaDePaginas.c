
#include <stdio.h>

#define MAX_QUADROS 100
#define MAX_ACESSOS 1000

int main() {
    int quadros[MAX_QUADROS];
    int paginas[MAX_ACESSOS];

    int quantidade_quadros;
    int quantidade_acessos;

    int page_hits = 0;
    int page_faults = 0;
    int substituicoes = 0;

    int ponteiro_fifo = 0;

    // Entrada da quantidade de quadros
    printf("=== SIMULADOR DE FALTA DE PAGINAS ===\n");

    printf("Quantidade de quadros da RAM: ");
    if (scanf("%d", &quantidade_quadros) != 1 ||
        quantidade_quadros < 1 ||
        quantidade_quadros > MAX_QUADROS) {
        printf("Quantidade de quadros invalida.\n");
        return 1;
    }

    // Inicializa os quadros como vazios
    for (int i = 0; i < quantidade_quadros; i++) {
        quadros[i] = -1;
    }

    // Entrada da sequencia de paginas
    printf("Quantidade de acessos: ");
    if (scanf("%d", &quantidade_acessos) != 1 ||
        quantidade_acessos < 1 ||
        quantidade_acessos > MAX_ACESSOS) {
        printf("Quantidade de acessos invalida.\n");
        return 1;
    }

    printf("Digite a sequencia de paginas:\n");

    for (int i = 0; i < quantidade_acessos; i++) {
        if (scanf("%d", &paginas[i]) != 1 || paginas[i] < 0) {
            printf("Pagina invalida.\n");
            return 1;
        }
    }

    printf("\n=== INICIO DA SIMULACAO ===\n");

    // Processamento dos acessos
    for (int i = 0; i < quantidade_acessos; i++) {

        int pagina_atual = paginas[i];
        int encontrada = 0;

        // Verifica se a pagina ja esta na RAM
        for (int j = 0; j < quantidade_quadros; j++) {
            if (quadros[j] == pagina_atual) {
                encontrada = 1;
                break;
            }
        }

        printf("\nAcesso a pagina %d: ", pagina_atual);

        if (encontrada) {
            page_hits++;
            printf("PAGE HIT");
        } else {
            page_faults++;
            printf("PAGE FAULT");

            // Procura um quadro vazio
            int quadro_vazio = -1;

            for (int j = 0; j < quantidade_quadros; j++) {
                if (quadros[j] == -1) {
                    quadro_vazio = j;
                    break;
                }
            }

            if (quadro_vazio != -1) {
                // Carrega a pagina no quadro vazio
                quadros[quadro_vazio] = pagina_atual;
            } else {
                // Memoria cheia: substituicao FIFO
                printf(" | Substituindo pagina %d",
                       quadros[ponteiro_fifo]);

                quadros[ponteiro_fifo] = pagina_atual;

                ponteiro_fifo =
                    (ponteiro_fifo + 1) % quantidade_quadros;

                substituicoes++;
            }
        }

        // Exibe o estado atual da memoria
        printf("\nRAM: ");

        for (int j = 0; j < quantidade_quadros; j++) {
            if (quadros[j] == -1) {
                printf("[ - ] ");
            } else {
                printf("[ %d ] ", quadros[j]);
            }
        }

        printf("\n");
    }

    // Calcula a taxa de faltas
    float taxa_faults =
        (float) page_faults / quantidade_acessos * 100;

    // Resultado final
    printf("\n=== RESULTADO DA SIMULACAO ===\n");

    printf("Total de acessos: %d\n", quantidade_acessos);
    printf("Page Hits: %d\n", page_hits);
    printf("Page Faults: %d\n", page_faults);
    printf("Substituicoes: %d\n", substituicoes);
    printf("Taxa de Page Faults: %.2f%%\n", taxa_faults);

    return 0;
}
