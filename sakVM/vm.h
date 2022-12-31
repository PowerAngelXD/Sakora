//
// Created by BALL on 2022/12/31.
//

#ifndef SAKORA_VM_H
#define SAKORA_VM_H

#include "core/environment.h"
#include "core/tool.h"
#include "core/codequeue.h"

namespace sakVM {
    /**
     * Naming conventions:
     * vm_xxx: Operation on VM
     */
    static std::string vm_info = "Sakora VM (Version: 1.0)";
    // VM code queues
    static std::vector<sakVM_core::CodeQueue> threads;
    // Environment of the VM
    static sakVM_core::Environment env;

    // VM instruction set
    namespace sakVM_code_set {

    }

    // Initialization operation for VM
    void vm_init(std::vector<std::string> cp, int ln, int col);
    // Run the code queue at the specified level
    void vm_run(size_t layer);
}

#endif //SAKORA_VM_H
