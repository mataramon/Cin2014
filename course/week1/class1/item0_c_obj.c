#include <stdio.h>
#include "data.h"

void Cool(struct Greeter*);

int main(){
    printf("Welcome!\n");
    struct Greeter MyGreeter;
    MyGreeter.message = "Lord I'm want to be an object";
    // Assigning the pointer to a different function
    MyGreeter.Hello = SayHello;
    MyGreeter.Hello(&MyGreeter);
    MyGreeter.Hello = Cool;
    MyGreeter.Hello(&MyGreeter);  
 
  return 0;
}

void Cool(struct Greeter* self){
    printf("Hello I'm a function in main so, what's up?\n");
}

