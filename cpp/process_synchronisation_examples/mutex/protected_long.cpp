#include <iostream>
#include <thread>
#include <mutex>

std::mutex mut;

// one mutex protects entire iteration over shared resource - protects cout as well
void threadA(int &num) {
  std::lock_guard lock(mut);
  for(int i = 0; i < 10; i++) {
    std::cout << "**** thread A incremented to: " << ++num << std::endl;
  }
}

void threadB(int &num) {
  std::lock_guard lock(mut);
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
