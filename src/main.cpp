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
const string scheduler = "FCFS";
bool cache = false;
// Processo é criado

// Processo recebe uma UC

// Thread fica pronta.

mutex mtx;
condition_variable cv;
bool turnA = true;
size_t currentProcessIndex = 0;
bool allProcessesConsumed = false;


using container = vector<vector<string>>;
void thread_A_start(core &c1, PCB &pcb, core &c2) {
    int similarity_caching_time = c1.core_instructions.size() * 650;
    if (cache)
    {
        sort(c1.core_instructions.begin(), c1.core_instructions.end());
        sort(c2.core_instructions.begin(), c2.core_instructions.end());

        vector<string> intersection;
        set_intersection(c1.core_instructions.begin(), c1.core_instructions.end(),
                          c2.core_instructions.begin(), c2.core_instructions.end(),
                          back_inserter(intersection));
        
        if (intersection.empty()) similarity_caching_time = (similarity_caching_time/4);
        else similarity_caching_time = similarity_caching_time/2;
    }
    else
        similarity_caching_time = 3000;

    while (true)
    { // loop infinito
        unique_lock<mutex> lock(mtx); // lock mutex
        cv.wait(lock, [] { return turnA; }); // wait until it's thread A's turn

        if(pcb.cores.empty())
        {
            cout << "All cores have been processed." << endl;
            return;
        }

        int core_address = pcb.address_mapping.get_address(0);
        cout << "Thread A is running process " << pcb.get_core(core_address).proc.id << endl;        
        

        // calcular valor de similaridade entre instructions do core 1 e instructions do core 2
        // esse valor verifica quantos elementos esses vectors tem em comum
        // quanto mais valores ambos os vectores tem em comum menor é esse número e quanto mais diferentes eles são maior ele é
        // esse valor varia de 0 à 3000 e é calculado pela função similarity_caching
        

        c1.running_asm(pcb.scheduller, similarity_caching_time); // run the process with the burst time
        
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


void thread_B_start(core &c2, PCB &pcb, core &c1) {
    int similarity_caching_time = c2.core_instructions.size() * 650;
    
    if (cache)
    {
        sort(c1.core_instructions.begin(), c1.core_instructions.end());
        sort(c2.core_instructions.begin(), c2.core_instructions.end());

        vector<string> intersection;
        set_intersection(c1.core_instructions.begin(), c1.core_instructions.end(),
                          c2.core_instructions.begin(), c2.core_instructions.end(),
                          back_inserter(intersection));
        
        if (intersection.empty()) similarity_caching_time = (similarity_caching_time/4);
        else similarity_caching_time = similarity_caching_time/2;
    }
    while (true) {
        unique_lock<mutex> lock(mtx);
        cv.wait(lock, [] { return !turnA; });

        if(pcb.cores.empty())
        {
            cout << "All cores have been processed." << endl;
            return;
        }

        int core_address = pcb.address_mapping.get_address(1);
        cout << "Thread B is running process " << pcb.get_core(core_address).proc.id << endl;
        // if (cache)
        //     similarity_caching(c2.core_instructions, c1.core_instructions, &similarity_caching_time);
        // else
        //     similarity_caching_time = 3000;

        c2.running_asm(pcb.scheduller, similarity_caching_time);
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

        
        if (pcb.cores.size() == 1)
        {
            int core_address = pcb.address_mapping.get_address(0);
            thread t1(thread_A_start, ref(pcb.get_core(core_address)), ref(pcb), ref(pcb.get_core(core_address)));
            t1.join();
            cout<<"AQUII 1111";
        }
        else
        {
            int core_address1 = pcb.address_mapping.get_address(0);
            int core_address2 = pcb.address_mapping.get_address(1);
            thread t1(thread_A_start, ref(pcb.get_core(core_address1)), ref(pcb), ref(pcb.get_core(core_address2)));
            thread t2(thread_B_start, ref(pcb.get_core(core_address2)), ref(pcb), ref(pcb.get_core(core_address1)));
            
            t1.join();
            t2.join();
        }
        

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
using namespace chrono;
int main(int argc, char* argv[]){


    //Printar os dois nomes dos programas caso haja menos de 1 entrada
    if (argc < 2) {
        cerr << "Usage: " << argv[0] << " <input_file1> <input_file2> ..." << endl;
        return 1;
    }

    //Criar um vetor de strings com os nomes dos programas tirando o último elemento
    vector<string> input_programs(argv + 1, argv + argc - 1);

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

    auto start = high_resolution_clock::now();
    running_cores(pcb);
    auto stop = high_resolution_clock::now();
    auto duration = duration_cast<milliseconds>(stop - start);
    
    if (cache)
        cout << "Escalonando com" << scheduler <<"e caching: " << duration.count() << " ms" << endl;
    else
       cout << "Escalonando com" << scheduler <<"e sem caching" << duration.count() << " ms" << endl;
    
    return 0;
}



