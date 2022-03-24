#include <coroutine>
#include <iostream>
#include <thread>
#include <memory>

#define DEBUG(x) std::cout << __FILE__ << ": " << __FUNCTION__ << ": " << __LINE__ << ": " << x << std::endl

template <typename T>
struct MyFuture {
  struct promise_type;
  using handle_type = std::coroutine_handle<promise_type>;

  handle_type coro;

  MyFuture(handle_type h) : coro(h) {
    DEBUG(" Constructor");
  }

  ~MyFuture() {
    DEBUG(" Destructor");
    if(coro) {
      coro.destroy();
    }
  }

  T get() {
    DEBUG("Return value");
    coro.resume();
    return coro.promise().result;
  }

  struct promise_type {
    T result;

    promise_type() {
      DEBUG("   Constructor");
    }
    
    ~promise_type() {
      DEBUG("   Destructor");
    }

    MyFuture<T> get_return_object() {
      DEBUG("   ");
      return MyFuture{handle_type::from_promise(*this)};
    }

    void return_value(T v) {
      DEBUG("   ");
      result = v;
    }

    std::suspend_always initial_suspend() {
      DEBUG("   ");
      return {};
    }

    std::suspend_always final_suspend() noexcept {
      DEBUG("   ");
      return {};
    }

    void unhandled_exception() {}
  };
};

MyFuture<int> createFuture() {
  DEBUG("");
  co_return 2021;
}

int main() {
  DEBUG("");
  auto fut = createFuture();
  auto res = fut.get();
  DEBUG(res);
}
