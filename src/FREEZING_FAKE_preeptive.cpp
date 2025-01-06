#include <iostream>
#include <vector>
#include <thread>
#include <mutex>
#include <condition_variable>
#include <chrono>
#include "core.h"

using namespace std;

mutex mtx;
condition_variable cv;
bool turnA = true;
size_t currentProcessIndex = 0;
bool allProcessesConsumed = false;

void thread_A_start(core &c1, vector<process> &processes) {
    while (true) { // loop infinito
        unique_lock<mutex> lock(mtx); // lock mutex
        cv.wait(lock, [] { return turnA; }); // wait until it's thread A's turn

        if (currentProcessIndex >= processes.size()) {
            allProcessesConsumed = true;
            cv.notify_all();
            break;
        }

        c1.setProcess(processes[currentProcessIndex]);
        cout << "Thread A is running process " << currentProcessIndex << endl; // print message
        c1.running_asm(); // run the process
        this_thread::sleep_for(chrono::seconds(c1.proc.quantum)); // Sleep for the quantum time
        cout << "Thread A is interrupted" << endl;

        currentProcessIndex++;
        turnA = false;
        cv.notify_all();
    }
}

void thread_B_start(core &c2, vector<process> &processes) {
    while (true) {
        unique_lock<mutex> lock(mtx);
        cv.wait(lock, [] { return !turnA; });

        if (currentProcessIndex >= processes.size()) {
            allProcessesConsumed = true;
            cv.notify_all();
            break;
        }

        c2.setProcess(processes[currentProcessIndex]);
        cout << "Thread B is running process " << currentProcessIndex << endl;
        c2.running_asm(); // run the process
        this_thread::sleep_for(chrono::seconds(c2.proc.quantum)); // Sleep for the quantum time
        cout << "Thread B is interrupted" << endl;

        currentProcessIndex++;
        turnA = true;
        cv.notify_all();
    }
}

int main(int argc, char *argv[]) {
    if (argc < 3) {
        cerr << "Usage: " << argv[0] << " <input_file1> <input_file2> ..." << endl;
        return 1;
    }

    vector<process> processes;
    for (int i = 1; i < argc; ++i) {
        processes.emplace_back(argv[i], 3, "novo", 4828, 284);
    }

    MainMemory ram(2048, 2048);
    REGISTER_BANK registers;
    Control_Unit UC;
    int counterForEnd = 5;
    int counter = 0;
    int clock = 0;
    bool endProgram = false;
    Instruction_Data data;

    core c1(ram, registers, UC, counterForEnd, counter, clock, endProgram, data, processes[0]);
    core c2(ram, registers, UC, counterForEnd, counter, clock, endProgram, data, processes[1]);

    thread t1(thread_A_start, ref(c1), ref(processes));
    thread t2(thread_B_start, ref(c2), ref(processes));

    t1.join();
    t2.join();

    if (allProcessesConsumed) {
        cout << "All processes have been consumed." << endl;
    }

    return 0;
}
