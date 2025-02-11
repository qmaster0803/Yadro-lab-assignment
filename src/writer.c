#include <stdlib.h>
#include <stdio.h>
#include <sys/types.h>
#include <sys/ipc.h>
#include <sys/shm.h>
#include <string.h>

#define SHM_SIZE 1000
#define SHM_MSG  "Hello world!"

int main()
{
        key_t shared_memory_key;
        int shared_memory_id;
        while(1) {
                // Generate random System V shared memory key
                shared_memory_key = (rand() % 100000);

                // Test this key for collisions
                shared_memory_id = shmget(shared_memory_key, SHM_SIZE, IPC_CREAT | IPC_EXCL | 0600);
                if(shared_memory_id != -1)
                        break;
                else
                        fprintf(stderr, "Got shared key collision, retrying...\n");
        }

        // Attach System V shared memory to pointer
        char *shared_memory_ptr = (char*)shmat(shared_memory_id, NULL, 0);
        if(shared_memory_ptr == (void*)-1) {
                fprintf(stderr, "Shared memory attachment failed.\n");
                return -1;
        }

        // Copy string to the shared memory
        strcpy(shared_memory_ptr, SHM_MSG);

        // Detach shared memory
        shmdt(shared_memory_ptr);

        printf("%d\n", shared_memory_key);
        
        return 0;
}
