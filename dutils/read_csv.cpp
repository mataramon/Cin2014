//
//  main.cpp
//  init
//
//  Created by Angel Jovany Figueroa Ypiña on 11/24/14.
//  Copyright (c) 2014 angel. All rights reserved.
//

#include <iostream>
#include "csv.h"

int main(int argc, const char * argv[])
{
    // Starting 
    const string filename = "Frames2.csv";    
    auto output = load_csv(filename);
    if (output.success){
         display_csv(output.data);       
    }else{
       cout<<"Error: "<<output.err<<"\n";
    } 
     
    return 0;
}


