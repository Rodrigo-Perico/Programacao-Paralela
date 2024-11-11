#include <pthread.h>
#include <semaphore.h>
#include <stdio.h>
#include <unistd.h>

sem_t caixa;

void* cliente(void* id) {
    sem_wait(&caixa);
    printf("Cliente %ld está sendo atendido.\n", (long)id);
    sleep(1);
    printf("Cliente %ld terminou.\n", (long)id);
    sem_post(&caixa);
    return NULL;
}

int main() {
    pthread_t clientes[5];
    sem_init(&caixa, 0, 1);

    for (long i = 0; i < 5; i++) pthread_create(&clientes[i], NULL, cliente, (void*)i);
    for (int i = 0; i < 5; i++) pthread_join(clientes[i], NULL);

    sem_destroy(&caixa);
    return 0;
}
