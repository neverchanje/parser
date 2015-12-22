//
// Created by neverchanje on 12/7/15.
//

#ifndef PARSER_CLOSURE_H
#define PARSER_CLOSURE_H

#include <vector>

#include "Item.h"

namespace parser {

ItemSet Closure(std::vector<Item> &&I);

void DumpClosure(const ItemSet &clsr);

} // namespace parser

#endif //PARSER_CLOSURE_H
