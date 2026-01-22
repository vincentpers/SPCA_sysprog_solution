#include <assert.h>
#include <stdalign.h>
#include <stdbool.h>
#include <stdint.h>
#include <stdlib.h>
#include <string.h>

#include "lib.h"

/*
typedef struct {
  void *data;
  size_t capacity;
  size_t item_size;

  size_t index;
} stack_t;
 */
void sstack_init(stack_t *stack, size_t capacity, size_t item_size) {
  stack->data = (void *) malloc(capacity * item_size);
  if (stack->data == NULL) assert(false && "No place found for the data in sstack_init");
  stack->capacity = capacity;
  stack->item_size = item_size;
  stack->index = 0;
}

void sstack_destroy(stack_t *stack) {
  free(stack->data);
  stack->data = NULL;
  stack->capacity = 0;
  stack->item_size = 0;
  stack->index = 0;
}

bool sstack_is_empty(const stack_t *stack) {
  //assert(!(bool) stack->index == (stack->index == 0));

  return !(bool) stack->index;
}

bool sstack_is_full(const stack_t *stack) {
  if (stack->capacity == 0) return true;
  return (stack->index == (stack->capacity));
}

bool sstack_push(stack_t *stack, const void *item) {
  if (sstack_is_full(stack)) return false;
  memcpy(((char *) stack->data + (int)(stack->index * stack->item_size)), item, stack->item_size);
  stack->index = stack->index + 1;

  return true;
}

bool sstack_pop(stack_t *stack, void *item) {
  if (sstack_is_empty(stack)) return false;
  stack->index = stack->index -1;;
  memcpy(item, ((char *) stack->data + (int)(stack->index * stack->item_size)), stack->item_size);
  
  /*
  void * p = calloc(100, 100);
  memcpy((void *) ((char *) stack->data + (int)(stack->index * stack->item_size)), p, stack->item_size);
  free(p);
  */
  return true;
}

size_t sstack_size(const stack_t *stack) {
  return stack->index;
}

size_t sstack_capacity(const stack_t *stack) {
  return stack->capacity;
}

void sstack_clear(stack_t *stack) {
  stack->index = 0;
}
