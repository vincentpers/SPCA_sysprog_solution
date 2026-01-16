#include "lib.h"

#include <stdalign.h>

/*
enum type {
  FIELD_TYPE_CHAR,
  FIELD_TYPE_INT,
  FIELD_TYPE_FLOAT,
  FIELD_TYPE_DOUBLE,
  FIELD_TYPE_POINTER,
};

struct field {
  enum type type;
  size_t offset;
};
*/

size_t compile(size_t num_fields, struct field *fields) {
  size_t offset = 0;
  size_t size;
  size_t max_size = 0;
  
  if (num_fields == 0) return 0;

  for (size_t i = 0; i < num_fields; ++i){
    if (FIELD_TYPE_CHAR == fields->type) size = 1; 
    else if (FIELD_TYPE_INT == fields->type) size = 4; 
    else if (FIELD_TYPE_FLOAT == fields->type) size = 4; 
    else if (FIELD_TYPE_DOUBLE == fields->type) size = 8; 
    else if (FIELD_TYPE_POINTER == fields->type) size = 8; 
    else assert(false);

    
    
    while (offset%size != 0){
      offset += 1;
    }
    
    fields->offset = offset;
    offset += size;

    if (max_size < size){
      max_size = size;
    }
    assert(max_size != 0);
    ++fields;
  }
  //assert(max_size > 0);
  while (offset%max_size != 0) offset += 1;
  
  return offset;
}
