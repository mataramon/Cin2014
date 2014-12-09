/* Class 1
 /    What we have in structured programming
 /    1- There are functions and data 
 /    2- There are structures 
 /
 /  What is object oriented programming?
 /     How could we build this on c
 /     What are the differences between c and c++ 
 /     What is the meaning of pointers?
*/

#include <stdio.h>        // Standard io output library
#include <fcntl.h>        // Communication related libraries 
#include <stdlib.h>
#include <string.h>
#include <sys/types.h>
#include <sys/ipc.h>
#include <sys/msg.h>
#include <errno.h>
#include "data.h"

typedef struct {
    const char*  name;
    int          id;
    key_t        key;
}Sender;

// Function menu()
Sender init(const char*);    // Adquire resources
int    run(long, Sender*);  // execute what we need
unsigned int sizeof_string(char*);                     


int main(){
   /* Program explaination
         [Program A] ---> Sends a message to [Program B] */
   const char *name    = "token";
   Sender worker = init(name);
   printf("Queue ID %d\n", worker.id);
   int result = run(10, &worker);  
   return 0; 
}

Sender init(const char* name){
       // Adquiring resources
       Sender MySender;
       // Assignation                  
       MySender.name = name;
       MySender.id   = 0;
       key_t key;

       if ((key = ftok(MySender.name, 'B')) == -1){
           perror("Cannot create key for the message queue ");
           exit(1);
       } 

       MySender.key = key;

       if ((MySender.id = msgget(MySender.key, 0644 | IPC_CREAT)) == -1){
           perror("Cannot get the key and permission set for the queue");
           exit(1);
       }
     
       return MySender;
}

// err = 0 means success
// other wise -1 means error

int run(long type, Sender* MySender){
       unsigned int i = 0;
       int err        = 0;
       PadtsMsg queue;
       printf ("Enter a message for your partner, press Ctrl-D to exit\n");
       queue.mtype = type; // Type of message
       // Requiring information
       while (fgets(queue.mtext, sizeof(queue.mtext), stdin) != NULL) {
           int len = strlen(queue.mtext);
           if (queue.mtext[len-1] == '\n') queue.mtext[len-1] = '\0';

           if (msgsnd(MySender->id, &queue, len+1, 0) == 1) {
               perror("Cannot send message");
               err = 1; 
           }
           
       }

       if (msgctl(MySender->id, IPC_RMID, NULL) == -1){
             perror("Cannot close the queue");
             err = 1;
       }

       return err;
}

unsigned int sizeof_string(char *str){
      unsigned int size = 0;
      char* base_address = str;
      while(*base_address != '\0'){
          base_address++;
          size++;
      }
      return size;
}

