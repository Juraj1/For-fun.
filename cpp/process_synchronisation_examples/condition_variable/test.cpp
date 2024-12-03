// proudly stolen from cppreference

#include <condition_variable>
#include <iostream>
#include <mutex>
#include <string>
#include <thread>
#include <unistd.h>
 
std::mutex m;
std::condition_variable cv;
std::string data;
bool ready = false;
bool processed = false;
 
void worker_thread()
{
    // wait until main() sends data
    // Enter monitor and lock critical section
    std::unique_lock lk(m);
    // wait unlocks mutex and suspends thread until notified and condition is ready.
    cv.wait(lk, []{ return ready; });

    sleep(2); 

    // after the wait, we own the lock
    std::cout << "Worker thread is processing data\n";
    data += " after processing";
 
    // send data back to main()
    processed = true;
    std::cout << "Worker thread signals data processing completed\n";
 
    // notifies main thread that the work is done
    cv.notify_one();
}
 
int main()
{

    // start worker thread
    std::thread worker(worker_thread);
  
    data = "Example data";
    // send data to the worker thread
    { // new context to lock the mutex and setup the condition.
        
        // lock critical section to satisfy condition
        std::lock_guard lk(m);
        // satisfy condition
        ready = true;
        std::cout << "main() signals data ready for processing\n";
    } // end of new context
    // notify waiting thread that it can wake up
    cv.notify_one();
 
    // wait for the worker
    {
        // lock the mutex
        std::unique_lock lk(m);
        // wait unlocks the mutex and suspends the thread untill processed condition is satisfied
        cv.wait(lk, []{ return processed; });
    }

    sleep(2);
    std::cout << "Back in main(), data = " << data << '\n';
 
    // thread has finished, join
    worker.join();

    return 0;
}
