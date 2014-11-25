//
//  csv.h
//  init
//
//  Created by Angel Jovany Figueroa Ypiña on 11/24/14.
//  Copyright (c) 2014 angel. All rights reserved.
//

#ifndef init_csv_h
#define init_csv_h

#include <iostream>
#include <vector>
#include <string>
#include <fstream>
#include <sstream>
#include <map>
#include <stdint.h>

using namespace std;

// Function Prototypes
vector<char> _string2charVec(string);
map<char, char> hex_map(void);
vector<string> split(const string &, char);

// Practice remember please
// in each function return if the function was successfull
// - Bool Success
// - Data
// - Error

template <class E>
struct result {
    bool success;
    E    data;
    string err;
};


// Equivalent between string and char hex value
map<char, char> hex_map(void){
    map<char, char> hex;
    hex['0'] = 0x0;
    hex['1'] = 0x1;
    hex['2'] = 0x2;
    hex['3'] = 0x3;
    hex['4'] = 0x4;
    hex['5'] = 0x5;
    hex['6'] = 0x6;
    hex['7'] = 0x7;
    hex['8'] = 0x8;
    hex['9'] = 0x9;
    hex['A'] = 0xA;
    hex['B'] = 0xB;
    hex['C'] = 0xC;
    hex['D'] = 0xD;
    hex['E'] = 0xE;
    hex['F'] = 0xF;
    
    return hex;
}

// Splits ech line with the delimeter
vector<string> &split_t(const string &line, char delimeter, vector<string> &items){
    stringstream ss(line);
    string item;
    while (getline(ss, item, delimeter)) {
        items.push_back(item);
    }
    return items;
}

vector<string> split(const string &line, char delimeter) {
    vector<std::string> elems;
    split_t(line, delimeter, elems);
    return elems;
}

vector<char> vec2char(const vector<string> &items){
    auto equivalents = hex_map();
    
    vector<char> chars;
    for(auto& e: items){
        // calculating char value
        char value = 0;
        bool add = false;
        //  F|F = 8 bits
        if (e.compare(" ") != 0){
            switch (e.size()){
                case 1:
                    if (equivalents.count(e[0]) > 0 ) add = true;
                    value = equivalents[e[0]];

                  break;
                case 2:
                    if (equivalents.count(e[0]) > 0 && equivalents.count(e[1]) > 0) add = true;
                    value = equivalents[e[1]] + (equivalents[e[0]] << 4);
                  break;
              default:
                  cout<<"Warning: invalid char size returning 0\n";
           }
           if (add) chars.push_back(value);
       }
    }
    
    return chars;
}

// Returns a vector with vectors of chars
result<vector<vector<char>>> load_csv(string location){
    // Declaration
    result<vector<vector<char>>> MyResult;
    MyResult.success = false;
    MyResult.err     = "";
    string line;
    ifstream file (location);
    //
    if (file.is_open()){
        while ( getline (file, line)){
            // Parser to convert the char to str
            auto row = _string2charVec(line);
            MyResult.data.push_back(row);
        }
        MyResult.success = true;
        
    }else{
       MyResult.err = "load_csv: Error cannot load file";
    }
    
    return MyResult;
}

// Converts the line to characters
vector<char> _string2charVec(string line){
    // Declaration
    vector<char> row;
    // Split the str into ,
    vector<string> items = split(line, ',');
    row = vec2char(items);
    return row;
}

void display_csv(const vector<vector<char>> items){
     cout<<"Rows: "   <<items.size()<<"\n";
     cout<<"Columns: "<<items[0].size()<<"\n";             
     for (auto& row: items){
        cout<<"# ";
        for(auto& i: row){
           printf("%x", i & 0xff);
        }
        cout<<endl;
     }
}

#endif
