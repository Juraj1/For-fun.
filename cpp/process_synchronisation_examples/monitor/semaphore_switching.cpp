#include <iostream>
#include <thread>
#include <mutex>
#include <condition_variable>
#include <semaphore.h>

// similar example as monitor synchronisation, however a bit different approach using unnamed semaphores
// if we were using named semaphores, this would have an advantage of inter process synchronisation

static sem_t mutex; //semaphore to protect critical section
static sem_t semA; // synchronisation semaphore to signal thread A
static sem_t semB; // synchronisation semaphore to signal thread B
static sem_t semReady; // synchronisation semaphore to signal parent thread, that either thread A or B is ready.

void threadA(int &num) {
  // open parent thread semaphore
  sem_post(&semReady);

  // iterate 10 times
  for(int i = 0; i < 10; i++) {
    // wait until either parent thread or B thread allows us to run
    sem_wait(&semA);

    // lock critical section
    sem_wait(&mutex);
    std::cout << "**** thread A incremented to: " << ++num << std::endl;
    // unlock critical section
    sem_post(&mutex);
  
    // notify thread B that it can run - unlock it's semaphore
    sem_post(&semB);
  }
}

void threadB(int &num) {
  // open parent thread semaphore
  sem_post(&semReady);  

  // iterate 10 times
  for(int i = 0; i < 10; i++) {
    // wait until either parent thread or A thread allows us to run 
    sem_wait(&semB);

    // lock critical section
    sem_wait(&mutex);
    std::cout << "#### thread B incremented to: " << ++num << std::endl;
    // unlock critical section
    sem_post(&mutex);

    // notify thread A that it can run - unlock it's semaphore
    sem_post(&semA);
  }
}

int main() {
  // init semaphores
  sem_init(&semA, 0, 0); 
  sem_init(&semB, 0, 0);  
  sem_init(&semReady, 0, 1);  
  sem_init(&mutex, 0, 1);

  int number = 0;

  // get semaphore ready into locked state
  sem_wait(&semReady);

  // start threads
  std::thread A(threadA, std::ref(number));
  std::thread B(threadB, std::ref(number));

  // block on semaphore ready and wait for child threads to open
  sem_wait(&semReady);
  // notify thread A that it can continue - unblock it's semaphore
  sem_post(&semA);


  // wait till the job is done and join threads
  A.join();
  B.join();
  
  std::cout << "after joining: " << number << std::endl;

  // cleanup
  sem_destroy(&mutex);;
  sem_destroy(&semA);
  sem_destroy(&semB);
  sem_destroy(&semReady);

  return 0;
}
