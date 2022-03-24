#include <coroutine>
#include <thread>
#include <memory>
#include <iostream>

#define DEBUG(x) std::cout << __FILE__ << ": " << __FUNCTION__ << ": " << __LINE__ << ": " << x << std::endl

template <typename T>
struct MyFuture {
  struct promise_type;
  using handle_type = std::coroutine_handle<promise_type>;

  handle_type coro;

  MyFuture(handle_type h) : coro(h) {
    DEBUG("constructor");
  }

  ~MyFuture() {
    if(coro) {
      coro.destroy();
    }
  }

  T get() {
    DEBUG(std::this_thread::get_id());
  
    std::thread t(
      [this] {
        coro.resume();
      }
    );

    t.join();
    
    return coro.promise().result;
  }

  struct promise_type {
    promise_type() {
      DEBUG(std::this_thread::get_id());
    }

    ~promise_type() {
      DEBUG(std::this_thread::get_id());
    }

    T result;

    auto get_return_object() {
      return MyFuture{handle_type::from_promise(*this)};
    }

    void return_value(T v) {
      DEBUG(std::this_thread::get_id());
      result = v;
    }

    std::suspend_always initial_suspend() {
      DEBUG(std::this_thread::get_id());
      return {};
    }
  
    std::suspend_always final_suspend() noexcept {
      DEBUG(std::this_thread::get_id());
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
  DEBUG(std::this_thread::get_id());

  auto fut = createFuture();
  auto res = fut.get();

  DEBUG(res);
  DEBUG(std::this_thread::get_id());

  return 0;
}
