#include "VirtualMemory.h"
#include "EX4_Resources/PhysicalMemory.h"
#include <cmath>
#include <algorithm>
#include <iostream>

struct virtualAddress{
    int length;
    uint64_t address;
};

struct maxDistPage{
    uint64_t v_address;
    uint64_t frame_pointer;
    uint64_t distance;
    uint64_t parent_frame;
};


void VMinitialize(){
  for (int i = 0; i < OFFSET_WIDTH; ++i)
  {
    PMwrite (i,0);
  }
}

unsigned int count_bits(uint64_t number)
{
  unsigned int count = 0;
  for (;number > 0;count++){
    number = number >> 1;
  }
  return count;
}

int get_root_bits_num(){
  int root_bits_num = VIRTUAL_ADDRESS_WIDTH % OFFSET_WIDTH;
  if (!root_bits_num) root_bits_num = OFFSET_WIDTH;
  return root_bits_num;
}
/*
 * Returns the prefix of the binary number which is used as the offset
 * towards the next hirarchy.
 * Shifts the address number [shift] bits to the right
 * 001010 ->  01010 returns: 0  (OFFSET = 1)
 */
int split_address(virtualAddress& virtual_address, int shift){
  int bits_to_shift = virtual_address.length - shift;
  uint64_t prefix = virtual_address.address >> bits_to_shift;
  uint64_t mask = (1LL << (virtual_address.length - shift)) - 1;
  virtual_address.length -= shift;
  virtual_address.address = virtual_address.address & mask;
  return prefix;
}

uint64_t get_cyclic_dist (virtualAddress &virtual_info, const uint64_t
&page_swapped_in)
{
  uint64_t dist_l = page_swapped_in - virtual_info.address;
  dist_l = dist_l > 0 ? dist_l : -dist_l;
  uint64_t dist_r = NUM_PAGES - dist_l;
  uint64_t cyclic_dist = dist_r < dist_l ? dist_r : dist_l;
  return cyclic_dist;
}


/**
 * returns the empty table child if exists else 0
 * @param virtualAddress
 * @param frame_pointer
 * @param max_frame_index
 * @param ref_table
 * @param max_dist_page
 * @return
 */
uint64_t traverse(uint64_t frame_pointer,
                  virtualAddress virtual_info,
                  uint64_t parent_frame,
                  uint64_t& max_frame_index,
                  uint64_t& page_swapped_in,
                  maxDistPage& max_page,
                  uint64_t last_frame){
    if (virtual_info.length == VIRTUAL_ADDRESS_WIDTH - OFFSET_WIDTH)
    {
      // check max_dist;
      uint64_t cyclic_dist = get_cyclic_dist (virtual_info, page_swapped_in);
      if (cyclic_dist > max_page.distance){
        max_page.distance = cyclic_dist;
        max_page.frame_pointer = frame_pointer;
        max_page.v_address = virtual_info.address;
        max_page.parent_frame = parent_frame;
      }
      return 0;
    }
    bool empty_table = true;
    word_t offset = OFFSET_WIDTH;
    if (virtual_info.length == 0){
      offset = get_root_bits_num();
    }
    uint64_t loop_offset = 1LL << offset;
    for (int i = 0; i < loop_offset; ++i){
      word_t child_p_frame;
      PMread(frame_pointer * PAGE_SIZE + i, &child_p_frame);
      max_frame_index = child_p_frame > max_frame_index ? child_p_frame :
                        max_frame_index; //todo check
      if (child_p_frame != 0){
        empty_table = false;
        if (child_p_frame == last_frame) continue;
        uint64_t child_virtual_address = (virtual_info.address << offset) + i;
        virtualAddress child_virtual_info = {
            virtual_info.length + offset,
            child_virtual_address
        };
        uint64_t empty_table_index = traverse (child_p_frame,
                                               child_virtual_info,
                                               frame_pointer,
                                               max_frame_index,
                                               page_swapped_in,
                                               max_page,
                                               last_frame);
        // if empty table found during traverse
        if (empty_table_index) {
          // unlink empty child if it's the father
          if (empty_table_index == child_p_frame){
            PMwrite (frame_pointer * PAGE_SIZE + i, 0);
          }
          return empty_table_index;
        }
      }
    }
    if (empty_table){
      return frame_pointer;
    }
    return 0;
  }



word_t get_next_frame (virtualAddress &path_info,
                       uint64_t page_swapped_in,
                       uint64_t last_frame)
{
  word_t next_frame;
  uint64_t max_frame_index = 0;
  maxDistPage max_page = {0,0,0};
  uint64_t empty_table_index = traverse (0, path_info, 0,
                                         max_frame_index,
                                         page_swapped_in,
                                         max_page,
                                         last_frame);
  // 1. empty table
  if (empty_table_index){
    next_frame = empty_table_index;
  }
    // 2. unused frame
  else if (max_frame_index + 1 < NUM_FRAMES){
    next_frame = max_frame_index + 1;
  }
    // 3. swap out a page
  else{
    // evict
    PMevict(max_page.frame_pointer, max_page.v_address);
    // todo: unlink father
    uint64_t page_link_address = max_page.parent_frame * PAGE_SIZE + (max_page
                                                                          .v_address % PAGE_SIZE);
    PMwrite(page_link_address, 0);
    next_frame = max_page.frame_pointer;
  }
  return next_frame;
}


uint64_t get_address (uint64_t &_virtual_address, uint64_t& dest_address)
{
  int root_bits_num = get_root_bits_num();
  int shift = root_bits_num;
  uint64_t cur_frame = 0;
  word_t next_frame;
  virtualAddress path_info = {0, 0};
  virtualAddress virtual_address = {VIRTUAL_ADDRESS_WIDTH, _virtual_address};
  uint64_t page_swapped_in = _virtual_address >> OFFSET_WIDTH;
  uint64_t op_frame = 0;
  while (virtual_address.length > OFFSET_WIDTH){
    uint64_t offset = split_address (virtual_address, shift);
    PMread(cur_frame * PAGE_SIZE + offset, &next_frame);
    // Page Fault
    if (next_frame == 0){
      next_frame = get_next_frame (path_info, page_swapped_in, op_frame);
      op_frame = next_frame;
      // write the next_frame
      PMwrite (cur_frame * PAGE_SIZE + offset, next_frame);
      // init the next_frame table
      if (virtual_address.length >= OFFSET_WIDTH * 2){
        for (int i = 0; i < PAGE_SIZE; i++){
          PMwrite (next_frame * PAGE_SIZE + i, 0);
        }
      }
    }
    else op_frame = 0;
    cur_frame = next_frame;
  }
  dest_address = cur_frame * PAGE_SIZE + virtual_address.address;
}



int VMread(uint64_t virtualAddress, word_t* value){ //todo return success/ fail
  // check if virtual address is in range of VIRTUAL_ADDRESS_WIDTH
  // check for negative
  uint64_t dest_address = 0;
  get_address (virtualAddress, dest_address);
  // read the page
  PMread(dest_address, value);
  // todo: return success / failure
//  std::cout << "read " << value << std::endl;
  return 0;
}

int VMwrite(uint64_t virtualAddress, word_t value){ //todo return success/ fail
  uint64_t dest_address = 0;
  get_address (virtualAddress, dest_address);
  PMwrite (dest_address, value);
  // todo: return success / failure
//  std::cout << "write " << "value" << " to " << value << std::endl;
  return 0;
}

