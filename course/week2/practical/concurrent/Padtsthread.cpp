#include <thread>
#include <iostream>
#include <mutex>

using namespace std;

////////////////////////////////////////////////////////////////////////////
class PDThread{

	void (*func)(void);
	void Init();

	public:
		PDThread(void(*)(void));
	    virtual ~PDThread();
	    virtual void Action() = 0;

	private:
		thread* _thread;
		
};

PDThread::PDThread(void (*exec)(void)){
	this->func = exec;
	// Passing to the thread
	_thread = new thread(func);
	this->Init();
}

void PDThread::Init(){
	cout<<"PDThread: Inside object starting thread: "<<_thread->get_id()<<endl;
	this->_thread->join();
}

PDThread::~PDThread(){
	//this->_thread->detach();
	delete _thread;
}
/////////////////////////////////////////////////////////////////////

class MyThread : PDThread {
	public:
		MyThread(void (*exec)(void)): PDThread(exec){}
		void Action();
};

void MyThread::Action(){

}
//////////////////////////////////////////////////////////////////////////
void hello(){
	cout<<"This is the function in a different thread\n";
}



int main(){
	MyThread dummy(hello);


	return 0;
}