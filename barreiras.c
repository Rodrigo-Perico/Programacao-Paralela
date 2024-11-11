#include <pthread.h>
#include <stdio.h>
#include <unistd.h>

pthread_barrier_t barreira;

void* carro(void* id) {
    printf("Carro %ld chegou no estacionamento.\n", (long)id);
    sleep(1);

    pthread_barrier_wait(&barreira);
    printf("Carro %ld saiu do estacionamento.\n", (long)id);
    return NULL;
}

int main() {
    pthread_t carros[5];
    pthread_barrier_init(&barreira, NULL, 5);

    for (long i = 0; i < 5; i++) pthread_create(&carros[i], NULL, carro, (void*)i);
    for (int i = 0; i < 5; i++) pthread_join(carros[i], NULL);

    pthread_barrier_destroy(&barreira);
    return 0;
}