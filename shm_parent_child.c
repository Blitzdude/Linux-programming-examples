#include <sys/types.h>
#include <sys/ipc.h>
#include <sys/shm.h>

void main(int argc, char *argv[])
{
   int shmID, *shmPTR, status;
   pid_t pid;
   shmID = shmget( IPC_PRIVATE, 4*sizeof(int), IPC_CREAT | 0666 );
   shmPTR = (int *) shmat( shmID, NULL, 0 );
   shmPTR[0] = atoi( argv[0] ); 
   shmPTR[1] = atoi( argv[1] );
   shmPTR[2] = atoi( argv[2] ); 
   shmPTR[3] = atoi( argv[3] );
   if ((pid = fork()) == 0) {
      child(shmPTR);
      exit(0); 
   }
   wait(&status);
   shmdt((void *) shmPTR); 
   shmctl(shmID, IPC_RMID, NULL);
   exit(0);
}

void child(int sharedMem[])
{
   printf( "%d %d %d %d\n", sharedMem[0],
                                         sharedMem[1], 
                                         sharedMem[2], 
                                         sharedMem[3] );
}
