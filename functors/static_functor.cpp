#include <iostream>

template <typename Func, typename ... ARGS>
void test(ARGS ... arg) {
  Func::call(arg...);
}

class functor {
private:
public:
  template <typename ... T>
  static void call(T ... args) {
  ((std::cout << std::forward<T>(args) << std::endl), ...);
//  std::cout << "asd" << std::endl;
  }
};

template <typename ... T>
void f(T ... args) {
  ((std::cout << std::forward<T>(args) << std::endl), ...);
}

int main()
{ 
  std::string lambda = "lambda";
  //test([&lambda]() { std::cout << lambda << std::endl; });

  std::string func = "functor";
  test<functor>(func, func);

  //std::string func = "functor";
  
  return 0;
}
