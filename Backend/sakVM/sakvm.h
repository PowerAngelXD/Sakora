//
// Created by BALL on 2022/12/31.
//

#ifndef SAKORA_SAKVM_H
#define SAKORA_SAKVM_H

#include "../env/environment.h"
#include "../env/tool.h"
#include "../env/codequeue.h"
#include <algorithm>

struct saKVM {
    /**
     * Naming conventions:
     * vm_xxx: Operation on VM
     * ins_xxx: Instructions of VM
     */
    // VM code queues
    std::vector<sakVM_core::CodeQueue> threads;
    // Environment of the VM
    sakVM_core::Environment env;

    saKVM(std::vector<std::string> cp, int ln, int col);

    // Initialization operation for VM
    void init(std::vector<std::string> cp, int ln, int col);
    // Run the code queue at the specified level
    void run(size_t layer);
    // VM instruction set
    void ins_push_int(visitor::Code code);
    void ins_push_deci(visitor::Code code);
    void ins_push_bool(visitor::Code code);
    void ins_push_str(visitor::Code code);
    void ins_push_iden(visitor::Code code);
    void ins_push_flag(visitor::Code code);
    void ins_set_list();
    void ins_set_mutable_list();
    void ins_add();
    void ins_sub();
    void ins_mul();
    void ins_div();
    void ins_gmem();
    void ins_mod();
    void ins_gt();
    void ins_lt();
    void ins_ge();
    void ins_le();
    void ins_eq();
    void ins_neq();
    void ins_logic_or();
    void ins_logic_and();
    void ins_no();
    void ins_stfop(visitor::Code code);
};


#endif //SAKORA_SAKVM_H
