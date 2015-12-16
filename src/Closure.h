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

  static Closure Make(const std::vector<Item> &I);

  void Dump();

  const std::vector<Item> &GetItems() const { return items_; }

 private:

  Closure();

  std::vector<Item> items_;

};

} // namespace parser

#endif //PARSER_CLOSURE_H
