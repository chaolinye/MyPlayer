#ifndef BITCONTAINER_H
#define BITCONTAINER_H
#include<iostream>
#include<memory.h>
class BitContainer{
public:
    typedef unsigned char BLOCK_TYPE;
    typedef unsigned long INDEX_TYPE;

    static const unsigned int BLOCK_BYTE=sizeof(BLOCK_TYPE);
    static const unsigned int BLOCK_BITS=BLOCK_BYTE<<3;
    static const BLOCK_TYPE MASK=1;
public:
    BitContainer(const INDEX_TYPE size=1000000)
    {
        blocks=(size-1)/BLOCK_BITS+1;
        bits=new BLOCK_TYPE[blocks];
        clean();

    }
    ~BitContainer(){
        if(NULL!=bits)
        {
            delete[]bits;
            bits=NULL;
        }
    }
    void clean()
    {
        memset(bits,0,blocks*BLOCK_BYTE);
    }
    bool set(INDEX_TYPE pos,bool tof=true)
    {
        if(pos<0||pos>=blocks*BLOCK_BITS)
        {
            return false;
        }
        INDEX_TYPE block=pos/BLOCK_BITS;
        unsigned int offset=pos%BLOCK_BITS;
        if(tof)
        {
            bits[block]|=MASK<<offset;
        }
        else
        {
            bits[block]&=~(MASK<<offset);
        }
        return true;
    }
    bool test(INDEX_TYPE pos)
    {
        if(pos<0||pos>=blocks*BLOCK_BITS)
        {
            return false;
        }
        INDEX_TYPE block=pos/BLOCK_BITS;
        unsigned int  offset=pos%BLOCK_BITS;
                if(0 < (bits[block] & (MASK << offset)))
                    return true;
                else
                    return false;
    }
    INDEX_TYPE size()const
      {
          return blocks*BLOCK_BITS;
      }
  private:
      INDEX_TYPE blocks;
      BLOCK_TYPE* bits;

};

#endif // BITCONTAINER_H
