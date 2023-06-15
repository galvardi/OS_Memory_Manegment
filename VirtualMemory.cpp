#include "VirtualMemory.h"
#include "EX4_Resources/PhysicalMemory.h"
#include <cmath>
#include <algorithm>
#include <iostream>

struct virtualInfo{
    int length;
    uint64_t address;
};

struct maxDistPage{
    uint64_t v_address;
    uint64_t frame_pointer;
    uint64_t distance;
    uint64_t parent_frame;
};

word_t get_next_frame (virtualInfo &path_info, uint64_t page_swapped_in);
void get_address (uint64_t &virtualAddress, word_t &dest_frame);
void VMinitialize(){
  PMwrite (0,0);
  PMwrite (1,0);
}

unsigned int count_bits(uint64_t number)
{
  // log function in base 2
  // take only integer part
  // todo check if conversion works well long -> double
  return (int)log2(number)+1;
}

int get_root_bits_num(){
  int root_bits_num = VIRTUAL_ADDRESS_WIDTH % OFFSET_WIDTH;
  if (!root_bits_num) root_bits_num = OFFSET_WIDTH;
  return root_bits_num;
}


int split_address(uint64_t& virtualAddress, int shift){
  int bits_to_shift = count_bits(virtualAddress) - shift;
  uint64_t prefix = virtualAddress >> bits_to_shift;
  uint64_t mask = (1LL << (count_bits (virtualAddress) - shift) + 1) - 1;
  virtualAddress = virtualAddress & mask;
  return prefix;
}

bool check_empty_table(uint64_t frame){
  bool empty = true;
  word_t val;
  for (int i = 0; i < OFFSET_WIDTH; ++i)
  {
    PMread (frame * PAGE_SIZE + i, &val);
    empty = empty && val != 0;
  }
  return empty;
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
                  virtualInfo virtual_info,
                  uint64_t parent_frame,
                  uint64_t& max_frame_index,
                  uint64_t& page_swapped_in,
                  maxDistPage& max_page){
    if (virtual_info.length == VIRTUAL_ADDRESS_WIDTH)
    {
      // check max_dist and return;
      uint64_t dist_l = page_swapped_in - virtual_info.address;
      dist_l = dist_l > 0 ? dist_l : -dist_l;
      uint64_t dist_r = NUM_PAGES - dist_l;
      uint64_t cyclic_dist = dist_r < dist_l ? dist_r : dist_l;
      if (cyclic_dist > max_page.distance){
        max_page.distance = cyclic_dist;
        max_page.frame_pointer = frame_pointer;
        max_page.v_address = virtual_info.address;
        max_page.parent_frame = parent_frame;
      }
    }
    bool empty_table = true;
    word_t offset = OFFSET_WIDTH;
    if (virtual_info.length == 0){
      offset = get_root_bits_num();
    }
    for (int i = 0; i < offset; ++i){
      word_t child_p_frame;
      PMread(frame_pointer * PAGE_SIZE + i, &child_p_frame);
      max_frame_index = child_p_frame > max_frame_index ? child_p_frame :
                        max_frame_index; //todo check
      if (child_p_frame != 0){
        empty_table = false;
        uint64_t child_virtual_address = (virtual_info.length << offset) + i;
        virtualInfo child_virtual_info = {
            virtual_info.length + offset,
            child_virtual_address
        };
        uint64_t empty_table_index = traverse (child_p_frame,
                                               child_virtual_info,
                                               frame_pointer,
                                               max_frame_index,
                                               page_swapped_in,
                                               max_page);
        // if empty table found during traverse
        if (empty_table_index) {
          // unlink empty child if it's the father
          if (empty_table_index == child_p_frame){
            PMwrite (frame_pointer + i, 0);
          }
          return empty_table_index;
        }
      }
      if (empty_table){
        return frame_pointer;
      }
    }
    return 0;
  }

uint64_t get_address (uint64_t &virtualAddress, uint64_t& dest_frame)
{
  int root_bits_num = get_root_bits_num();
  int shift = root_bits_num;
  uint64_t offset_size = 1LL << OFFSET_WIDTH;
  word_t next_frame;
  virtualInfo path_info = {0, 0};
  uint64_t page_swapped_in = virtualAddress >> OFFSET_WIDTH;
  while (virtualAddress > (offset_size)){
    uint64_t offset = split_address (virtualAddress, shift);
    PMread(dest_frame * PAGE_SIZE + offset, &next_frame);
    // Page Fault
    if (next_frame == 0){
      next_frame = get_next_frame (path_info, page_swapped_in);
      // write the next_frame
      PMwrite (dest_frame + offset, next_frame);
      // init the next_frame table
      if (count_bits (virtualAddress) > OFFSET_WIDTH*2){
        for (int i = 0; i < PAGE_SIZE; i++){
          PMwrite (next_frame + i, 0);
        }
      }
    }
    dest_frame = next_frame;
  }
  return dest_frame * PAGE_SIZE + virtualAddress;
}
word_t get_next_frame (virtualInfo &path_info, uint64_t page_swapped_in)
{
  word_t next_frame;
  uint64_t max_frame_index = 0;
  maxDistPage max_page = {0,0,0};
  uint64_t empty_table_index = traverse (0, path_info, 0,
                                        max_frame_index,
                                        page_swapped_in,
                                        max_page);
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
    PMevict(max_page.v_address, max_page.frame_pointer * PAGE_SIZE);
    // todo: unlink father
    uint64_t page_link_address = max_page.parent_frame * PAGE_SIZE + (max_page
        .v_address % PAGE_SIZE);
    PMwrite(page_link_address, 0);
    next_frame = max_page.frame_pointer;
  }
  return next_frame;
}


int VMread(uint64_t virtualAddress, word_t* value){ //todo return success/ fail
  // check if virtual address is in range of VIRTUAL_ADDRESS_WIDTH
  // check for negative
  uint64_t dest_address = 0;
  get_address (virtualAddress, dest_address);
  // read the page
  PMread(dest_address, value);
  // todo: return success / failure
  std::cout << "read " << value << std::endl;
  return 0;
}

int VMwrite(uint64_t virtualAddress, word_t value){ //todo return success/ fail
  uint64_t dest_address = 0;
  get_address (virtualAddress, dest_address);
  PMwrite (dest_address, value);
  // todo: return success / failure
  std::cout << "write to " << value << std::endl;
  return 0;
}

