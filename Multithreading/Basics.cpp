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