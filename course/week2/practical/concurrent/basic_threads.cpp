//
//  main.cpp
//  test
//
//  Created by Angel Jovany Figueroa Ypiña on 11/6/14.
//  Copyright (c) 2014 Angel Jovany Figueroa Ypiña. All rights reserved.
//      g++ -std=c++11 -pthread
//      clang++ -std=c++11 -stdlib=libc++

#include <iostream>
#include <thread>
#include <vector>

void hello(){
    std::cout << "Hello Thread " << std::this_thread::get_id() << std::endl;
}
// Main execution
int main(){

    // Here you create a vector of threads
    std::vector<std::thread> threads;
    // Filling the vector of threads (as it is a pool of threads)
    for(int i = 0; i < 10; ++i){
        threads.push_back(std::thread(hello));
    }
    // For each thread in vector
    for(auto& thread : threads){
        // Start the thread
        thread.join();
    }

    return 0;
}