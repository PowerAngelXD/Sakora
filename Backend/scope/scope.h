//
// Created by BALL on 2022/12/26.
//

#ifndef SAKORA_SCOPE_H
#define SAKORA_SCOPE_H

#include "identifier.h"
#include "../../error/storage_error.h"
using std::get;

namespace storage {
    // Type alias for a member of a scope (pair of a string and a Val)
    typedef std::tuple<std::string, Identifier, Val> Member;

    // Struct representing a scope
    struct Scope {
        // identifier of the scope
        std::string ident;
        // map of members (string to Val)
        std::vector<Member> members;

        // Constructors
        Scope() = default;
        // construct with identifier
        Scope(std::string i);
        // Get members and can access and modify
        Val &getMem(std::string id, int ln = -1, int col = -1);
    };

    // Class representing a space (collection of scopes)
    class Space {
        // scopes
        std::vector<Scope> space;
        // depth counter (index of current scope in the vector)
        size_t deepC = 0;
    public:
        // Constructor
        Space();

        // Scope management
        void createScope(std::string i);      // create a new scope with the given identifier
        void addScope(Scope s);               // add a scope to the vector
        void deleteScope();                   // delete the current scope (pointed by the depth counter)
        std::string getIdent();               // get the identifier of the current scope (pointed by the depth counter)

        // Value management (for the current scope)

        // create a member with the given name and value
        template<typename T>
        void createMember(std::string name, T val, int ln = -1, int col = -1);

        // create a member with the given name, value, and type
        template<typename T>
        void createMemberWithType(std::string name, T val, type::Type t, int ln = -1, int col = -1);

        // create a member with the given name, value, identifier, and type
        template<typename T>
        void createMemberCompletely(std::string name, Identifier id, T val, type::Type t, int ln = -1, int col = -1);

        // check if the current scope has a member with the given name
        bool findMember(const std::string& name);
        // delete the member with the given name
        void deleteMember(const std::string& name, int ln = -1, int col = -1);
        // get value by given name
        Val &getVal(const std::string& name, int ln = -1, int col = -1);
    };

}


#endif //SAKORA_SCOPE_H
