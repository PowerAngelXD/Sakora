//
// Created by BALL on 2022/12/25.
//

#include "type.h"

using namespace type;

Type::Type(BasicType b): basic(b), ownership(StorageKind::Val), st(Structure::Normal) {}
Type::Type(BasicType b, StorageKind ok): basic(b), ownership(ok), st(Structure::Normal) {}
Type::Type(BasicType b, StorageKind ok, Structure s): basic(b), ownership(ok), st(s) {}