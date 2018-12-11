/*
Author M Ravi Kumar
CS18MTECH11028
MTECH CSE IIT HYDERABAD
*/
#ifndef INCLUDE_BLOOM_FILTER_HPP
#define INCLUDE_BLOOM_FILTER_HPP

#include <iostream>
#include <stdint.h>
#include "MurmurHash3.h"
#include <vector>
#include <array>
using namespace std;


struct BloomFilter {
    BloomFilter(uint64_t size, uint8_t numHashes);
    void insert(const uint8_t *data, std::size_t len);
    bool probablyContains(const uint8_t *data, std::size_t len) const;
private:
    uint8_t numHashes;
    std::vector<bool> bit_arr; //Bit Array
};
//Bloom filter constructor
BloomFilter::BloomFilter(uint64_t size, uint8_t numHashes)
    : bit_arr(size),
    numHashes(numHashes) {}
//Hash array created using the MurmurHash3 code
uint64_t hash_otpt[2];
uint64_t * mumurhash(const uint8_t *data, std::size_t len)
{
    MurmurHash3_x64_128(data, len, 0, hash_otpt);
    return hash_otpt;
}
//We get two hash codes from MurmurHash3 fun and used double hashing for reducing collision
inline uint64_t bit_arr_index(int i,uint64_t hash1,uint64_t hash2,    uint64_t size) 
{
    //cout<<(hash1 + i * hash2) % size<<" ";
    return (hash1 + i * hash2) % size; 
}
//Adds an element to the  Bloom Filter
//For an element we get bit indexs   
void BloomFilter::insert(const uint8_t *data, std::size_t len) {
    auto hash_val = mumurhash(data, len);
    for (int i = 0; i < numHashes; i++)
    {
        //Set values to 1 in Bit Array
      bit_arr[bit_arr_index(i, hash_val[0], hash_val[1], bit_arr.size())] = true;
    }
}
//Returns true or false based on a probabilistic assesment of the array         using MurmurHash3
bool BloomFilter::probablyContains(const uint8_t *data, std::size_t   len) const {
    auto hash_val = mumurhash(data, len);
     //Computed bit indexs from   MurmurHash3 hash codes and check its boolean values
    for (int i = 0; i < numHashes; i++)
    {
        if (!bit_arr[bit_arr_index(i, hash_val[0], hash_val[1], bit_arr.size())])
        {
            return false;
        }
    }
    return true;
}

#endif
