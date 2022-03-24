#include <coroutine>
#include <iostream>
#include <memory>

#define DEBUG(x) std::cout << __FILE__ << ": " << __FUNCTION__ << ": " << __LINE__ << ": " << x << std::endl

template <typename T>
struct Generator {
  struct promise_type;
  using handle_type = std::coroutine_handle<promise_type>;

  handle_type coro;

  
  Generator(handle_type h) : coro(h) {
    DEBUG("Constructor");
  }

  Generator(const Generator&) = delete;
  Generator &operator=(const Generator&) = delete;
  Generator(Generator &&oth) : coro(oth.coro) {
    DEBUG("Move Constructor");
    oth.coro = nullptr;
  }

  Generator &operator=(Generator &&oth) {
    DEBUG("Move operator =");
    coro = oth.coro;
    oth.coro = nullptr;
    return *this;
  }

  ~Generator() {
    DEBUG("Destructor");
    if(coro) {
      coro.destroy();
    }
  }

  T genNextValue() {
    DEBUG("");
    coro.resume();
    return coro.promise().current_value;
  }

  struct promise_type {
    T current_value;

    promise_type() {
      DEBUG("");
    }

    ~promise_type() {
      DEBUG("");
    }

    std::suspend_always initial_suspend() {
      DEBUG("");
      return {};
    }

    std::suspend_always final_suspend() noexcept {
      DEBUG("");
      return {};
    }

    auto get_return_object() {
      DEBUG("");
      return Generator{handle_type::from_promise(*this)};
    }

    std::suspend_always yield_value(T value) {
      DEBUG("");
      current_value = value;
      return {};
    }
  
    void return_void() {}
    void unhandled_exception() {}
  };
};

Generator<int> getNext(int start = 10, int step = 10) {
  DEBUG("");
  auto value = start;
  while(true) {
    DEBUG("Before co_yield");
    co_yield value;
    DEBUG("After co_yield");
    value += step;
  }
}

int main() {
  auto gen = getNext();
  for(int i = 0; i <=2; ++i) {
    auto val = gen.genNextValue();
    DEBUG(val);
  }
}
