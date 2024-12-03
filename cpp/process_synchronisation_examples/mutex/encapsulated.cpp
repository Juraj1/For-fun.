#include <iostream>
#include <thread>
#include <mutex>

// encapsulation of shared resource and mutex - ensures proper protection of critical section, does not break ownership etc.
class my_int {
public:
  my_int(int a): val(a) {}
  
  int increment() {
    std::lock_guard lock(mut);
    val++;
    return val;
  }

  int decrement() {
    std::lock_guard lock(mut);
    val--;
    return val;
  }

  int get() {
    std::lock_guard lock(mut);
    return val;
  }

private:
  int val;
  std::mutex mut;
};

// unprotected std::cout - possible race condition
void threadA(my_int &num) {
  for(int i = 0; i < 10; i++) {
    std::cout << "**** thread A incremented to: " << num.increment() << std::endl;
  }
}

void threadB(my_int &num) {
  for(int i = 0; i < 10; i++) {
    std::cout << "#### thread B incremented to: " << num.increment() << std::endl;
  }
}

int main() {
  my_int number(0);
  std::thread A(threadA, std::ref(number));
  std::thread B(threadB, std::ref(number));

  A.join();
  B.join();
  
  std::cout << "after joining: " << number.get() << std::endl;

  return 0;
}
