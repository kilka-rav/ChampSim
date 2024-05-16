#include "msl/fwcounter.h"
#include "ooo_cpu.h"


void O3_CPU::initialize_branch_predictor() {}

uint8_t O3_CPU::predict_branch(uint64_t ip)
{
    auto&& currentInstr = input_queue.front();
    if (currentInstr.is_branch && currentInstr.branch_type == BRANCH_CONDITIONAL) {
        return currentInstr.branch_taken;
    }
    return 1;
}

void O3_CPU::last_branch_result(uint64_t ip, uint64_t branch_target, uint8_t taken, uint8_t branch_type)
{

}
