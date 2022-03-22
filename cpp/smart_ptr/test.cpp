#include <iostream>
#include <memory>
#include <vector>
#include <iterator>

template <typename T> 
concept HasEmplaceBack = requires (T a) {
  a.emplace_back();
};

template <typename T>
class myContainer {
public:
  template <typename ... ARGS>
  auto emplace_back(ARGS... args) {
    ((std::cout << "forwarding: " << std::forward<ARGS>(args) << std::endl),...);
    return vec.emplace_back(std::forward<ARGS>(args)...);
  }
private:
  std::vector<T> vec;
};

template <typename T>
auto foo(std::shared_ptr<T> ptr, HasEmplaceBack auto  &cont) {
  return cont.emplace_back(ptr);
}

int main() {
  myContainer<std::shared_ptr<std::string>> cnt;
  
  auto val = std::make_shared<std::string>("Hello World");
  auto it = foo(val, cnt);
  std::cout << *it << std::endl;
  return 0;
} 
