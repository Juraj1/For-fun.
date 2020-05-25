#include <iostream>
#include <sstream>

template <typename Func, typename ... ARGS>
auto test(Func fun, ARGS ... arg) {
  return fun(arg...);
}

class functor {
public:
  template <typename ... T>
  auto operator()(T ... args) {
    return (args + ...);
  }
};

template <typename ... T>
auto f(T ... args) {
  ((std::cout << std::forward<T>(args) << std::endl), ...);
  return (args + ...);
}

auto a(std::string test){
  std::cout << test << std::endl;
  return test;
}

int main()
{ 
  std::string lambda = "lambda";
  std::cout << test([&lambda]()->std::string { std::cout << lambda << std::endl; return lambda; }) << std::endl;

  int func = 10;
  functor fc;
  std::cout << test(fc, func, func) << std::endl;

  std::string ptr = "pointer";
  std::cout << test(&a, ptr) << std::endl;
  
  return 0;
}
