//
// Created by BALL on 2022/12/28.
//

#ifndef SAKORA_ENVIRONMENT_H
#define SAKORA_ENVIRONMENT_H

#include "../../Backend/object/object.h"
#include <stack>

namespace sakVM_core {
    // This class represents an environment in which a program can be executed.
    // An environment consists of a space in which variables and their values are stored,
    // a runtime stack used to store temporary values during program execution,
    // and information about the current line and column in the source code.
    class Environment {
        // The space in which variables and their values are stored.
        storage::Space space;
        // A stack used to store temporary values during program execution.
        std::stack<storage::Val> runtime;
        // Constant pool
        std::vector<std::string> constantPool;
        // The current line in the source code.
        int line;
        // The current column in the source code.
        int column;
    public:
        Environment()=default;
        // Constructs a new environment with the given line and column information.
        Environment(std::vector<std::string> cp, int ln, int col);


        // Get the string of a specific index
        std::string getConstant(size_t index);

        // Pushes a value onto the runtime stack.
        void push(storage::Val val);
        // Returns the top value on the runtime stack without removing it.
        storage::Val peek();
        // Removes and returns the top value on the runtime stack.
        storage::Val pop();

        // Returns true if the environment contains a variable with the given identifier.
        bool findIdentifier(const std::string& ident);
        // Returns a reference to the value of the variable with the given identifier, or throws an error if it does not exist.
        storage::Val &getVal(const std::string& ident, int ln = -1, int col = -1);
        // Deletes the variable with the given identifier, or throws an error if it does not exist.
        void deleteVal(const std::string& ident, int ln, int col);

        // Creates a new variable with the given identifier and value, and the default type.
        template<typename ValType>
        void createValue(std::string ident, ValType val, int ln, int col);

        // Creates a new variable with the given identifier, value, and type.
        template<typename ValType>
        void createValueWithType(std::string ident, ValType val, type::Type type, int ln, int col);
    };

}

#endif //SAKORA_ENVIRONMENT_H
