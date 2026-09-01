#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <sys/types.h>
#include <sys/wait.h>

#define NUM_FILHOS 5

int main(void)
{
    pid_t filhos[NUM_FILHOS];

    printf("PID do processo pai: %d\n\n", getpid());

    for (int i = 0; i < NUM_FILHOS; i++)
    {
        filhos[i] = fork();

        if (filhos[i] < 0)
        {
            perror("Erro ao executar fork()");
            exit(EXIT_FAILURE);
        }

        if (filhos[i] == 0)
        {

            int tempo = NUM_FILHOS - i;

            printf(
                "[FILHO %d] Criado | PID=%d | "
                "Tempo de execução=%d segundos\n",
                i + 1,
                getpid(),
                tempo
            );

            sleep(tempo);

            printf(
                "[FILHO %d] Terminando | PID=%d\n",
                i + 1,
                getpid()
            );

            exit(i + 1);
        }
    }

    printf("\n[PAI] Todos os filhos foram criados.\n");
    printf("[PAI] PIDs dos filhos:\n");

    for (int i = 0; i < NUM_FILHOS; i++)
    {
        printf(
            "       Filho %d -> PID=%d\n",
            i + 1,
            filhos[i]
        );
    }

    printf("\n[PAI] Começando os waitpid()...\n\n");
    
    for (int i = 0; i < NUM_FILHOS; i++)
    {
        int status;

        printf(
            "[PAI] Esperando especificamente pelo "
            "Filho %d (PID=%d)...\n",
            i + 1,
            filhos[i]
        );

        pid_t pid_terminado = waitpid(
            filhos[i],
            &status,
            0
        );

        if (pid_terminado == -1)
        {
            perror("Erro em waitpid()");
            exit(EXIT_FAILURE);
        }

        if (WIFEXITED(status))
        {
            printf(
                "[PAI] Filho %d (PID=%d) foi recebido.\n",
                i + 1,
                pid_terminado
            );

            printf(
                "[PAI] Código de retorno: %d\n\n",
                WEXITSTATUS(status)
            );
        }
    }

    printf("========================================\n");
    printf("[PAI] Todos os filhos terminaram.\n");
    printf("========================================\n");

    return 0;
}