#include <stdio.h>
#include <stdlib.h>
#include <errno.h>
#include <sys/types.h>
#include <sys/ipc.h>
#include <sys/msg.h>
#include "data.h"

int main(void)
{
    PadtsMsg queue;
    int msqid;
    key_t key;

    if ((key = ftok("token", 'B')) == -1) {  
        perror("cannot access to the token file");
        exit(1);
    }

    if ((msqid = msgget(key, 0644)) == -1) { 
        perror("cannot connect to the queue");
        exit(1);
    }
    
    printf("Listener: this is what i found:\n");

    for(;;) { 
        if (msgrcv(msqid, &queue, sizeof(queue.mtext), 0, 0) == -1) {
            perror("Error receiving message");
            exit(1);
        }
        printf("Message: \"%s\"\n", queue.mtext);
    }

    return 0;
}
