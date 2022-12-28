//
// Created by BALL on 2022/12/28.
//

#ifndef SAKORA_IDENTIFIER_H
#define SAKORA_IDENTIFIER_H

#include "value.h"

namespace storage {
    // How identifiers have values
    enum OwnKind {
        ReadOnlyRef,
        MutableRef,
        Own,
        Lost // Identifier of unmapped value
    };

    // Modifier of operation mode of identifier on value
    enum Modifier {
        Dynamic,
        Static,
        Undefined // Identifier of unmapped value
    };

    class Identifier {
        // Content of identifier
        std::string content;
        OwnKind ownership;
        Modifier mod;
    public:
        Identifier(std::string c);

        // Get the identifier content
        std::string ident();
        std::string operator() (); // get the identifier content

        bool isHasValue();
        bool isRef();
        OwnKind getRefKind();
        bool isDynamic();
    };
}

#endif //SAKORA_IDENTIFIER_H
