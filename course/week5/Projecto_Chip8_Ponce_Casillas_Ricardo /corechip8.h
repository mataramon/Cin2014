#ifndef CORECHIP8_h
#define CORECHIP8_h



using namespace std;

class CoreChip8 {

    private:
   
       unsigned short PC;            //Program Counter
       unsigned short I;             //Index Register
       unsigned short SP;            //Stack Pointer
       unsigned short Opcode;        //current Opcode

       unsigned char  V[16];         //V-register V0-VF
       unsigned char  Memory[4096];  //Size Memory
       unsigned short Stack[16];     //Stack 

       unsigned char  Delay_Timer;
       unsigned char  Sound_Timer;

    
    public:

       unsigned char Screen[64][32];
       unsigned char Keys[16];

       void init();
       void FDXemulate();
       void DecrementTimers();
       bool LoadGame(const char *filename);

       CoreChip8();
       ~CoreChip8();

};




#endif
