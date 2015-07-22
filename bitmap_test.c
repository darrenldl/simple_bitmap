#include <stdio.h>
#include <stdlib.h>

#include "simple_bitmap.h"

int main (void) {
   
   map_block raw_map[get_bitmap_map_block_number(24)];
   simple_bitmap map;
   
   map_block new_raw_map[get_bitmap_map_block_number(16)];
   simple_bitmap new_map;
   
   map_block result;
   
   bit_index ret;
   
   bitmap_cont_group grp;
   
   // test init
   bitmap_init(&map, raw_map, NULL, 13, 0);
   
   bitmap_one(&map);
   
   bitmap_show(&map);
   bitmap_raw_show(&map);
   
   bitmap_init(&new_map, new_raw_map, NULL, 21, 0);
   
   // test write
   bitmap_write(&map, 14, 0x0);
   
   bitmap_show(&map);
   bitmap_raw_show(&map);
   
   raw_map[1] = 0x9F;
   bitmap_raw_show(&map);
   bitmap_count_zeros_and_ones(&map);
   
   bitmap_show(&map);
   bitmap_raw_show(&map);
   
   // test search
   raw_map[0] = 0xFF;
   raw_map[1] = 0x00;
   bitmap_count_zeros_and_ones(&map);
   
   printf("\n\n\nSearch test\n");
   bitmap_raw_show(&map);
   
   if (bitmap_first_zero_bit_index(&map, &ret, 14)) {
      printf("first zero bit index search failed!\n");
   }
   else {
      printf("first zero bit index search result : %d\n", ret);
   }
   
   if (bitmap_first_one_bit_index(&map, &ret, 14)) {
      printf("first one bit index search failed!\n");
   }
   else {
      printf("first one bit index search result : %d\n");
   }
   
   if (bitmap_first_one_cont_group(&map, &grp, 14)) {
      printf("first one cont group search failed!\n");
      bitmap_cont_group_show(&grp);
   }
   else {
      bitmap_cont_group_show(&grp);
   }
   
   if (bitmap_first_zero_cont_group(&map, &grp, 15)) {
      printf("first zero cont group search failed!\n");
      bitmap_cont_group_show(&grp);
   }
   else {
      bitmap_cont_group_show(&grp);
   }
   
   printf("ret : %d\n", ret);
   
   // test copy
   printf("\n\n\nCopy test\n");
   
   raw_map[1] = 0xF0;
   
   bitmap_show(&map);
   bitmap_raw_show(&map);
   
   if (bitmap_copy(&map, &new_map, 0, 1)) {
      printf("copy failed!\n");
   }
   bitmap_show(&new_map);
   bitmap_raw_show(&new_map);
   
   // test grow
   printf("\n\n\nGrow test\n");
   
   bitmap_show(&map);
   bitmap_raw_show(&map);
   
   bitmap_grow(&map, NULL, 22, 1);
   
   bitmap_show(&map);
   bitmap_raw_show(&map);
   
   // test shrink
   printf("\n\n\nShrink test\n");
   
   bitmap_show(&map);
   bitmap_raw_show(&map);
   
   bitmap_shrink(&map, NULL, 22);
   
   bitmap_show(&map);
   bitmap_raw_show(&map);
   
   printf("%02X %02X %02X\n", raw_map[0], raw_map[1], raw_map[2]);
   
   return 0;
}