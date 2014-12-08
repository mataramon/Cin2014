#ifndef DATA_H
#define DATA_H
#include <stdio.h>

typedef struct {
      long mtype;
      char mtext[1024]; // 1 K 
} PadtsMsg;

// This is the most basic obj
struct Greeter{
      const char* message;
      // vtable implementation
      void (*Hello)(struct Greeter*);	      
};

void SayHello(struct Greeter* self){
    printf("Hello %s\n", self->message);

}

#endif
