//
// Created by BALL on 2022/12/26.
//

#ifndef SAKORA_SCOPE_H
#define SAKORA_SCOPE_H

#include "value.h"
#include <map>

namespace storage {
    typedef std::pair<std::string, Val> Member;
    struct Scope {
        std::string ident; // identifier of Scope
        std::map<std::string, Val> members;

        Scope()=default;
        Scope(std::string i);
    };

    class Space {
        std::vector<Scope> space;
        size_t deepC = 0;
    public:
        Space();

        // ScopeManager
        void createScope(std::string i);
        void addScope(Scope s);
        void deleteScope();     // Always delete from the current value of the depth counter
        std::string getIdent(); // Always obtain the identifier of the scope currently pointed by the depth counter
        // ValueManager (Current Scope)
        template<typename T>
        void createMember(std::string name, T val);

        template<typename T>
        void createMemberWithType(std::string name, T val, type::Type t);

        void deleteMember(std::string name);
        bool findMember(std::string name);
    };
}


#endif //SAKORA_SCOPE_H
