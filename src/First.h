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

SymbolSet First(SymbolID X);

SymbolSet First(std::vector<SymbolID> &&symbols);

} // namespace parser

#endif //PARSER_FIRST_H
