// ConsoleApplication1.cpp : Defines the entry point for the console application.
//

#include <iostream>
#include <thread>
#include <vector>
#include <mutex>
#include <memory>
#include "generics.h"

using namespace std;
using namespace algebra;

#define N 100 

void worker(vector<int*> A, vector<int*> B, int id, int length, shared_ptr<mutex> lck){
    // The worker will take the id row
    // and will multiply row A * row B
    
    int result = dot<int>(A[id], B[id], length);
    //lck->lock();
    cout << "Worker "<<id<<" :"<< result<<"\n";
    //lck->unlock();
}



int main(){

    // Matrix row dot row
    auto iMatrix = generate_matrix<int>(N, N, gen_int);
    auto biMatrix = generate_matrix<int>(N, N, gen_int);

    // generics
    auto dMatrix = generate_matrix<double>(N, N, gen_double);
    auto cMatrix = generate_matrix<char>(N, N, gen_char);
    auto jMatrix = generate_matrix<j<int>>(N, N, gen_jint);

    // Showing matrix elements
    display_matrix<int>(iMatrix, N);
    display_matrix<double>(dMatrix, N);
    display_matrix<char>(cMatrix, N);
    display_matrix<j<int>>(jMatrix, N);

    // Starting threads
    vector<thread> myPool;
    auto Lock = shared_ptr<mutex>(new mutex);

    for (int i = 0; i < N; i++){
        myPool.push_back(thread(worker, iMatrix, biMatrix, i, N, Lock));
    }


    for (auto&thread : myPool){
        thread.join();
    }

    //system("PAUSE");

    return 0;
}
