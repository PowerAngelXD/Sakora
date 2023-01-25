//
// Created by BALL on 2022/12/25.
//

#include "type.h"

using namespace type;

Type::Type(BasicType b): basic(b), st(Structure::Normal) {}
Type::Type(BasicType b, Structure s): basic(b), st(s) {}
Type::Type(BasicType b, Structure s, StorageKind stok): basic(b), st(s), stk(stok) {}