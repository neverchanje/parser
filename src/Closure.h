//
// Created by neverchanje on 12/7/15.
//

#ifndef PARSER_CLOSURE_H
#define PARSER_CLOSURE_H

#include <vector>

#include "Rule.h"

namespace parser {

class Closure {

 public:

  static Closure Make(const std::vector<ItemID>& I);

  void Dump();

 private:

  // Creation of Closure is only allowed to use the routine Closure::Make()
  Closure();

  std::vector<ItemID> items_;

};

} // namespace parser

#endif //PARSER_CLOSURE_H
