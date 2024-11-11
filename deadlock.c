#include <pthread.h>
#include <stdio.h>
#include <unistd.h>

pthread_mutex_t impressora = PTHREAD_MUTEX_INITIALIZER;
pthread_mutex_t scanner = PTHREAD_MUTEX_INITIALIZER;

void* funcionario1(void* arg) {
    printf("Funcionário 1 tentando acessar a impressora...\n");
    pthread_mutex_lock(&impressora);
    printf("Funcionário 1 acessou a impressora.\n");
    sleep(1); // Simulando tempo de uso da impressora

    printf("Funcionário 1 tentando acessar o scanner...\n");
    pthread_mutex_lock(&scanner); // Aqui ocorre o deadlock
    printf("Funcionário 1 acessou o scanner.\n");

    // Liberação dos recursos (nunca ocorre devido ao deadlock)
    pthread_mutex_unlock(&scanner);
    pthread_mutex_unlock(&impressora);
    return NULL;
}

void* funcionario2(void* arg) {
    printf("Funcionário 2 tentando acessar o scanner...\n");
    pthread_mutex_lock(&scanner);
    printf("Funcionário 2 acessou o scanner.\n");
    sleep(1); // Simulando tempo de uso do scanner

    printf("Funcionário 2 tentando acessar a impressora...\n");
    pthread_mutex_lock(&impressora); // Aqui ocorre o deadlock
    printf("Funcionário 2 acessou a impressora.\n");

    // Liberação dos recursos (nunca ocorre devido ao deadlock)
    pthread_mutex_unlock(&impressora);
    pthread_mutex_unlock(&scanner);
    return NULL;
}

int main() {
    pthread_t t1, t2;

    // Criação das threads
    pthread_create(&t1, NULL, funcionario1, NULL);
    pthread_create(&t2, NULL, funcionario2, NULL);

    // Espera as threads terminarem (mas elas ficam travadas)
    pthread_join(t1, NULL);
    pthread_join(t2, NULL);

    printf("Programa terminou (não deveria aparecer devido ao deadlock).\n");
    return 0;
}
