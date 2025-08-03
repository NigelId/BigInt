#pragma once
#include <cstdint>
#include <cstring>

class Arena
{
   uint64_t *base;
   size_t cap;
   size_t offset;

 public:
   Arena(size_t size) : cap(size), offset(0) { base = new uint64_t[cap]; }

   uint64_t *alloc(size_t size)
   {
      if (offset + size > cap)
      {
         cap = offset + size;
         delete[] base;
         base = new uint64_t[cap];
      }
      uint64_t *ptr = base + offset;
      offset += size;
      return ptr;
   }
   void reset() { offset = 0; }
   ~Arena() { delete[] base; }
};
