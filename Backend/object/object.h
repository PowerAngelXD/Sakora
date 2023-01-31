//
// Created by BALL on 2022/12/27.
//

#ifndef SAKORA_OBJECT_H
#define SAKORA_OBJECT_H

#include "../scope/scope.h"
#include <map>

namespace type {
    // ObjectKind enum represents the different kinds of objects that can be represented by the Object struct
    enum ObjectKind {
        FuncObj,        // Function object
        StructObj,      // Struct object
        ImplementObj    // Implementation object
    };

    // Arg type represents an argument for a function, which is a pair consisting of a string (the argument name)
    // and a type::UnitType (the type of the argument)
    typedef std::pair<std::string, type::UnitType> Arg;

    // FunctionObject class represents a function with a set of arguments and a return type
    class FunctionObject {
        // Identifier for this function
        std::string ident;
        // Vector of visitor::Code objects representing the code for this function
        std::vector<visitor::Code> codeQueue;
        // Map of arguments for this function, with the argument name as the key
        std::map<std::string, type::UnitType> args;
        // Return type for this function
        type::UnitType retType;

    public:
        FunctionObject()=default;
        // Constructor to create a FunctionObject with the given identifier, vector of code, and return type
        FunctionObject(std::string id, std::vector<visitor::Code> cq, type::UnitType ret);

        // Returns the return type for this function
        type::UnitType getReturnType();
        // Returns the Arg object with the given name, or an empty Arg object if no such argument exists
        Arg getArg(const std::string& argName);
        // Returns the identifier for this function
        std::string getIdentifier();

        // Overloaded array access operator to retrieve the Arg object with the given name
        Arg operator[] (const std::string& argName);
    };

    // Forward declaration of ImplementObject class
    class ImplementObject;

    // Definition of a member, which is a pair consisting of a string (the name of the member)
    // and a storage::Val (the value of the member)
    typedef std::pair<std::string, storage::Val> Member;

    // Definition of an associated implementation, which is a pair consisting of a string (the name of the implementation)
    // and an ImplementObject pointer (a pointer to the ImplementObject that represents the implementation)
    typedef std::pair<std::string, ImplementObject*> AssocImpl;

    // StructObject class represents an object that has a set of members and associated implementations
    class StructObject {
        // Identifier for this object
        std::string ident;
        // Map of members for this object, with the member name as the key
        std::map<std::string, storage::Val> members;
        // Map of associated implementations for this object, with the implementation name as the key
        std::map<std::string, ImplementObject*> impls;

    public:
        // Constructor to create a StructObject with the given identifier and map of members
        StructObject(std::string id, std::map<std::string, storage::Val> mems);

        // Returns the value of the member with the given name, or a default-constructed storage::Val object if no such member exists
        storage::Val getMemberVal(const std::string& memIdent);
        // Returns the ImplementObject pointer for the associated implementation with the given name,
        // or a nullptr if no such implementation exists
        ImplementObject* getAssocImpl(const std::string& impl);
        // Adds the given ImplementObject pointer to the map of associated implementations for this object
        void AddImplement(ImplementObject* impl);

        // Overloaded array access operator to retrieve the value of the member with the given name
        storage::Val operator[] (std::string memIdent);
        // Overloaded function call operator to retrieve the ImplementObject pointer for the associated implementation with the given name
        ImplementObject* operator() (std::string impl);
    };

    // Definition of a method, which is a pair consisting of a string (the name of the method)
    // and a FunctionObject (the function object that represents the method)
    typedef std::pair<std::string, FunctionObject> Method;

    // ImplementObject class represents an implementation of a struct object, which has a set of methods
    class ImplementObject {
        // Identifier for this implementation
        std::string ident;
        // Pointer to the StructObject that this implementation is associated with
        StructObject *father = nullptr;
        // Map of methods for this implementation, with the method name as the key
        std::map<std::string, FunctionObject> methods;

    public:
        // Constructor to create an ImplementObject with the given identifier
        ImplementObject(std::string id);
        // Constructor to create an ImplementObject with the given identifier and pointer to the associated StructObject
        ImplementObject(std::string id, StructObject *f);

        // Adds the given FunctionObject to the map of methods for this implementation
        void addMethod(FunctionObject fn);
        // Returns the FunctionObject for the method with the given name, or a default-constructed FunctionObject if no such method exists
        FunctionObject getMethod(const std::string& methodName);
        // Returns a pointer to the StructObject that this implementation is associated with
        StructObject *getFather();

        // Overloaded array access operator to retrieve the FunctionObject for the method with the given name
        FunctionObject operator[](const std::string& methodName);
        // Overloaded addition assignment operator to add the given FunctionObject to the map of methods for this implementation
        void operator+=(FunctionObject fn);
    };

    // Object struct represents an object in the program, which could be a function object, a struct object, or an implement object
    struct Object {
        // Pointer to a FunctionObject, which is non-null if this object is a function object
        FunctionObject* fnObj = nullptr;
        // Pointer to a StructObject, which is non-null if this object is a struct object
        StructObject* structObj = nullptr;
        // Pointer to an ImplementObject, which is non-null if this object is an implement object
        ImplementObject* implObj = nullptr;

        // Enum value indicating the type of this object (function object, struct object, or implement object)
        ObjectKind kind;

        /**
         * @brief Construct an object with the given identifier, code vector, and return type.
         * @param ident The identifier of the object.
         * @param cs The code vector of the object.
         * @param ret The return type of the object.
        */
        Object(std::string ident, std::vector<visitor::Code> cs, type::UnitType ret);
        /**
         * @brief Construct an object with the given identifier and member map.
         * @param ident The identifier of the object.
         * @param mems The map of members (string to Val).
        */
        Object(std::string ident, std::map<std::string, storage::Val> mems);
        /**
         * @brief Construct an object with the given identifier and father.
         * @param ident The identifier of the object.
         * @param f The father of the object.
        */
        Object(std::string ident, StructObject* f);
        /**
         * @brief Construct an object with the given identifier.
         * @param ident The identifier of the object.
        */
        explicit Object(std::string ident);

    };
}

#endif //SAKORA_OBJECT_H
