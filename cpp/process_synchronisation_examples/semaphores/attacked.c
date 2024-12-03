#include <pthread.h>
#include <semaphore.h>
#include <stdio.h>
#include <stdlib.h>
#include <assert.h>
#include <unistd.h>
#include <sys/types.h>
#include <sys/wait.h>
#include <fcntl.h>
#include <sys/stat.h>

int main() {
  // create named semaphore in the filesystem /dev/shm with permissions RW for the user (600)
  const char *sem_name = "my_amazing_named_semaphore";
  sem_t *sem = sem_open(sem_name, O_CREAT | O_EXCL, 0600, 0);
  assert (sem != SEM_FAILED);

  // fork child process
  pid_t child_pid = fork();
  assert(child_pid != -1);

  // child process
  if (child_pid == 0) {
    // immediately after spawn block process and wait for signal from parent
    sem_wait(sem);
    printf("second\n");
    // cleanup
    sem_close(sem);
    return 0;
  }

  // parent code
  printf("first\n");
  // wait for child process to finish
  wait(NULL);

  printf("third\n");
  // cleanup
  sem_close(sem);
  sem_unlink(sem_name);

  return 0;
}

