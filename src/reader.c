#include <stdio.h>
#include <string.h>
#include <sys/ipc.h>
#include <sys/shm.h>
#include <sys/types.h>

#define SHM_SIZE 1000

int main()
{
        // Read shared memory ket from stdin
        key_t shared_memory_key;
        if(scanf("%d", &shared_memory_key) != 1) {
                fprintf(stderr, "Bad input.\n");
                return -1;
        }

        // Get System V shared memory id
        int shared_memory_id = shmget(shared_memory_key, SHM_SIZE, 0600);
        if(shared_memory_id == -1) {
                fprintf(stderr, "Unable to access shared memory with this key.\n");
                return -1;
        }

        // Attach shared memory to the pointer
        char *shared_memory_ptr = (char*)shmat(shared_memory_id, NULL, 0);
        if(shared_memory_ptr == (void*)-1) {
                fprintf(stderr, "Unable to attach shared memory.\n");
                return -1;
        }

        // Copy string from shared memory
        char result_string[SHM_SIZE];
        strncpy(result_string, shared_memory_ptr, SHM_SIZE);
        result_string[SHM_SIZE-1] = '\0'; // just for safety

        // Detach&delete shared memory
        shmdt(shared_memory_ptr);
        shmctl(shared_memory_id, IPC_RMID, NULL);

        // Print string from shared memory
        puts(result_string);
        return 0;
}
