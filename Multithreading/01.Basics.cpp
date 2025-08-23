// TOPIC: Introduction to thread in c++ (c++11)

// QUESTIONS
// 1. What do you understand by thread and give one example in C++?

// ANSWER
// 0. In evey application there is a default thread which is main(), in side this we create other threads.
// 1. A thread is also known as lightweight process. Idea is achieve parallelism by dividing a process into multiple threads. 
//    For example:
//    (a) The browser has multiple tabs that can be different threads. 
//    (b) MS Word must be using multiple threads, one thread to format the text, another thread to process inputs (spell checker)
//    (c) Visual Studio code editor would be using threading for auto completing the code. (Intellicence)

// WAYS TO CREATE THREADS IN C++11
// 1. Function Pointers
// 2. Lambda Functions
// 3. Functors
// 4. Member Functions
// 5. Static Member functions

// REQUIREMENT
// Find the addition of all odd number from 1 to 2600000000 and all even number from 1 to 2600000000

#include <iostream>
#include <thread>
#include <chrono>
#include <algorithm>
using namespace std;
using namespace std::chrono;
typedef unsigned long long ull;

ull OddSum = 0;
ull EvenSum = 0;

void findEven(ull start, ull end) {
    for (ull i = start; i <= end; i++) {
        if ((i & 1) == 0) {
            EvenSum += i;
        }
    }
}

void findOdd(ull start, ull end) {
    for (ull i = start; i <= end; i++) {
        if ((i & 1) == 1) {
            OddSum += i;
        }
    }
}

int main() {
    ull start = 0, end = 2600000000;

    auto startTime = high_resolution_clock::now();

    thread t1(findEven, start, end);
    thread t2(findOdd, start, end);

    t1.join();
    t2.join();

    // findOdd(start, end);
    // findEven(start, end);

    auto stopTime = high_resolution_clock::now();
    auto duration = duration_cast<microseconds>(stopTime - startTime);

    cout << "OddSum: " << OddSum << endl;
    cout << "Evensum: " << EvenSum << endl;

    cout << "Duration in Seconds: " << duration.count() / 1000000 << endl;

    cout << "CPU supports: " << thread::hardware_concurrency() << " threads" << endl;

    return 0;
}