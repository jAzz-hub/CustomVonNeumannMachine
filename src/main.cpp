#include"./cpu/REGISTER_BANK.h"
#include"./cpu/CONTROL_UNIT.h"
#include"./memory/MAINMEMORY.h"
#include"./loader.h"
#include"./core.h"
#include"./process.h"
#include<pthread.h>
using namespace std;


// Processo é criado

// Processo recebe uma UC

// Thread fica pronta.


void thread_A_start(core &c1) {
    while (true) { // loop infinito
        unique_lock<mutex> lock(mtx); // lock mutex
        cv.wait(lock, [] { return turnA; }); // wait until it's thread A's turn

        cout << "Thread A is running process " << currentProcessIndex << endl;        
        c1.running_asm(c1.proc.quantum); // run the process
        cout << "Thread A is interrupted" << endl;
        
        turnA = false;
        cv.notify_all();
    }
}


void thread_B_start(core &c2) {
    while (true) {
        unique_lock<mutex> lock(mtx);
        cv.wait(lock, [] { return !turnA; });


        cout << "Thread B is running process " << currentProcessIndex << endl;
        c2.running_asm(c2.proc.quantum);
        cout << "Thread B is interrupted" << endl;

        // Move the process to the end of the queue
        turnA = true;
        cv.notify_all();
    }
}

void running_cores(PCB pcb)
{
    while(true)
    {  
        thread t1(thread_A_start, ref(pcb.cores[i]), ref(processes));
        thread t2(thread_B_start, ref(pcb.cores[i+1]), ref(processes));
                
        t1.join();
        t2.join();

        if (c1.stop_flag == true)
        {   
            if (c1.zombie == true)
            {
                c1 = c1.pop();
                PCB.zombie.append(c1);
            }
            else
            {
                string* aux1 = ;
                string* aux2 = ;
                pcb[]
                pcb[]
            }

            
            if (c2.zombie == true)
    	    {
                c2 = c2.pop();
                PCB.zombie.append(c2);
            }
            else
                //c2 vai pro final da fila
        }

        if pcb.cores.empty() == true
        {
            false;
            break;
        }
    }
}

int main(int argc, char* argv[]){

    if (argc != 2) {
    std::cerr << "Usage: " << argv[0] << " <input_file>" << std::endl;
    return 1;
    }

    std::cout<<argv<<std::endl;

    // PCB pcb = PCB(argv, argc);

    // running_cores(pcb);

    return 0 ;




    //1º Lêem-se 10 programas no máximo

    //2º Cria-se uma fila de cores à partir de cada programa

    //3º Inicia-se a função rodando os cores()

    c1.start();

    c1.running_asm();

    Considere que para cada processo que rodar
    um novo core deve ser criado    
    Toda vez que o pipeline for interrompido, ou seja que hip_A
    for validada, core.zombie será tratado como true.
    Se core.zombie for true, o core será removido da fila de cores.


há uma fila de cores que é criada à partir de uma fila de programas
    
    de forma que quando a função running_asm parar 

    pois hip_A foi validada como verdadeira

    o core é guardado no final de uma fila.


    return 0;

}
