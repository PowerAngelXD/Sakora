//
// Created by BALL on 2022/12/25.
//

#include "type.h"

using namespace type;

Type::Type(BasicType b): basic(b), ownership(OwnKind::Own), mod(Modifier::Static), st(Structure::Normal) {}
Type::Type(BasicType b, OwnKind ok): basic(b), ownership(ok), mod(Modifier::Static), st(Structure::Normal) {}
Type::Type(BasicType b, OwnKind ok, Modifier m): basic(b), ownership(ok), mod(m), st(Structure::Normal) {}
Type::Type(BasicType b, OwnKind ok, Modifier m, Structure s): basic(b), ownership(ok), mod(m), st(s) {}