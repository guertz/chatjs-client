#include <iostream>
#include <algorithm>

#include <vector>
#include <cassert>

/**
 *  @brief Definizione metodi per generare stringhe caratteri uniche
 *  @file uuid.cc
 */

using namespace std;

namespace UUID {
    typedef vector<std::string> Tokens;

    static Tokens tokens;

    std::string generate() {

        static const char alphanum[] =
            "0123456789"
            "ABCDEFGHIJKLMNOPQRSTUVWXYZ"
            "abcdefghijklmnopqrstuvwxyz";

        string unique;

        // automatically \0 at bottom ?
        for (int i = 0; i < 8; ++i) {
            unique.insert(0, 1, alphanum[rand() % (sizeof(alphanum) - 1)]);
        }

        // atomic?
        Tokens::iterator tk_itr = std::find(tokens.begin(), tokens.end(), unique);
        assert(tk_itr ==  tokens.end());
        
        tokens.push_back(unique);

        return unique;

    }
}