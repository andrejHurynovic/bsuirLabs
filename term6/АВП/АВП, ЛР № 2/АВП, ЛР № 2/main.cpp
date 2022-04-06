//
//  main.cpp
//  АВП, ЛР № 2
//
//  Created by Andrej Hurynovič on 6.04.22.
//

#include <iostream>
#include <iomanip>
#include <memory>

using namespace std;

constexpr size_t maximalAssociativity = 20;

constexpr size_t elementSize = 64;
constexpr size_t cacheSize = 4194304;

constexpr uint64_t iterationsNumber = INT_MAX;
constexpr size_t maximalNumberOfBlocks = cacheSize / elementSize;

char* init(std::unique_ptr<char[]> &buffer, size_t associativity) {
    size_t blockSize = cacheSize / associativity;
    size_t blocksNumber = blockSize / elementSize;
    
    using element_t = uint8_t[elementSize];
    using block_t = element_t[maximalNumberOfBlocks];
    memset(buffer.get(), '\0', cacheSize * maximalAssociativity);
    
    block_t *cache = reinterpret_cast<block_t*>(buffer.get());
    
    for (size_t bankIndex = 0; bankIndex < associativity; ++bankIndex) {
        for (size_t blockIndex = 0; blockIndex < blocksNumber; ++blockIndex) {
            if (bankIndex < associativity - 1) {
                reinterpret_cast<uint64_t&>(cache[bankIndex][blockIndex]) = (blockIndex + ((bankIndex + 1) * maximalNumberOfBlocks)) * elementSize;
            }
        }
    }
    reinterpret_cast<uint64_t&>(cache[associativity - 1][blocksNumber - 1]) = 0;
    
    return reinterpret_cast<char*>(cache[0][0]);
}


int main() {
    chrono::steady_clock::time_point start, finish;
    unique_ptr<char[]> buffer(new char[maximalAssociativity * cacheSize]);
    
    cout << "|Associativity|Time (ms)|" << endl;
    
    uint64_t t = 0;
    for (size_t associativity = 1; associativity <= maximalAssociativity; ++associativity) {
        char *ptr = init(buffer, associativity);
        
        start = chrono::steady_clock::now();
        
        for (uint64_t k = 0; k < iterationsNumber; ++k) {
            t = reinterpret_cast<const uint64_t&>(ptr[t]);
        }
        
        finish = chrono::steady_clock::now();
        
        cout << "|" <<  setw(13) << associativity << "|" << setw(9) << chrono::duration_cast<chrono::milliseconds>(finish - start).count() << "|" << t << endl;
    }
}
