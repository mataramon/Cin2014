//
//  main.cpp
//  deassambly
//
//  Created by Angel Jovany Figueroa Ypiña on 11/8/14.
//  Copyright (c) 2014 Angel Jovany Figueroa Ypiña. All rights reserved.
//

#include <thread>
#include <iostream>
#include <map>
#include <vector>
#include <memory>

using namespace std;

// Generic function
long long factorial(int n){
    if (n){
        return n*factorial(n-1);
    }
    return 1;
}

void worker(int id, shared_ptr<map<int, long long>> results, shared_ptr<mutex> lck){
    //std::cout << "... Worker "<<id<<"\n";
    // calculating the thread
    auto fact = factorial(id);
    lck->lock();
    (*results)[id]=fact;
    lck->unlock();
}

int main(){
    
    std::vector<std::thread> threads;
    auto results = shared_ptr<map<int, long long>>(new std::map<int, long long>);
    auto Locker  = shared_ptr<mutex> (new std::mutex);
    
    for(int i = 0; i < 100; ++i){
        threads.push_back(std::thread(worker, i , results, Locker));
    }

    for(auto& thread : threads){
            thread.join();
    }
    
    for (auto& it: *results){
        std::cout<<" id "<<it.first<<" val :"<<it.second<<"\n";
    
    }
    
    return 0;
}