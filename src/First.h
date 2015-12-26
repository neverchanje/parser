//
// Created by neverchanje on 12/24/15.
//

#ifndef PARSER_FIRST_H
#define PARSER_FIRST_H

#include <unordered_set>
#include <vector>

namespace parser {

typedef int SymbolID;

typedef std::unordered_set<SymbolID> SymbolSet;

// FIRST(X) can not handle left-recursive grammar.
// Cost O(1) time.
const SymbolSet &First(SymbolID X);

void InitFirst();

void DumpFirst(const SymbolSet &symset);

} // namespace parser

#endif //PARSER_FIRST_H
