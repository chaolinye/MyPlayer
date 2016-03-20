#ifndef BLOOMFILTER_H
#define BLOOMFILTER_H

#include <cmath>
#include "bitcontainer.h"

class BloomFilter
{
public:
    typedef unsigned long ULONG;
    BitContainer bitset;//a bit array
public:
    BloomFilter(const ULONG maxElemNum=1000,const double errRate=0.01):
      bitset(BitContainer((ULONG)(log(1/errRate)*maxElemNum*2))),
      mem((ULONG)(log(1/errRate)*maxElemNum*2))
      {
          k=(int)(0.7*mem/maxElemNum);
      }
    bool add(const char* str);
    bool exists(const char* str);
    ULONG hashCode(const char* str, int n);
    void clean();
private:

    int k;//number of hash functions to be used
    ULONG mem;//bits of memory need in bitContainer
};

#endif // BLOOMFILTER_H
