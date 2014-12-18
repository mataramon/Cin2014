//
//  main.cpp
//  test
//
//  Created by Angel Jovany Figueroa Ypiña on 11/6/14.
//  Copyright (c) 2014 Angel Jovany Figueroa Ypiña. All rights reserved.
//      g++ -std=c++11 -pthread
//      clang++ -std=c++11 -stdlib=libc++

// Atomics 


#include <iostream>
#include <thread>
#include <vector>
#include <atomic>
using namespace std;
/*
void hello(atomic<int> *item, int i){
    (*item)++;
    for (int c = 0; c < 3 ;c++)
        cout << "Thread ID [" << this_thread::get_id() << "] i: ["<<i<<"] Counter ["<<*item<<"]\n";

}
*/
void hello(int *item, int i){
    (*item)++;
    for (int c = 0; c < 3 ;c++)
        cout << "Thread ID [" << this_thread::get_id() << "] i: ["<<i<<"] Counter ["<<*item<<"]\n";

}

// Main execution
int main(){
    // atomic
    atomic<int> ourInt(-1);
    auto j = new int;
    *j = 0; 

    // Here you create a vector of threads
    vector<std::thread> threads;
    // Filling the vector of threads (as it is a pool of threads)
    for(int i = 0; i < 55000; ++i){
        threads.push_back(thread(hello, j, i));
    }
    // For each thread in vector
    for(auto& thread : threads){
        // Start the thread
        thread.join();
    }

    cout<<"Final value: "<<ourInt.load()<<"\n";
    cout<<"Final value int: "<<*j<<"\n";

    delete j;

    return 0;
}