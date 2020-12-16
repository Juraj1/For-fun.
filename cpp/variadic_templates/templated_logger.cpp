/// @author Jiri Zahradnik 
/// @file templated_logger.cpp

#include <iostream>
#include <fstream>
#include <type_traits>
#include <vector>

#include <syslog.h>

// ignore warning, then restore
//#pragma GCC diagnostic push
//#pragma GCC diagnostic ignored "-Wignored-attributes"
//#pragma GCC diagnostic pop

/* types of logger, just for semantics */
using syslog_log_t = struct syslog_type{};
using console_log_t = struct console_type{};
using file_log_t = struct file_type{}; 

template <typename T, typename F>
class logger {
protected:
  F file;
public:
  logger(F &&out) : file(std::forward<F>(out)) {};
  
  /* perfect forward the channel for logging as rvalue, can hold copy and reference */
  /* if the logging channel is file, close it on end */
  ~logger() {
    if constexpr (std::is_same_v<T, file_log_t>) {
      file.flush();
      file.close();
    }
  }
  
  /* log, allows using stream and syslog call */
  void log(const std::string &msg, int log_level = 0) {
    if constexpr (std::is_same_v<T, syslog_log_t>) {
      file(log_level, "%s", msg.c_str());
    }
    else {
      file << msg;
    }
  }
};

int main(int argc, char *argv[]) {
  //logger<file_log_t, std::ofstream> A(std::ofstream("text.txt", std::ios_base::out | std::ios_base::app));
  std::ofstream file("text.txt", std::ios_base::out | std::ios_base::app);
  logger<file_log_t, decltype(file)&> A(file);
  A.log("Ahoj\n");

  logger<console_log_t, decltype(std::cout)&> B(std::cout);
  B.log("COUT\n");

  logger<syslog_log_t, decltype(syslog)&> C(syslog);
  C.log("SYSLOG blabla\n", LOG_DEBUG);
  

  return 0;
}
