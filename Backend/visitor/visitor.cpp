//
// Created by BALL on 2022/12/25.
//

#include "visitor.h"

using namespace visitor;

Code::Code(CodeKind k, int l, int c): kind(k),val(0), ln(l), col(c) {}
Code::Code(CodeKind k, double v, int l, int c): kind(k), val(v), ln(l), col(c) {}