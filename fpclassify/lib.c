#include <assert.h>
#include <stdalign.h>
#include <stdbool.h>
#include <stdint.h>
#include <stdlib.h>
#include <string.h>

#include "lib.h"

#define SIGN_MASK ((unsigned)1<<31)
#define EXP_MASK ((unsigned)0xff<<23)
#define MANT_MASK ((unsigned)0x7fffff)



fp_class_t fpclassify(float value) {
  char * val = (char*) &value;
  unsigned v = ((unsigned) val[0] &0xff)<<0 | ((unsigned) val[1]&0xff)<<8 | ((unsigned) val[2]&0xff)<<16 | ((unsigned) val[3]&0xff)<<24;


  unsigned sign = (v & SIGN_MASK)>>31;// != 0x0;
  unsigned exp = (v & EXP_MASK)>>23;
  unsigned mant = (v & MANT_MASK);
  
  printf("sing: %01x\nexp: %02x\nmant: %06x\n", sign, exp, mant);
  
  if (exp == 0){
    if (mant == 0) return FP_ZERO;
    return FP_SUBNORMAL;
  }
  else if (exp == 0xff){
    if (mant == 0){
      return FP_INFINITE;
    }
    return FP_NAN;
  }
  else{
    //assert(false);
    return FP_NORMAL;
  }

}


/*
typedef enum {
  FP_NAN,
  FP_INFINITE,
  FP_NORMAL,
  FP_SUBNORMAL,
  FP_ZERO
} fp_class_t;
 
*/