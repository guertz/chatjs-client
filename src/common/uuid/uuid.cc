#include <iostream>
#include <algorithm>

#include <vector>
#include <cassert>

#include "common/logger/logger.h"

/**
 *  @brief Definizione metodi per generare stringhe caratteri uniche
 *  @file uuid.cc
 */

using namespace std;

namespace UUID {
    typedef vector<std::string> Tokens;

    static Tokens tokens;

    // atomic?
    std::string generate() {

        static const char alphanum[] =
            "0123456789"
            "ABCDEFGHIJKLMNOPQRSTUVWXYZ"
            "abcdefghijklmnopqrstuvwxyz";

        Tokens::iterator tk_itr = tokens.end();
        string unique;

        while(tk_itr !=  tokens.end()) {
            
            log_base(TAG::INF, "UUID::generate", ((unique.size() > 0) ? 
                                                (unique + " (duplicate found)") 
                                                    : 
                                                "" 
                                              ));

            unique = "";

            for (int i = 0; i < 10; ++i) {
                unique.insert(0, 1, alphanum[rand() % (sizeof(alphanum) - 1)]);
            }

            tk_itr = std::find(tokens.begin(), tokens.end(), unique);
        }
        
        tokens.push_back(unique);

        return unique;

    }
}