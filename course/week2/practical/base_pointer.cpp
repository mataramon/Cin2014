#include <iostream>
#include <string>

using namespace std;

class Base {
    private:
	string name;

    protected:
	int a;

    public:
	Base(){name = "Base";}
	Base(string name){this->name = name;}
 	
<<<<<<< HEAD
      //  void hello(){cout<<"Hello from "<<name<<"\n";}
      //   virtual void  hello(){cout<<"Hello from "<<name<<"\n";}
         virtual void hello() = 0;
=======
        //void hello(){cout<<"Hello from "<<name<<"\n";}
        //virtual void hello(){cout<<"Hello from "<<name<<"\n";}
        virtual void hello() = 0;
>>>>>>> 17fb0e58523a1942346ca89b1f9cd0edcacdd63f
};

class Son : public Base {
    private:
	string name;

    protected:
	int b;

    public:
	Son(){name = "Son";}
	Son(string name){this->name = name;}
	void hello(){
            cout<<"Hello from "<<name<<"\n";
            //Base::hello();
            //cout<<"end Son---\n";
        }
};

class GrandSon : public Son{
    private:
	string name;
    
    protected:
	int c;
    
    public:
	GrandSon(){name = "GrandSon";}
	GrandSon(string name){this->name = name;}
	void hello(){cout<<"Hello from "<<name<<"\n";}
};

// Showing 
void show(Base*);

int main(){
    cout<<"Levels\n";
<<<<<<< HEAD
//    Base myBase;
    Son  mySon;
    GrandSon myGrandSon;

//    myBase.hello();
=======
    //Base myBase;
    Son  mySon;
    GrandSon myGrandSon;

    //myBase.hello();
>>>>>>> 17fb0e58523a1942346ca89b1f9cd0edcacdd63f
    mySon.hello();
    myGrandSon.hello();

    // Pointers
    cout<<"Base pointer [Son]\n";
    Base* ptr_base;
    Son*  ptr_son;

    ptr_base = &mySon;

    ptr_base->hello();
    cout<<"Base pointer [GrandSon]\n";
    ptr_base = &myGrandSon;
    ptr_base->hello();
    cout<<"Other pointer\n";
    ptr_son = &myGrandSon;
    ptr_son->hello();
    cout<<"---- Actions\n";
    //show(&myBase);
    show(&mySon);
<<<<<<< HEAD
    //show(&myGrandSon);    
=======
    show(&myGrandSon);    
>>>>>>> 17fb0e58523a1942346ca89b1f9cd0edcacdd63f

}

void show(Base* init){
     init->hello();

}

