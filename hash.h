#ifndef HASH_H
#define HASH_H

#include <iostream>
#include <cmath>
#include <random>
#include <chrono>

typedef std::size_t HASH_INDEX_T;

struct MyStringHash {
    HASH_INDEX_T rValues[5] { 983132572, 1468777056, 552714139, 984953261, 261934300 };
    MyStringHash(bool debug = true)
    {
        if(false == debug){
            generateRValues();
        }
    }
    // hash function entry point (i.e. this is h(k))
    HASH_INDEX_T operator()(const std::string& k) const
    {
        // Add your code here
        unsigned long long w[5];
        int numSix = k.size()/6;
        int remainingK = k.size()%6;
        for(int i = 0; i <= numSix; i++){
            unsigned long long a1 = letterDigitToNumber(k[k.size()-6-i*6]);
            unsigned long long a2 = letterDigitToNumber(k[k.size()-5-i*6]);
            unsigned long long a3 = letterDigitToNumber(k[k.size()-4-i*6]);
            unsigned long long a4 = letterDigitToNumber(k[k.size()-3-i*6]);
            unsigned long long a5 = letterDigitToNumber(k[k.size()-2-i*6]);
            unsigned long long a6 = letterDigitToNumber(k[k.size()-1-i*6]);
            w[4-i] = (((((a1*36+a2)*36+a3)*36+a4)*36+a5)*36+a6);
        }
        unsigned long long a[6];
        for(int i = 0; i < 6-remainingK; i++){
            a[i] = 0;
        }
        for(int i = 6-remainingK; i < 6; i++){
            a[i] = letterDigitToNumber(k[k.size()-numSix*6-remainingK+i-(6-remainingK)]);
        }
        w[4-numSix] = (((((a[0]*36+a[1])*36+a[2])*36+a[3])*36+a[4])*36+a[5]);
        for(int i = 0; i < 4-numSix; i++){
            w[i] = 0;
        }
        return rValues[0]*w[0] + rValues[1]*w[1] + rValues[2]*w[2] + rValues[3]*w[3] + rValues[4]*w[4];
    }

    // A likely helper function is to convert a-z,0-9 to an integral value 0-35
    HASH_INDEX_T letterDigitToNumber(char letter) const
    {
        // Add code here or delete this helper function if you do not want it
        letter = tolower(letter);
        if(letter>=65) return letter - 'a';
        return letter - '0' + 26;
    }

    // Code to generate the random R values
    void generateRValues()
    {
        // obtain a seed from the system clock:
        unsigned seed = std::chrono::system_clock::now().time_since_epoch().count();
        std::mt19937 generator (seed);  // mt19937 is a standard random number generator

        // Simply call generator() [it has an operator()] to get another random number
        for(int i{ 0 }; i < 5; ++i)
        {
            rValues[i] = generator();
        }
    }
};

#endif
