//
//  main.cpp
//  KR
//
//  Created by Vlad Gordiichuk on 4/3/19.
//  Copyright © 2019 Vlad Gordiichuk. All rights reserved.
//

#include <iostream>
#include <fstream>
#include <stdlib.h>
using namespace std;

void writeIntAsStringToFile(int value, char* c) {
    const char *ones[20] = {"zero", "one", "two", "three", "four", "five", "six", "seven", "eight", "nine", "ten", "eleven", "twelve", "thirteen", "fourteen", "fifteen", "sixteen", "seventeen", "eighteen", "nineteen"};
    const char *tens[10] = {"", "ten", "twenty", "thirty", "forty", "fifty", "sixty", "seventy", "eighty", "ninety"};
    
    if (value == 1000000) {
        writeIntAsStringToFile(value / 1000000, c);
        strcpy(c, " million");
    } else if (value >= 1000) {
        writeIntAsStringToFile(value / 1000, c);
        strcat(c, " thousand");
        if (value % 1000) {
            if (value % 1000 < 100)
                strcat(c, " and");
            strcat(c, " ");
            writeIntAsStringToFile(value % 1000, c);
        }
    } else if (value >= 100) {
        writeIntAsStringToFile(value / 100, c);
        strcat(c, " hundred");
        if (value % 100) {
            strcat(c, " and ");
            writeIntAsStringToFile(value % 100, c);
        }
    } else if (value >= 20) {
        strcat(c, tens[value / 10]);
        if (value % 10) {
            strcat(c, " ");
            writeIntAsStringToFile(value % 10, c);
        }
    } else {
        strcat(c, ones[value]);
    }
}

int main() {
    ifstream file ("numbers.txt");
    char ch;
    int *array = new int(100);
    bool next = true;
    
    
    int countArray = 0;
    
    if (file.is_open()) {
        while (file.get(ch)) {
            if (ch >= '0' && ch <= '9') {
                if (next) {
                    array[countArray++] = 0;
                    array[countArray - 1] = (ch - '0');
                } else {
                    array[countArray - 1] *= 10;
                    array[countArray - 1] += (ch - '0');
                }
                next = false;
            } else {
                next = true;
            }
        }
        file.close();
    } else
        cout << "Could not open file" << endl;
    
    for (int i = 0; i < countArray; i++) {
        char *c = new char[1000];
        writeIntAsStringToFile(array[i], c);
        
        char number_str_value[10];
        sprintf(number_str_value, "%d", array[i]);
        
        ofstream file (strcat(number_str_value, ".txt"));
        file << c;
    }
    
    return 0;
}
