#include <iostream>
#include <thread>
#include <mutex>
#include <condition_variable>

using lock_t = std::unique_lock<std::mutex>;

// simple monitor to protect and synchronise access to shared resource
// we want to synchronize threads in such manner that they will work in following way: A -> B -> A -> B -> etc.
std::mutex mut; // mutex protects the critical section
std::condition_variable condA; // blocks thread A
std::condition_variable condB; // blocks thread B
std::condition_variable condReady; // blocks parent thread

void threadA(int &num) {

  // notify parent thread that at least one child has spawned - if nobody's waiting on the condion, notify/notify_one will not be received!
  condReady.notify_one();

  // iterate and increase the value 10 times
  for(int i = 0; i < 10; i++) {
    // lock critical section
    lock_t lock(mut);
    // wait wait until notification by thread B or parent thread.
    condA.wait(lock);
    
    // print and increment the value - both COUT and INT are protected shared resource
    std::cout << "**** thread A incremented to: " << ++num << std::endl;
    
    // notify thread B that the job was done
    condB.notify_one();
  }
}

void threadB(int &num) {

  // notify parent thread that at least one child has spawned - if nobody's waiting on the condion, notify/notify_one will not be received!
  condReady.notify_one();
  
  // iterate and increase the value 10 times
  for(int i = 0; i < 10; i++) {
    // lock critical section
    lock_t lock(mut);
    // wait wait until notification by thread A or parent thread.
    condB.wait(lock);
    
    // print and increment the value - both COUT and INT are protected shared resource
    std::cout << "#### thread B incremented to: " << ++num << std::endl;
    
    // notify thread A that the job was done
    condA.notify_one();
  }
}

int main() {
  int number = 0;
  // start worker threads that will be alternating and priting icnremented value.
  std::thread A(threadA, std::ref(number));
  std::thread B(threadB, std::ref(number));

  { // new context to utilize RAII locking
    // lock the mutex to protect monitor
    lock_t lock(mut);
    // wait unlocks the mutex and puts thread to sleep untill notified by either threads
    condReady.wait(lock);
  }

  // iterations begin with thread A since it is notified, to notify thread B first, use condB
  condA.notify_one();

  // the job is done, join threads
  A.join();
  B.join();
  
  std::cout << "after joining: " << number << std::endl;

  return 0;
}
