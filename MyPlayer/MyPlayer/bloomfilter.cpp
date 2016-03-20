#include "bloomfilter.h"
//#include"bitcontainer.h"

typedef unsigned long ULONG;

ULONG BloomFilter::hashCode(const char *str, int n)
{
    ULONG seeds[] = {13,23,31,41,51,61,71,73,79,83,87}; //
    ULONG seed = seeds[n];
    ULONG hash = 0;

    while (*str)
    {
        hash = hash * seed + (*str++);
    }

    return (hash & 0x7FFFFFFF)% mem; //确保得到的值不会数组越界
}

bool BloomFilter::add(const char *str)
{
    if(NULL == str)
        return false;
    if(exists(str))
        return false;
    for(int i=0;i<k;++i)
    {
        ULONG hcode = hashCode(str,i);
        bitset.set(hcode);
    }
    return true;
}

bool BloomFilter::exists(const char* str)
{
    bool result=false;
    if(NULL == str)
        return result;
    for(int i=0;i<k;++i)
    {
        ULONG hc = hashCode(str,i);
        if(! bitset.test(hc))
        {
            return result;
        }
    }
    return true;
}
void BloomFilter::clean()
{
    bitset.clean();
}
