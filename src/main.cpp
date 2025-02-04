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
const string scheduler = "RR";

// Processo é criado

// Processo recebe uma UC

// Thread fica pronta.

mutex mtx;
condition_variable cv;
bool turnA = true;
size_t currentProcessIndex = 0;
bool allProcessesConsumed = false;
bool cache = false;

void thread_A_start(core &c1, PCB &pcb) {
    while (true)
    { // loop infinito
        unique_lock<mutex> lock(mtx); // lock mutex
        cv.wait(lock, [] { return turnA; }); // wait until it's thread A's turn

        if(pcb.cores.empty())
        {
            cout << "All cores have been processed." << endl;
            return;
        }

        cout << "Thread A is running process " << c1.proc.id << endl;        
        
        c1.running_asm(pcb.scheduller); // run the process with the burst time
        
        cout << "Thread A is interrupted" << endl;
        
        turnA = false;
        c1.proc.set_state("waiting");
        cv.notify_all();
        if(c1.stop_flag == true || c1.zombie == true)
        {
            pcb.zombie_check();
            break;
        }
    }
}


void thread_B_start(core &c2, PCB &pcb) {
    while (true) {
        unique_lock<mutex> lock(mtx);
        cv.wait(lock, [] { return !turnA; });

        if(pcb.cores.empty())
        {
            cout << "All cores have been processed." << endl;
            return;
        }

        cout << "Thread B is running process " << c2.proc.id << endl;
        c2.running_asm(pcb.scheduller);
        cout << "Thread B is interrupted" << endl;

        // Move the process to the end of the queue
        turnA = true;
        cv.notify_all();
        if (c2.stop_flag == true || c2.zombie == true)
        {
            pcb.zombie_check();
            break;
        }
    }
}

void running_cores(PCB pcb)
{
    int iteration_count = 0;
    while (!pcb.cores.empty() && iteration_count < 10)
    {
        if (pcb.cores.size() < 2){
            cout << "Not enough cores to run." << endl;
            cout<<endl<<endl<<endl<<"ZOMBIES INFO:"<<endl;
            pcb.zombies_info();
            cout<<endl<<endl<<endl<<"CORES INFO:"<<"Sobrou 1 core"<<endl;
            pcb.cores_info();
            
            cout << "All cores have been processed." << endl;
            return;
        }
    

        thread t1(thread_A_start, ref(pcb.cores[0]), ref(pcb));
        thread t2(thread_B_start, ref(pcb.cores[1]), ref(pcb));

        t1.join();
        t2.join();

        // Incrementar o contador de iterações e imprimir métricas
        iteration_count++;
        cout << "Iteration " << iteration_count << " completed." << endl;
        cout << "Number of cores remaining: " << pcb.cores.size() << endl;
        cout << "Number of zombie cores: " << pcb.zombies.size() << endl;
        cout<<endl<<endl;
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

    //Criar um vetor de strings com os nomes dos programas tirando o último elemento
    std::vector<std::string> input_programs(argv + 1, argv + argc - 1);

    PCB pcb = PCB(input_programs, argv[argc-1], cache);

    pcb.cores.pop_back();

    // Iterar sobre o vector mostrando cada core
    for (const auto& core : pcb.cores) {
        cout << "Program Name: " << core.proc.input_program << endl;
        cout << "-------------------------" << endl;
    }

    if (pcb.scheduller == "SJF")
    {
        pcb.sorting_cores();
        cout<<"Sorted cores by burst time"<<endl;
    }

    running_cores(pcb);

    return 0;
}



