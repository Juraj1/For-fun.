#include <iostream>
#include <thread>
#include <mutex>
#include <unistd.h>

std::mutex mut;

// one mutex protects both shared resources: std::cout and int, however the protection is only inside iteration
void threadA(int &num) {
  for(int i = 0; i < 10; i++) {
    std::lock_guard lock(mut);
    std::cout << "**** thread A incremented to: " << ++num << std::endl;
  }
}

void threadB(int &num) {
  for(int i = 0; i < 10; i++) {
    std::lock_guard lock(mut);
    std::cout << "#### thread B incremented to: " << ++num << std::endl;
  }
}

int main() {
  int number = 0;
  std::thread A(threadA, std::ref(number));
  std::thread B(threadB, std::ref(number));

  A.join();
  B.join();
  
  std::cout << "after joining: " << number << std::endl;

  return 0;
}
