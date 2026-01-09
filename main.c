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
   return x * 0x2545F4914F6CDD1DULL;
}

u32 get_rand_range(u64 *state, u32 min, u32 max)
{
   u64 raw   = xorshift64star(state);
   u32 range = max - min + 1;

   return (u32)(raw % range) + min;
}

int main(void)
{
   u64 seed = time(NULL) ^ (u64)&seed ^ (u64)main;

#define min 1u
#define max 100u

   u64 freq[max + 1] = {0};

   for (u32 i = 0; i < 10000; i++) {
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
