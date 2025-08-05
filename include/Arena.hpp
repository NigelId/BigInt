#pragma once
#include <cstdint>
#include <cstring>

class Arena
{
   uint64_t *base = nullptr;
   size_t cap;
   size_t offset;

 public:
   Arena(size_t size) : cap(size), offset(0) { base = new uint64_t[cap]; }

   uint64_t *alloc(size_t size)
   {
      uint64_t *ptr = base + offset;
      offset += size;
      return ptr;
   }
   void reset() { offset = 0; }
   size_t mark() { return this->offset; }
   void rewind(size_t mark) { offset = mark; }
   ~Arena() { delete[] base; }
};
