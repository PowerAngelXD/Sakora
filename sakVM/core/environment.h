//
// Created by BALL on 2022/12/28.
//

#ifndef SAKORA_ENVIRONMENT_H
#define SAKORA_ENVIRONMENT_H

#include "../../Backend/object/object.h"
#include <stack>

namespace sakVM_core {
    class Environment {
        // the space stores symbol tables of different levels and corresponding values
        storage::Space space;
        /*
         * The value stack of the runtime VM must have only one value or be empty at the end of the run;
         * Some values in the value stack cannot be accessed, but they play a very important role in the VM level
        */
        std::stack<storage::Val> runtime;

        int line, column;
    public:
        Environment(int ln, int col);

        void push(storage::Val);
        storage::Val peek();
        storage::Val pop();

        bool findIdentifier(std::string ident);
        storage::Val& getVal(std::string ident);
        void deleteVal(std::string ident);

        template<typename ValType>
        void createValue(std::string ident, ValType val);

        template<typename ValType>
        void createValueWithType(std::string ident, ValType val, type::Type type);

    };
}

#endif //SAKORA_ENVIRONMENT_H
