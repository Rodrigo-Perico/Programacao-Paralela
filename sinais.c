#include <pthread.h>
#include <signal.h>
#include <stdio.h>
#include <unistd.h>

void desligar(int sig) { printf("Luz desligada.\n"); }
void* sensor(void* arg) {
    signal(SIGUSR1, desligar);
    while (1) pause();
    return NULL;
}

void* controlador(void* id) {
    sleep(2);
    pthread_kill(*(pthread_t*)id, SIGUSR1);
    return NULL;
}

int main() {
    pthread_t t_sensor, t_controlador;
    pthread_create(&t_sensor, NULL, sensor, NULL);
    pthread_create(&t_controlador, NULL, controlador, &t_sensor);
    pthread_join(t_controlador, NULL);
    pthread_cancel(t_sensor);

    return 0;
}
