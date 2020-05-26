#include <iostream>
#include <sstream>
#include <memory>
#include <type_traits>
#include <utility>

template <typename Func, typename ... ARGS>
auto test(Func fun, ARGS ... arg) {
  return fun(arg...);
}

template <typename Func, template <typename> typename SmartFuncPtr, typename ... ARGS>
auto test(SmartFuncPtr<Func> fun, ARGS ... arg) {
  return fun->operator()(arg...);
}

class functor {
public:
  template <typename ... T>
  auto operator()(T ... args) {
    return (args + ...);
  }
};

auto a(std::string test){
  std::cout << test << std::endl;
  return test;
}

int main()
{ 
  std::string lambda = "lambda";
  std::cout << test([&lambda]()->std::string { std::cout << lambda << std::endl; return lambda; }) << std::endl;

  float func = 10.5;
  functor fc;
  std::cout << test(fc, func, func) << std::endl;

  std::string ptr = "pointer";
  std::cout << test(&a, ptr) << std::endl;

  std::shared_ptr<functor> fcptr = std::make_shared<functor>(functor());
  std::string smart = "smart pointer";
  std::cout << test(fcptr, smart) << std::endl;

  std::unique_ptr<functor> fcuptr = std::make_unique<functor>(functor());
  std::string unique = "unique pointer";
  std::cout << test(std::move(fcuptr), unique, unique, unique) << std::endl;
  
  return 0;
}
