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
  int val; // value being protected
  std::mutex mut; // protecting mutex
};

// encapsulation of shared resource and mutex - ensures proper protection of critical section, does not break ownership etc.
class printer {
public:
  printer() = default;
  
  void print(const std::string &str) {
    std::lock_guard lock(print_mut);
    std::cout << str << std::endl;
  }
private:
  std::mutex print_mut; // mutex protecting shared resource cout
};

// thread A incrementing and printing
void threadA(my_int &num, printer &prnt) {
  for(int i = 0; i < 10; i++) {
    std::string str = "**** thread A incremented to: " + std::to_string(num.increment());
    prnt.print(str);
  }
}

// thread B incrementing and printing
void threadB(my_int &num, printer &prnt) {
  for(int i = 0; i < 10; i++) {
    std::string str = "#### thread B incremented to: " + std::to_string(num.increment());
    prnt.print(str);
  }
}

int main() {
  // protecting object init
  my_int number(0);
  // printer init
  printer prnt;

  // spawn thread
  std::thread A(threadA, std::ref(number), std::ref(prnt));
  std::thread B(threadB, std::ref(number), std::ref(prnt));

  // wait for job to be finished
  A.join();
  B.join();
  
  std::cout << "after joining: " << number.get() << std::endl;

  return 0;
}
