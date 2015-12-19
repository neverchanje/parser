//
// Created by neverchanje on 12/18/15.
//

#include <gtest/gtest.h>
#include "Rule.h"

using namespace parser;

TEST(Rule_Basics, Rule_Basics_Test) {

  RuleTable::Clear();

  Symbol::Make("E", Symbol::Type::NONTERMINAL);
  Symbol::Make("T", Symbol::Type::NONTERMINAL);
  Symbol::Make("F", Symbol::Type::NONTERMINAL);
  Symbol::Make("plus", Symbol::Type::TERMINAL);
  Symbol::Make("multiply", Symbol::Type::TERMINAL);
  Symbol::Make("left_bracket", Symbol::Type::TERMINAL);
  Symbol::Make("right_bracket", Symbol::Type::TERMINAL);
  Symbol::Make("id", Symbol::Type::TERMINAL);
  Symbol::EOR();

  SymbolTable::Pack();

//  NTerminals: 6, NNonTerminals: 3
//  Symbols:
//  { ID: 0, TAG: EOR }
//  { ID: 1, TAG: id }
//  { ID: 2, TAG: right_bracket }
//  { ID: 3, TAG: left_bracket }
//  { ID: 6, TAG: T }
//  { ID: 4, TAG: multiply }
//  { ID: 7, TAG: F }
//  { ID: 5, TAG: plus }
//  { ID: 8, TAG: E }
  SymbolTable::Dump();

  SymbolID
      E = SymbolTable::GetSymbol("E").GetID(),
      T = SymbolTable::GetSymbol("T").GetID(),
      F = SymbolTable::GetSymbol("F").GetID(),
      plus = SymbolTable::GetSymbol("plus").GetID(),
      right_bracket = SymbolTable::GetSymbol("right_bracket").GetID(),
      left_bracket = SymbolTable::GetSymbol("left_bracket").GetID(),
      multiply = SymbolTable::GetSymbol("multiply").GetID(),
      id = SymbolTable::GetSymbol("id").GetID();

  // E -> E + T
  // E -> T
  // T -> T * F
  // T -> F
  // F -> (E)
  // F -> id
  Rule::Make(E, {E, plus, T});
  Rule::Make(E, {T});
  Rule::Make(T, {T, multiply, F});
  Rule::Make(T, {F});
  Rule::Make(F, {left_bracket, E, right_bracket});
  Rule::Make(F, {id});

//  E -> E plus T $
//  E -> T $
//  T -> T multiply F $
//  T -> F $
//  F -> left_bracket E right_bracket $
//  F -> id $
  RuleTable::Dump();
}