#include <assert.h>
#include <stdalign.h>
#include <stdbool.h>
#include <stdint.h>
#include <stdlib.h>
#include <string.h>

#include "lib.h"

endianness_t get_system_endianness() {
  int *i;
  int a = 0x1;
  i = &a;
  char * first = (char *)i;
  if (*first == 0x0) return BIG_ENDIAN;
  else return LITTLE_ENDIAN;
  return OTHER_ENDIAN;
}

uint16_t swap_u16(uint16_t val) {
  return (val >> 8) | (val << 8);
  
  char * n = (char*) &val;
  uint16_t vres = 0;
  //printf("%04x\n", (uint16_t)( n[1]<<8));
  vres |= (uint16_t) (n[0])<<8;
  vres |=  0x00ff & n[1];
  return vres;
}

uint32_t swap_u32(uint32_t val) {
  uint32_t res = 0;
  uint16_t* vals = (uint16_t *) &val;
  res |= ((uint32_t)swap_u16(vals[0]))<<16;
  res |= 0x0000ffff & swap_u16(vals[1]);

  return res;
}

uint64_t swap_u64(uint64_t val) {
  uint64_t res = 0;
  uint32_t * vals = (uint32_t *) &val;
  res |= ((uint64_t) swap_u32(vals[0]))<<32;
  res |= 0xffffffff & swap_u32(vals[1]);
  return res;
}
