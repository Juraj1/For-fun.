#include <iostream>
#include <thread>
#include <string>

static int ITERATION_COUNT = 0;

// unprotected resources - both cout and integer are unprotected - a fuckup (race condition) is going to happen
void threadA(int &num) {
  for(int i = 0; i < ITERATION_COUNT; i++) {
    std::cout << "**** thread A incremented to: " << ++num << std::endl;
  }
}

void threadB(int &num) {
  for(int i = 0; i < ITERATION_COUNT; i++) {
    std::cout << "#### thread B incremented to: " << ++num << std::endl;
  }
}

int main(int argc, char *argv[]) {
  
  if(argc != 2) {
    std::cout << "missing argument: iteration count" << std::endl;
    return 1;
  }
 
  ITERATION_COUNT = std::stoi(argv[1]);
 
  int number = 0;
  std::thread A(threadA, std::ref(number));
  std::thread B(threadB, std::ref(number));

  A.join();
  B.join();
  
  std::cout << "after joining: " << number << std::endl;

  return 0;
}
