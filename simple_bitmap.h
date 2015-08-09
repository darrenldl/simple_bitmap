/* simple bitmap library
 * Author : darrenldl <dldldev@yahoo.com>
 * 
 * Version : 0.05
 * 
 * Note:
 *    simple bitmap is NOT thread safe
 * 
 * License:
 * This is free and unencumbered software released into the public domain.
 *
 * Anyone is free to copy, modify, publish, use, compile, sell, or
 * distribute this software, either in source code form or as a compiled
 * binary, for any purpose, commercial or non-commercial, and by any
 * means.
 * 
 * In jurisdictions that recognize copyright laws, the author or authors
 * of this software dedicate any and all copyright interest in the
 * software to the public domain. We make this dedication for the benefit
 * of the public at large and to the detriment of our heirs and
 * successors. We intend this dedication to be an overt act of
 * relinquishment in perpetuity of all present and future rights to this
 * software under copyright law.
 * 
 * THE SOFTWARE IS PROVIDED "AS IS", WITHOUT WARRANTY OF ANY KIND,
 * EXPRESS OR IMPLIED, INCLUDING BUT NOT LIMITED TO THE WARRANTIES OF
 * MERCHANTABILITY, FITNESS FOR A PARTICULAR PURPOSE AND NONINFRINGEMENT.
 * IN NO EVENT SHALL THE AUTHORS BE LIABLE FOR ANY CLAIM, DAMAGES OR
 * OTHER LIABILITY, WHETHER IN AN ACTION OF CONTRACT, TORT OR OTHERWISE,
 * ARISING FROM, OUT OF OR IN CONNECTION WITH THE SOFTWARE OR THE USE OR
 * OTHER DEALINGS IN THE SOFTWARE.
 * 
 * For more information, please refer to <http://unlicense.org/>
 */

#ifndef SIMPLE_BITMAP_H
#define SIMPLE_BITMAP_H


// uncomment the following line to force simple bitmap to shut up,
// and use minimal number of libraries

//#define SIMPLE_BITMAP_SILENT

#ifdef SIMPLE_BITMAP_SILENT
   #define printf(...)
#endif

#ifndef SIMPLE_BITMAP_SILENT
   #include <stdio.h>
#endif

#include <stdint.h>

#include <limits.h>

#include "simple_something_error.h"

#define get_bitmap_map_block_number(size_in_bits)   ((size_in_bits) / MAP_BLOCK_BIT + (((size_in_bits) % MAP_BLOCK_BIT) == 0 ? 0 : 1))
#define get_bitmap_map_block_index(bit_index)       ((bit_index) / (MAP_BLOCK_BIT))
#define get_bitmap_map_block_bit_index(bit_index)   ((bit_index) % (MAP_BLOCK_BIT))

#define MAP_BLOCK_BIT   CHAR_BIT

typedef unsigned char map_block;    // map block must be unsigned
typedef struct simple_bitmap simple_bitmap;
typedef uint_fast32_t bit_index;
typedef struct bitmap_cont_group bitmap_cont_group;

struct simple_bitmap {
   map_block* base;
   map_block* end;
   bit_index length;
   
   bit_index number_of_zeros;
   bit_index number_of_ones;
};

struct bitmap_cont_group {
  map_block bit_type;
  bit_index start;
  bit_index length;
};

/* default value :
 *    0 - overwrite space with 0s
 *    1 - overwrite space with 1s
 *   >1 - leave the space as it is
 */
int bitmap_init   (simple_bitmap* map, map_block* base, map_block* end, uint_fast32_t size_in_bits, map_block default_value);

int bitmap_zero   (simple_bitmap* map);
int bitmap_one    (simple_bitmap* map);

int bitmap_read   (simple_bitmap* map, uint_fast32_t index, map_block* result);
int bitmap_write  (simple_bitmap* map, uint_fast32_t index, map_block input_value);

int bitmap_first_one_bit_index   (simple_bitmap* map, uint_fast32_t* result, bit_index skip_to_bit);
int bitmap_first_zero_bit_index  (simple_bitmap* map, uint_fast32_t* result, bit_index skip_to_bit);

int bitmap_first_one_cont_group     (simple_bitmap* map, bitmap_cont_group* ret_grp, bit_index skip_to_bit);
int bitmap_first_zero_cont_group    (simple_bitmap* map, bitmap_cont_group* ret_grp, bit_index skip_to_bit);

// backward version of the searching functions
/* Note:
 *    for index searching functions, the indexing follow as above ones(from left to right)
 *    for continuous group searching functions,
 *    the indexing and direction follow as above ones(from left to right)
 */
int bitmap_first_one_bit_index_back   (simple_bitmap* map, uint_fast32_t* result, bit_index skip_to_bit);
int bitmap_first_zero_bit_index_back  (simple_bitmap* map, uint_fast32_t* result, bit_index skip_to_bit);

int bitmap_first_one_cont_group_back     (simple_bitmap* map, bitmap_cont_group* ret_grp, bit_index skip_to_bit);
int bitmap_first_zero_cont_group_back    (simple_bitmap* map, bitmap_cont_group* ret_grp, bit_index skip_to_bit);

int bitmap_count_zeros_and_ones (simple_bitmap* map);

// both maps must be initialised
int bitmap_copy (simple_bitmap* src_map, simple_bitmap* dst_map, unsigned char allow_truncate, map_block default_value);

// no data checks, only copying
int bitmap_meta_copy (simple_bitmap* src_map, simple_bitmap* dst_map);

// map must be initialised
// this function does not handle memory management issues
/* default value :
 *    0 - overwrite space with 0s
 *    1 - overwrite space with 1s
 *   >1 - leave the space as it is
 */
int bitmap_grow (simple_bitmap* map, map_block* end, uint_fast32_t size_in_bits, map_block default_value);
int bitmap_shrink (simple_bitmap* map, map_block* end, uint_fast32_t size_in_bits);

int bitmap_show (simple_bitmap* map);
int bitmap_cont_group_show (bitmap_cont_group* grp);
int bitmap_raw_show (simple_bitmap* map);

#endif