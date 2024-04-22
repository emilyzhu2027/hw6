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
        int string_len = (int)(k.size());
        int num_six_full = string_len / 6;
        int num_leftover = string_len % 6;
        unsigned long long sum = 0;

        if (num_leftover != 0){
            sum += rValues[5-num_six_full-1] * findWIndex(k.substr(0, num_leftover));
        }


        for (int i=1; i <= num_six_full; i++){
            std::string substr = k.substr((string_len - i*6), 6);
            sum += rValues[5-i] * findWIndex(substr);
        }

        return (HASH_INDEX_T)(sum);
    }

    // A likely helper function is to convert a-z,0-9 to an integral value 0-35
    HASH_INDEX_T letterDigitToNumber(char letter) const
    {
        // Add code here or delete this helper function if you do not want it
        int num = 0;
        if (letter >= 'A' && letter <= 'Z'){
            letter = (char)tolower(letter);
        }

        if (letter >= 'a' && letter <= 'z'){
            num = letter - 'a';
        }
        else if (letter >= '0' && letter <= '9'){
            num = letter - '0'+ 26;
        }

        return (HASH_INDEX_T)(num);
    }

    unsigned long long findWIndex(const std::string& sub_k) const
    {
        // Add your code here
        unsigned long long result = 0;
        int power = 1;
        for (int i = sub_k.size() - 1; i >= 0; --i) {
            result += letterDigitToNumber(sub_k[i]) * power;
            power *= 36;
        }

        return result;
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
