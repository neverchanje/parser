//
// Created by neverchanje on 12/7/15.
//

#include "Closure.h"

using namespace parser;

Closure Closure::Make(const std::vector<Item> &I) {
  Closure clsr;
  clsr.items_ = I;

  return clsr;
}
