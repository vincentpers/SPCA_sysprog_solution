#include <assert.h>
#include <stdalign.h>
#include <stdbool.h>
#include <stdint.h>

#include "lib.h"

result_t access_memory(struct page_table *pt, va_t virtual_address,
                       action_type_t action, pa_t *physical_address) {

  //start
  /*
  | Bits | Description |
  | :--- | :--- |
  | **0-11** | Physical Page Number (PPN) |
  | **12** | Valid Bit (1 = Valid, 0 = Fault) |
  | **13** | Read Permission (1 = Allowed) |
  | **14** | Write Permission (1 = Allowed) |
  | **15** | Execute Permission (1 = Allowed) |
  */
  
  unsigned vpn = (virtual_address & ((1<<14)-1)<<8)>>8;
  unsigned vpo = (unsigned) virtual_address & ((1<<8)-1);

  unsigned entry = (unsigned) pt->entries[vpn];

  unsigned ppn = (entry & ((1<<12)-1));
  unsigned valid_bit = (entry & 1<<12);
  unsigned read_permission = (entry & (1<<13));
  unsigned write_permission = (entry & (1<<14));
  unsigned execute_permission = (entry & (1<<15));

  /*
  unsigned sum = ppn + valid_bit + read_permission + write_permission + vpn + vpo + execute_permission;
  printf("sum st. it comiles: %d\n", sum);
  */
  if (!valid_bit) return PAGE_FAULT;
  if (action == READ && !read_permission) return PERMISSION_DENIED;
  else if (action == WRITE && !write_permission) return PERMISSION_DENIED;
  else if (action == EXECUTE && !execute_permission) return PERMISSION_DENIED;
  
  *physical_address = 0;
  *physical_address = ppn<<8 | vpo;//<<20 & vpo;
  printf("pa: %08x\n", ppn<<8 | vpo);
  printf("PPN: %08x\n VPO: %08x\n",  ppn, vpo);
  return SUCCESS;


}
