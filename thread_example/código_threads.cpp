#include <stdio.h>
#include <pthread.h>
#include <unistd.h>

// Estrutura que representa nossa "classe" com métodos
typedef struct {
    pthread_t thread_A;       // Identificador da thread A
    pthread_t thread_B;       // Identificador da thread B
    int quantum_A;            // Quantum para thread A
    int quantum_B;            // Quantum para thread B
    pthread_mutex_t mutex;    // Mutex para sincronização
    pthread_cond_t cond_A;    // Condição para thread A
    pthread_cond_t cond_B;    // Condição para thread B
    int turn;                 // Variável para alternar a execução (1 = A, 2 = B)

    // Métodos da struct
    void (*iniciar)(struct thread_control*); // Método para inicializar as threads
    void (*funcao_A)(struct thread_control*); // Função da thread A
    void (*funcao_B)(struct thread_control*); // Função da thread B
} thread_control;

// Função da thread A
void thread_funcao_A(thread_control* t) {
    while (1) {
        pthread_mutex_lock(&t->mutex);

        // Aguarda a vez da thread A
        while (t->turn != 1)
            pthread_cond_wait(&t->cond_A, &t->mutex);

        printf("Thread A está rodando...\n");
        sleep(t->quantum_A);  // Simula o tempo de execução de A
        printf("Thread A foi interrompida após %d segundos.\n", t->quantum_A);

        // Alterna para a thread B
        t->turn = 2;
        pthread_cond_signal(&t->cond_B);

        pthread_mutex_unlock(&t->mutex);
    }
}

// Função da thread B
void thread_funcao_B(thread_control* t) {
    while (1) {
        pthread_mutex_lock(&t->mutex);

        // Aguarda a vez da thread B
        while (t->turn != 2)
            pthread_cond_wait(&t->cond_B, &t->mutex);

        printf("Thread B está rodando...\n");
        sleep(t->quantum_B);  // Simula o tempo de execução de B
        printf("Thread B foi interrompida após %d segundos.\n", t->quantum_B);

        // Alterna para a thread A
        t->turn = 1;
        pthread_cond_signal(&t->cond_A);

        pthread_mutex_unlock(&t->mutex);
    }
}

// Função para inicializar as threads
void thread_iniciar(thread_control* t) {
    t->turn = 1; // A thread A começa primeiro

    // Inicializa mutexes e condições
    pthread_mutex_init(&t->mutex, NULL);
    pthread_cond_init(&t->cond_A, NULL);
    pthread_cond_init(&t->cond_B, NULL);

    // Cria as threads
    pthread_create(&t->thread_A, NULL, (void* (*)(void*))t->funcao_A, t);
    pthread_create(&t->thread_B, NULL, (void* (*)(void*))t->funcao_B, t);
}

int main() {
    // Cria e inicializa uma variável da struct
    thread_control t = {0};  // Inicializa com valores padrão

    t.quantum_A = 3;  // Quantum da thread A
    t.quantum_B = 1;  // Quantum da thread B

    // Associa as funções a métodos da struct
    t.iniciar = thread_iniciar;
    t.funcao_A = thread_funcao_A;
    t.funcao_B = thread_funcao_B;

    // Inicializa as threads
    t.iniciar(&t);

    // Aguarda as threads terminarem (nunca vai terminar, pois está em loop)
    pthread_join(t.thread_A, NULL);
    pthread_join(t.thread_B, NULL);

    return 0;
}
