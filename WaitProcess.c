#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <sys/types.h>
#include <sys/wait.h>

#define NUM_FILHOS 5

int main() {
    pid_t filhos[NUM_FILHOS];

    printf("PID do pai: %d\n\n", getpid());

    for (int i = 0; i < NUM_FILHOS; i++) {

        filhos[i] = fork();

        if (filhos[i] < 0) {
            perror("fork");
            exit(EXIT_FAILURE);
        }

        if (filhos[i] == 0) {

            int tempo = NUM_FILHOS - i;

            printf(
                "Filho %d criado: PID=%d, PPID=%d, dormindo %d segundos\n",
                i + 1,
                getpid(),
                getppid(),
                tempo
            );

            sleep(tempo);

            printf(
                "Filho %d terminando: PID=%d\n",
                i + 1,
                getpid()
            );

            return i + 1;
        }
    }

    printf("\nPai aguardando os filhos...\n");

    for (int i = 0; i < NUM_FILHOS; i++) {
        int status;
        pid_t pid = wait(&status);

        if (pid > 0) {
            if (WIFEXITED(status)) {
                printf(
                    "Pai recebeu filho PID=%d, código de retorno=%d\n",
                    pid,
                    WEXITSTATUS(status)
                );
            }
        }
    }

    printf("Todos os filhos terminaram.\n");

    return 0;
}