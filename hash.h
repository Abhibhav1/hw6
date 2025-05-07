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
        static const int BASE = 36;
        unsigned long long words[5]={0,0,0,0,0};

        int w=4;
        for (int i= static_cast<int>(k.size());i>0 && w>=0;){
          const int wordlen=std::min(i,6);
          i-=wordlen;
          unsigned long long val=0;
          for (int j=0;j<wordlen;j++){
            val=val*BASE + letterDigitToNumber(k[i+j]);
          }
          words[w--]=val;
        }

        HASH_INDEX_T h=0;
        for (std::size_t i=0;i<5;i++){
          h+=rValues[i]*words[i];
        }
        return h;



    }

    // A likely helper function is to convert a-z,0-9 to an integral value 0-35
    HASH_INDEX_T letterDigitToNumber(char letter) const
    {
        // Add code here or delete this helper function if you do not want it
        letter=static_cast<char>(std::tolower(static_cast<unsigned char>(letter)));
        if ('a'<=letter && letter<='z') return letter-'a';
        if ('0'<=letter && letter<='9') return 26 + (letter-'0');
        return 0;
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
