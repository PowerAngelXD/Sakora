//
// Created by BALL on 2023/1/26.
//

#ifndef SAKORA_TYPE_H
#define SAKORA_TYPE_H

#include "basic_type.h"

namespace type {
    enum StructureKind {
        Struct,
        Array,
        VarArray,
        Impl,
        Fn,
        Normal
    };

    // Type-Structure Option
    struct TSOption {
        StructureKind* s_kind = nullptr;
        UnitType* unit_type = nullptr;
    };
    TSOption optBuilder(StructureKind st);
    TSOption optBuilder(UnitType ut);
    TSOption optBuilder(BasicType bt);


    struct Type {
        std::vector<TSOption> type_content;
        TSOption head;

        Type()=default;
        Type(UnitType unit_type);
        Type(std::initializer_list<TSOption> TS_list);

        [[nodiscard]] bool isStructure() const;
        bool operator== (Type t);
        bool operator!= (Type t);

        std::string to_string();
    };
}

#endif //SAKORA_TYPE_H
