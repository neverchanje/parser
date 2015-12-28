//
// Created by neverchanje on 12/10/15.
//

#ifndef PARSER_LALR_H
#define PARSER_LALR_H

namespace parser {

// The order of LAItem in an LAItemSet is nothing to do with lookahead.
// Two LAItems with the same rule_id and offset but different lookaheads will
// be treated as the same LAItem in LAItemSet.
// Example:
// (E -> a •B b, c) and (E -> a •B b, d) will be merge together in one LAItemSet.

} // namespace parser

#endif //PARSER_LALR_H
