/// @author Jiri Zahradnik 
/// @file templated_logger.cpp

#include <iostream>
#include <fstream>
#include <type_traits>
#include <vector>
#include <tuple>
#include <syslog.h>

// ignore warning, then restore
//#pragma GCC diagnostic push
//#pragma GCC diagnostic ignored "-Wignored-attributes"
//#pragma GCC diagnostic pop

/* types of logger, just for semantics */
using syslog_log_t = struct syslog_type{};
using console_log_t = struct console_type{};
using file_log_t = struct file_type{}; 
using composite_log_t = struct composite_type{};

/* forward declaration for composite_logger usage */
template <typename T, typename ... F>
class logger;

/* templates for same type check , TODO mozna pujde pouzit std::is_same_v */
template <typename A, typename B>
struct same_type { static constexpr bool value = false; };

template <typename T>
struct same_type<T, T> { static constexpr bool value = true; };

/* template for searching type in type pack */
template <typename TARGET, typename ... PACK>
using is_present = std::conjunction<std::is_same<TARGET, PACK>...>;

/* template class for variadic vectors */
template <typename ... ACCEPTED_CHANNELS>
class variadic_vector {
protected:
  /* create tuple of vectors, one for each ACCEPTED_CHANNELS type */
  using tuple_of_vectors = std::tuple<std::vector<ACCEPTED_CHANNELS>...>;
  tuple_of_vectors vectors;

  template <int N, typename T>
  struct  vector_of_type 
          : same_type< T,
                             typename std::tuple_element<N, tuple_of_vectors>::type::value_type>
  {};

  template <int N, typename T, typename TUPLE, bool MATCH = false> 
  struct matching_field {
    static std::vector<T>& get(TUPLE &tp) {
      return matching_field< N + 1,
                             T,
                             TUPLE,
                             vector_of_type<N + 1, T>::value
                           >::get(tp);
    }
  };

  template <int N, typename T, typename TUPLE>
  struct matching_field<N, T, TUPLE, true> {
    static std::vector<T>& get(TUPLE &tp) {
      return std::get<N>(tp);
    }
  };

public:
  template <typename T>
  std::vector<T> &access() {
    return matching_field< 0, 
                           T,
                           tuple_of_vectors,
                           vector_of_type<0, T>::value
                         >::get(vectors);
  }
};

/* template class for composite logger */
template <typename ... ACCEPTED_CHANNELS>
class composite_logger {
protected:
  //std::vector<logger<syslog_log_t, SYS>> sysloggers;
  //std::vector<logger<console_log_t, CONS>> console_loggers;
  //std::vector<logger<file_log_t, FL>> file_loggers;

  /* variadic vectors for types ACCEPTED_CHANNELS */
  variadic_vector<ACCEPTED_CHANNELS...> vectors;

public:
  composite_logger() = default;
  template <typename T, typename F>
  void add(logger<T, F> log) {
    /* check whether type of channel is in accepted channels */
    static_assert(
            is_present<F, ACCEPTED_CHANNELS...>::value,
            "Logger type not found in accepted channels."
    );
    
    auto vec = vectors.template access<F>();
    vec.push_back(log);
  }


  void log(const std::string &msg, int log_level = 0) {
    std::cout << "test" << std::endl;
  }

  //void log(const std::string& msg, int log_level = 0) {
  //  if constexpr (!sysloggers.empty()) {
  //    for (auto &member : sysloggers) {
  //      member.log(msg, log_level);
  //    }
  //  }
  //  if constexpr (!console_loggers.empty()) {
  //    for (auto &member : console_loggers) {
  //      member.log(msg);
  //    }
  //  }
  //  if constexpr (!file_loggers.empty()) {
  //    for (auto &member : file_loggers) {
  //      member.log(msg);
  //    }
  //  }
  //} 
};

template <typename T, typename F, typename ... OTHER>
class single_logger {
protected:
  F file;
public:
  single_logger(F&& out) : file(std::forward<F>(out)) {};
  
  /* perfect forward the channel for logging as rvalue, can hold copy and reference */
  /* if the logging channel is file, close it on end */
  ~single_logger() {
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


/* template for composite logger */
template <typename T, typename ... F>
class logger : public std::conditional<
  std::is_same_v<T, composite_log_t>,
  composite_logger<F...>,
  single_logger<T, F...>
  >::type
{
public:
  explicit logger(F&& ... out) : single_logger<T, F...>::single_logger(std::forward<F>(out)...) {};
  logger() : composite_logger<F...>::composite_logger() {};
};

int main(int argc, char *argv[]) {
  //logger<file_log_t, std::ofstream> A(std::ofstream("text.txt", std::ios_base::out | std::ios_base::app));
  std::ofstream file("text.txt", std::ios_base::out | std::ios_base::app);
  logger<file_log_t, decltype(file)&> A(file);
  A.log("TEST");

  //logger<console_log_t, decltype(std::cout)&> B(std::cout);
  //B.log("COUT\n");

  //logger<syslog_log_t, decltype(syslog)&> C(syslog);
  //C.log("SYSLOG blabla\n", LOG_DEBUG);
  
  return 0;
}
