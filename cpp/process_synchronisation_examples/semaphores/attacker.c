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
  // open named semaphore in the filesystem /dev/shm with permissions RW for the user (600)
  const char *sem_name = "my_amazing_named_semaphore";
  sem_t *sem = sem_open(sem_name, O_CREAT, 0600, 0);
  assert (sem != SEM_FAILED);

  // open unrelated process' semaphore, it can now continue doing it's job
  // IMPORTANT: Setting proper ACL for named semaphore is crucial, or somebody can mess with your synchronisation and cause fatal damage
  sem_post(sem);
  sem_close(sem);

  return 0;
}

