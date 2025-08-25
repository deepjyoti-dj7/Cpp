// TOPIC: unique_lock In C++ (std::unique_lock<mutex> lock(m1))

// NOTES:
// 1. The class unique_lock is a mutex ownership wrapper.
// 2. It Allows:
//	   a. Can Have Different Locking Strategies
//	   b. time-constrained attempts at locking (try_lock_for, try_lock_until)
//	   c. recursive locking
//	   d. transfer of lock ownership (move not copy)
//	   e. condition variables. (next section)

// Locking Strategies
//    TYPE       	  	EFFECTS(S)
// 1. defer_lock		do not acquire ownership of the mutex.
// 2. try_to_lock		try to acquire ownership of the mutex without blocking.
// 3. adopt_lock		assume the calling thread already has ownership of the mutex.

#include <iostream>
#include <thread>
#include <mutex>
using namespace std;

std::mutex m1;
int buffer = 0;



// EXAMPLE: 1

void task(const char* threadNumber, int loopFor) {
	std::unique_lock<mutex> lock(m1); // Automatically calls lock on mutex m1
	for(int i = 0; i < loopFor; i++){
		buffer++;
		cout << threadNumber << buffer << endl;
	}
}

int main() {
	thread t1(task, "T1 ", 10);
	thread t2(task, "T2 ", 10);
	t1.join();
	t2.join();
	return 0;
}



// EXAMPLE: 2

void task(const char* threadNumber, int loopFor) {
	std::unique_lock<mutex> lock(m1, std::defer_lock); // Does not call lock on mutex m1, because used defer_lock
	lock.lock();  // But then we will have to explicitly tell to lock when ever we want to lock mutex m1.
	for(int i = 0; i < loopFor; i++){
		buffer++;
		cout << threadNumber << buffer << endl;
	}
	// lock.unlock(); is not needed as it will be unlocked in destructor of unique_lock.
}

int main() {
	thread t1(task, "T1 ", 10);
	thread t2(task, "T2 ", 10);
	t1.join();
	t2.join();
	return 0;
}



// Example: 3

void task_adopt(const char* threadNumber) {
    m1.lock();  // manually lock first
    std::unique_lock<mutex> lock(m1, std::adopt_lock); // adopt ownership
    for (int i = 0; i < 5; i++) {
        buffer++;
        cout << threadNumber << buffer << endl;
    }
    // lock will release m1 automatically when it goes out of scope
}

int main() {
    thread t1(task_adopt, "T1 ");
    thread t2(task_adopt, "T2 ");

    t1.join();
    t2.join();

    cout << "Final buffer = " << buffer << endl;
}




// Example: 4

void task_try(const char* threadNumber) {
    std::unique_lock<mutex> lock(m1, std::try_to_lock);
    if (lock.owns_lock()) { // check if we actually got the lock
        for (int i = 0; i < 5; i+++) {
            buffer++;
            cout << threadNumber << buffer << endl;
            this_thread::sleep_for(chrono::milliseconds(50));
        }
    } else {
        cout << threadNumber << " could not acquire lock\n";
    }
}

int main() {
    thread t1(task_try, "T1 ");
    thread t2(task_try, "T2 ");

    t1.join();
    t2.join();

    cout << "Final buffer = " << buffer << endl;
}