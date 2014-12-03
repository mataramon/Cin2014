#include <iostream>
#include <string>
#include <ncurses.h>                                                  

namespace cinves {
   void cout(std::string term){  
        std::cout<<"playing from cinves "<<term; 
   }	
}

int main(){
    std::cout<<"hello world\n";
    cinves::cout("hello world\n");
    
    initscr();
    start_color();

    endwin();

}
