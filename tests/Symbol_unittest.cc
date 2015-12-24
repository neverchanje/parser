//
// Created by neverchanje on 12/17/15.
//

#include <gtest/gtest.h>
#include "Symbol.h"

using namespace parser;

TEST(Symbol_Basics, Symbol_Basics_Test) {

  SymbolTable::Clear();

  Symbol::Make("Blank", Symbol::Type::TERMINAL);
  Symbol::Make("Comma", Symbol::Type::TERMINAL);
  Symbol::Make("Statement", Symbol::Type::NONTERMINAL);
  Symbol::Make("Expression", Symbol::Type::NONTERMINAL);
  Symbol::Make("If", Symbol::Type::TERMINAL);
  Symbol::Make("Else", Symbol::Type::TERMINAL);
  Symbol::Make("WhileStatement", Symbol::Type::NONTERMINAL);

  SymbolTable::Pack();

//  NTerminals: 6, NNonTerminals: 3
//  Symbols:
//  { ID: 6, TAG: WhileStatement }
//  { ID: 0, TAG: Else }
//  { ID: 7, TAG: Statement }
//  { ID: 1, TAG: If }
//  { ID: 2, TAG: $ }
//  { ID: 8, TAG: Expression }
//  { ID: 3, TAG: Comma }
//  { ID: 4, TAG: ε }
//  { ID: 5, TAG: Blank }
  SymbolTable::Dump();
}

TEST(Symbol_Basics2, Symbol_Basics_Test) {

  SymbolTable::Clear();

  Symbol::Make("E", Symbol::Type::NONTERMINAL);
  Symbol::Make("T", Symbol::Type::NONTERMINAL);
  Symbol::Make("F", Symbol::Type::NONTERMINAL);
  Symbol::Make("plus", Symbol::Type::TERMINAL);
  Symbol::Make("multiply", Symbol::Type::TERMINAL);
  Symbol::Make("left_bracket", Symbol::Type::TERMINAL);
  Symbol::Make("right_bracket", Symbol::Type::TERMINAL);
  Symbol::Make("id", Symbol::Type::TERMINAL);

  SymbolTable::Pack();

//  NTerminals: 7, NNonTerminals: 3
//  Symbols:
//  { ID: 0, TAG: $ }
//  { ID: 1, TAG: ε }
//  { ID: 2, TAG: id }
//  { ID: 3, TAG: right_bracket }
//  { ID: 4, TAG: left_bracket }
//  { ID: 5, TAG: plus }
//  { ID: 7, TAG: F }
//  { ID: 6, TAG: multiply }
//  { ID: 8, TAG: T }
//  { ID: 9, TAG: E }
  SymbolTable::Dump();
}