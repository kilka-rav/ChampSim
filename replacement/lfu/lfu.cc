#include <algorithm>
#include <cassert>
#include <map>
#include <vector>

#include "cache.h"

namespace replacement {

std::map<CACHE*, std::vector<uint64_t>> lfu;

}//namespace replacement

void CACHE::initialize_replacement() {
    replacement::lfu[this] = std::vector<uint64_t>(NUM_SET * NUM_WAY, 0);
}

uint32_t CACHE::find_victim(uint32_t triggering_cpu, uint64_t instr_id, uint32_t set, const BLOCK* current_set, uint64_t ip, uint64_t full_addr, uint32_t type) {
  auto begin = std::next(std::begin(replacement::lfu[this]), set * NUM_WAY);
  auto end = std::next(begin, NUM_WAY);
  auto victim = std::min_element(begin, end);
  return static_cast<uint32_t>(std::distance(begin, victim));
}

void CACHE::update_replacement_state(uint32_t triggering_cpu, uint32_t set, uint32_t way, uint64_t full_addr, uint64_t ip, uint64_t victim_addr, uint32_t type, uint8_t hit) {
  if (hit && access_type{type} != access_type::WRITE) {
    replacement::lfu[this].at(set * NUM_WAY + way) += 1;
  }
}

void CACHE::replacement_final_stats() {}