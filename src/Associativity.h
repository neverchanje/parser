//
// Created by neverchanje on 12/10/15.
//

#ifndef PARSER_ASSOCIATIVITY_H
#define PARSER_ASSOCIATIVITY_H

#include <string>

enum Assoc {
  NONE,
  RIGHT,
  LEFT
};

std::string AssocToString(Assoc assoc);

#endif //PARSER_ASSOCIATIVITY_H
