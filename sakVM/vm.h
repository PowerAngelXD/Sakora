//
// Created by BALL on 2022/12/31.
//

#ifndef SAKORA_VM_H
#define SAKORA_VM_H

#include "core/environment.h"
#include "core/tool.h"
#include "core/codequeue.h"

struct sakVM {
    /**
     * Naming conventions:
     * vm_xxx: Operation on VM
     * ins_xxx: Instructions of VM
     */
    // VM code queues
    std::vector<sakVM_core::CodeQueue> threads;
    // Environment of the VM
    sakVM_core::Environment env;

    sakVM(std::vector<std::string> cp, int ln, int col);

    // Initialization operation for VM
    void vm_init(std::vector<std::string> cp, int ln, int col);
    // Run the code queue at the specified level
    void vm_run(size_t layer);
    // VM instruction set
    void ins_push_i16(visitor::Code code);
    void ins_push_i32(visitor::Code code);
    void ins_push_i64(visitor::Code code);
    void ins_push_float(visitor::Code code);
    void ins_push_double(visitor::Code code);
    void ins_push_bool(visitor::Code code);
    void ins_push_str(visitor::Code code);
    void ins_push_iden(visitor::Code code);
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

};


#endif //SAKORA_VM_H
