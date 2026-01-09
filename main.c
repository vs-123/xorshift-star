#include <stdint.h>
#include <stdio.h>
#include <time.h>

typedef uint64_t u64;
typedef uint32_t u32;

u64 xorshift64star(u64 *state)
{
   u64 x = *state;
   x ^= x << 12;
   x ^= x >> 25;
   x ^= x << 27;
   *state = x;
   return x * 0x8A55AE51A34D786FULL;
}

u32 get_rand_range(u64 *state, u32 min, u32 max)
{
   u32 range        = max - min + 1;
   u64 random_32bit = (u32)xorshift64star(state);

   u64 multiresult = random_32bit * range;
   u32 leftover    = (u32)multiresult;

   if (leftover < range) {
      u32 threshold = -range % range;
      while (leftover < threshold) {
         random_32bit = (u32)xorshift64star(state);
         multiresult  = random_32bit * range;
         leftover     = (u32)multiresult;
      }
   }

   return (multiresult >> 32) + min;
}

int main(void)
{
   u64 seed = time(NULL) ^ (u64)&seed ^ (u64)main;

#define min 1u
#define max 100u

   u64 freq[max + 1] = {0};

   for (u32 i = 0; i < 1000000; i++) {
      u32 num = get_rand_range(&seed, min, max);
      freq[num - 1]++;
   }

   for (u32 i = 0; i < max; i++) {
      u32 num       = i + 1;
      u64 frequency = freq[i];

      printf("%u \t %llu times\n", num, frequency);
   }

   return 0;
}
