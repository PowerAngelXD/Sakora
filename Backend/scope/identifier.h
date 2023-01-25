//
// Created by BALL on 2022/12/28.
//

#ifndef SAKORA_IDENTIFIER_H
#define SAKORA_IDENTIFIER_H

#include "value.h"

namespace storage {
    // How identifiers have values
    enum OwnKind {
        Ref,
        Own
    };

    class Identifier {
        // Content of identifier
        std::string content;
        OwnKind ownership;
    public:
        Identifier(std::string c);
        Identifier(std::string c, OwnKind o);

        // Get the identifier content
        std::string ident();
        std::string operator() (); // get the identifier content

        bool isRef();
        OwnKind getRefKind();
    };
}

#endif //SAKORA_IDENTIFIER_H
