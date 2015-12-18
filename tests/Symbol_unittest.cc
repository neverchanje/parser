//
// Created by neverchanje on 12/17/15.
//

#include <gtest/gtest.h>
#include "Symbol.h"

using namespace parser;

TEST(Symbol_Basics, Symbol_Basics_Test) {
  Symbol::Make("Blank", Symbol::Type::TERMINAL);
  Symbol::Make("Comma", Symbol::Type::TERMINAL);
  Symbol::Make("Statement", Symbol::Type::NONTERMINAL);
  Symbol::Make("Expression", Symbol::Type::NONTERMINAL);
  Symbol::Make("If", Symbol::Type::TERMINAL);
  Symbol::Make("Else", Symbol::Type::TERMINAL);
  Symbol::Make("WhileStatement", Symbol::Type::NONTERMINAL);

  SymbolTable::Pack();

//  NTerminals: 4, NNonTerminals: 3
//  Symbols:
//  { ID: 4, TAG: WhileStatement }
//  { ID: 0, TAG: Else }
//  { ID: 5, TAG: Statement }
//  { ID: 1, TAG: If }
//  { ID: 6, TAG: Expression }
//  { ID: 2, TAG: Comma }
//  { ID: 3, TAG: Blank }
  SymbolTable::Dump();
}