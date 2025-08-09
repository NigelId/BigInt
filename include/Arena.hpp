#pragma once
#include <cstdint>
#include <cstring>
#include <stdexcept>

class Arena
{
   uint64_t *base = nullptr;
   size_t cap;
   size_t offset;

 public:
   Arena(size_t size) : cap(size), offset(0) { base = new uint64_t[cap]; }

   uint64_t *alloc(size_t size)
   {
      if (size > cap)
      {
         throw std::out_of_range("allocating memory outside arena's capacity");
      }
      uint64_t *ptr = base + offset;
      offset += size;
      return ptr;
   }
   size_t mark() const { return this->offset; }

   void jump_to(size_t mark)
   {
      if (mark > cap)
      {
         throw std::out_of_range("jumping to elements outside arena's range");
      }
      offset = mark;
   }
   uint64_t *now() const { return base; }
   void reset() { offset = 0; }
   ~Arena() { delete[] base; }
};
