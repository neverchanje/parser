//
// Created by neverchanje on 12/20/15.
//

#include <gtest/gtest.h>
#include "Closure.h"

using namespace parser;

class ClosureBasic1: public ::testing::Test {
 protected:

  virtual void SetUp() {
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

    SymbolID
        E = SymbolTable::GetSymbol("E").GetID(),
        T = SymbolTable::GetSymbol("T").GetID(),
        F = SymbolTable::GetSymbol("F").GetID(),
        plus = SymbolTable::GetSymbol("plus").GetID(),
        right_bracket = SymbolTable::GetSymbol("right_bracket").GetID(),
        left_bracket = SymbolTable::GetSymbol("left_bracket").GetID(),
        multiply = SymbolTable::GetSymbol("multiply").GetID(),
        id = SymbolTable::GetSymbol("id").GetID();

    r1 = Rule::Make(E, {E, plus, T}).GetID();
    r2 = Rule::Make(E, {T}).GetID();
    r3 = Rule::Make(T, {T, multiply, F}).GetID();
    r4 = Rule::Make(T, {F}).GetID();
    r5 = Rule::Make(F, {left_bracket, E, right_bracket}).GetID();
    r6 = Rule::Make(F, {id}).GetID();
  }

  RuleID r1, r2, r3, r4, r5, r6;

};

TEST_F(ClosureBasic1, ClosureBasic1_Test1) {
  // E -> •E + T
  Closure clsr = Closure::Make({MakeItem(r1, 0)});

//  T -> •T multiply F $
//  F -> •id $
//  E -> •T $
//  F -> •left_bracket E right_bracket $
//  T -> •F $
//  E -> •E plus T $
  clsr.Dump();
}

TEST_F(ClosureBasic1, ClosureBasic1_Test2) {
  // E -> E + •T
  Closure clsr = Closure::Make({MakeItem(r1, 2)});

//  F -> •id $
//  T -> •T multiply F $
//  F -> •left_bracket E right_bracket $
//  T -> •F $
//  E -> E plus •T $
  clsr.Dump();
}
