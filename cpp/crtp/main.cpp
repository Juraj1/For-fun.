#include <vector>
#include <utility>
#include <variant>

#include "implementation.h"

/* crtp call handler */
template <typename T>
auto crtp_call(base<T>& val) {
  return val.do_stuff();
}

int main() {
  std::vector<std::variant<implementation_a, implementation_b>> vec;
  implementation_a A;
  implementation_b B;

  vec.push_back(A);
  vec.push_back(B);

  for(auto &member : vec) {
    if(std::holds_alternative<implementation_a>(member)) {
      crtp_call(std::get<implementation_a>(member)); 
    }
    else if (std::holds_alternative<implementation_b>(member)) {
      std::cout << crtp_call(std::get<implementation_b>(member)) << std::endl;
    }
    else {
      std::cerr << "no viable type conversion" << std::endl;
    } 
  } 

  return 0;
}
