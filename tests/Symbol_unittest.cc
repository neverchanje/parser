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

//  NTerminals: 5, NNonTerminals: 3
//  Symbols:
//  { ID: 0, TAG: id }
//  { ID: 1, TAG: right_bracket }
//  { ID: 2, TAG: left_bracket }
//  { ID: 3, TAG: plus }
//  { ID: 5, TAG: F }
//  { ID: 4, TAG: multiply }
//  { ID: 6, TAG: T }
//  { ID: 7, TAG: E }
  SymbolTable::Dump();
}