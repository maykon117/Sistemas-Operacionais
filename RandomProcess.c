#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <sys/types.h>
#include <sys/wait.h>

#define NUM_FILHOS 5
#define ITERACOES 500000000

int main() {

    printf("PID do pai: %d\n\n", getpid());

    for (int i = 0; i < NUM_FILHOS; i++) {

        pid_t pid = fork();

        if (pid < 0) {
            perror("fork");
            exit(EXIT_FAILURE);
        }

        if (pid == 0) {

            volatile unsigned long long contador = 0;

            printf(
                "Filho %d iniciado - PID=%d\n",
                i + 1,
                getpid()
            );

            for (unsigned long long j = 0;
                 j < ITERACOES;
                 j++) {
                contador++;
            }

            printf(
                "Filho %d terminou - PID=%d\n",
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

        if (pid > 0 && WIFEXITED(status)) {

            printf(
                "wait() recebeu PID=%d | código=%d\n",
                pid,
                WEXITSTATUS(status)
            );
        }
    }

    return 0;
}