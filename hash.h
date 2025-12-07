#ifndef HASH_H
#define HASH_H

#include <iostream>
#include <cmath>
#include <random>
#include <chrono>
#include <ctime>
#include <cstdlib>

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
      if (k.empty()) return 0;

      unsigned long long w[5] = {0, 0, 0, 0, 0};

      int loc = static_cast<int>(k.size()) - 1;
      for (HASH_INDEX_T i = 4; i >= 0 && loc >= 0; i--) {
        unsigned long long power = 1;

        for (HASH_INDEX_T j = 0; j < 6 && loc >= 0; j++) {
          w[i] += letterDigitToNumber(k[loc]) * power;
          power *= 36;
          loc -= 1;
        }
      }

      HASH_INDEX_T result = 0;

      for (HASH_INDEX_T i = 0; i <= 4; i++) {
        result += rValues[i] * w[i];
      }

      return result;
    }

    // A likely helper function is to convert a-z,0-9 to an integral value 0-35
    HASH_INDEX_T letterDigitToNumber(char letter) const
    {
        // Add code here or delete this helper function if you do not want it
      HASH_INDEX_T number;
      
      if (letter >= 'A' && letter <= 'Z') {
        letter = static_cast<char>(letter - 'A' + 'a');
      }

      if (letter >= 'a' && letter <= 'z') {
        number = static_cast<HASH_INDEX_T>(letter - 'a');
      }
      else if (letter >= '0' && letter <= '9') {
        number = static_cast<HASH_INDEX_T>(letter - '0' + 26);
      }

      return number;
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
