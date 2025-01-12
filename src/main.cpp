#include <iostream>
#include <vector>
#include <thread>
#include <mutex>
#include <condition_variable>
#include "./cpu/REGISTER_BANK.h"
#include "./cpu/CONTROL_UNIT.h"
#include "./memory/MAINMEMORY.h"
#include "./loader.h"
#include "./core.h"
#include "./process.h"
#include "./PCB.h"
using namespace std;


// Processo é criado

// Processo recebe uma UC

// Thread fica pronta.

mutex mtx;
condition_variable cv;
bool turnA = true;
size_t currentProcessIndex = 0;
bool allProcessesConsumed = false;

void thread_A_start(core &c1, PCB &pcb) {
    while (true) { // loop infinito
        unique_lock<mutex> lock(mtx); // lock mutex
        cv.wait(lock, [] { return turnA; }); // wait until it's thread A's turn

        cout << "Thread A is running process " << c1.proc.id << endl;        
        c1.running_asm(c1.proc.quantum); // run the process
        cout << "Thread A is interrupted" << endl;
        
        turnA = false;
        cv.notify_all();
        if(c1.stop_flag == true || c1.zombie == true)
        {
            pcb.ZombieCheck();
            break;
        }
    }
}


void thread_B_start(core &c2, PCB &pcb) {
    while (true) {
        unique_lock<mutex> lock(mtx);
        cv.wait(lock, [] { return !turnA; });


        cout << "Thread B is running process " << c2.proc.id << endl;
        c2.running_asm(c2.proc.quantum);
        cout << "Thread B is interrupted" << endl;

        // Move the process to the end of the queue
        turnA = true;
        cv.notify_all();
        if (c2.stop_flag == true || c2.zombie == true)
        {
            pcb.ZombieCheck();
            break;
        }
    }
}

void running_cores(PCB pcb)
{
    int iteration_count = 0;
    while (!pcb.cores.empty() && iteration_count < 10)
    {
        if (pcb.cores.size() < 2) {
            cout << "Not enough cores to run." << endl;
            return;
        }

        thread t1(thread_A_start, ref(pcb.cores[0]), ref(pcb));
        thread t2(thread_B_start, ref(pcb.cores[1]), ref(pcb));

        t1.join();
        t2.join();

        // if (pcb.cores[0].stop_flag == true)
        // {
        //     if (pcb.cores[0].zombie == true)
        //     {
        //         pcb.zombies.push_back(pcb.cores[0]);
        //         pcb.cores.pop_front();
        //     }
        //     else
        //     {
        //         // Move core to the end of the queue
        //         pcb.cores.push_back(pcb.cores[0]);
        //         pcb.cores.pop_front();
        //     }
        // }

        // if (pcb.cores[1].stop_flag == true)
        // {   
        //     if (pcb.cores[1].zombie == true)
        //     {
        //         pcb.zombies.push_back(pcb.cores[1]);
        //         pcb.cores.erase(pcb.cores.begin() + 1);
        //     }
        //     else
        //     {
        //         // Move core to the end of the queue
        //         pcb.cores.push_back(pcb.cores[1]);
        //         pcb.cores.erase(pcb.cores.begin() + 1);
        //     }
        // }

        // if (pcb.cores.empty())
        // {
        //     cout << "All cores have been processed." << endl;
        //     return;
        // }

        // Incrementar o contador de iterações e imprimir métricas
        iteration_count++;
        cout << "Iteration " << iteration_count << " completed." << endl;
        cout << "Number of cores remaining: " << pcb.cores.size() << endl;
        cout << "Number of zombie cores: " << pcb.zombies.size() << endl;
    }

    if (iteration_count >= 10) {
        cout << "Maximum number of iterations reached. Stopping execution." << endl;
    }
}

using namespace std;
int main(int argc, char* argv[]){

    //Printar os dois nomes dos programas caso haja menos de 1 entrada
    if (argc < 2) {
        std::cerr << "Usage: " << argv[0] << " <input_file1> <input_file2> ..." << std::endl;
        return 1;
    }

    std::vector<std::string> input_programs(argv + 1, argv + argc);

    PCB pcb = PCB(input_programs);
    for (const auto& program : input_programs) {
        std::cout << program << std::endl;
    }

    running_cores(pcb);

    return 0 ;




    //1º Lêem-se 10 programas no máximo

    //2º Cria-se uma fila de cores à partir de cada programa

    //3º Inicia-se a função rodando os cores()

//     Considere que para cada processo que rodar
//     um novo core deve ser criado    
//     Toda vez que o pipeline for interrompido, ou seja que hip_A
//     for validada, core.zombie será tratado como true.
//     Se core.zombie for true, o core será removido da fila de cores.


// há uma fila de cores que é criada à partir de uma fila de programas
    
//     de forma que quando a função running_asm parar 

//     pois hip_A foi validada como verdadeira

//     o core é guardado no final de uma fila.


    return 0;

}



