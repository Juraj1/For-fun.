#include <iostream>
#include <thread>
#include <unistd.h>


// unprotected shared resources - race condition
void threadA(int &num) {
  for(int i = 0; i < 10; i++) {
    std::cout << "**** thread A incremented to: " << ++num << std::endl;
  }
}

void threadB(int &num) {
  for(int i = 0; i < 10; i++) {
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
