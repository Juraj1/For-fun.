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

  // create named semaphore stored in filesystem's /dev/shm with permissions 0600 - rw for user only
  const char *sem_name = "my_amazing_named_semaphore";
  sem_t *sem = sem_open(sem_name, O_CREAT | O_EXCL, 0600, 0);
  assert (sem != SEM_FAILED);

  // fork new process from here, everything untill child's process return 0 will be done twice, including sem_wait()
  pid_t child_pid = fork();
  assert(child_pid != -1);

  // locks semaphore, twice
  printf("locking semaphore\n");
  sem_wait(sem);

  // child process
  if (child_pid == 0) {
    printf("waiting on semaphore\n");
    // waits for semaphore to be unlocked, but it is unlocked only once, we need another unlock to prevent deadlock
    sem_wait(sem);
    printf("second\n");
    // close semaphore and exit
    sem_close(sem);
    return 0;
  }

  // parent code
  printf("first\n");
  printf("releasing semaphore\n");
  // release semaphore to allow child to run, but do it only once, for child to run, it needs to be relased twice
  // sem_post(sem) - this will allow the child to run
  sem_post(sem);
  // wait till child process finishes it's execution
  wait(NULL);

  printf("third\n");
  // close and unlink the semaphore - remove it from the filesystem - OS will not destroy it for us.
  // since the program will not get here due to deadlock, we must rm -rf the semaphore by ourself
  sem_close(sem);
  sem_unlink(sem_name);

  return 0;
}

