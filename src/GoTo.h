//
// Created by neverchanje on 12/22/15.
//

#ifndef PARSER_GOTO_H
#define PARSER_GOTO_H

#include "Item.h"

namespace parser {

typedef int SymbolID;

// If there's any grammar symbol X exists so that A -> a •X b is in
// the set of items I, an empty ItemSet will return.
ItemSet GoTo(const ItemSet &I, SymbolID X);

} // namespace parser

#endif //PARSER_GOTO_H
