//
// Created by neverchanje on 12/27/15.
//
#include <gtest/gtest.h>
#include "LAClosure.h"
#include "Rule.h"

using namespace parser;

class LAClosureBasic1: public ::testing::Test {
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

    E = SymbolTable::GetSymbol("E").GetID();
    T = SymbolTable::GetSymbol("T").GetID();
    F = SymbolTable::GetSymbol("F").GetID();
    plus = SymbolTable::GetSymbol("plus").GetID();
    right_bracket = SymbolTable::GetSymbol("right_bracket").GetID();
    left_bracket = SymbolTable::GetSymbol("left_bracket").GetID();
    multiply = SymbolTable::GetSymbol("multiply").GetID();
    id = SymbolTable::GetSymbol("id").GetID();
    eor = SymbolTable::GetSymbol("$").GetID();

    r1 = Rule::Make(E, {E, plus, T}).GetID();
    r2 = Rule::Make(E, {T}).GetID();
    r3 = Rule::Make(T, {T, multiply, F}).GetID();
    r4 = Rule::Make(T, {F}).GetID();
    r5 = Rule::Make(F, {left_bracket, E, right_bracket}).GetID();
    r6 = Rule::Make(F, {id}).GetID();
  }

  RuleID r1, r2, r3, r4, r5, r6;
  SymbolID E, T, F, plus, multiply, left_bracket, right_bracket, id, eor;
};

TEST_F(LAClosureBasic1, LAClosureBasic1_Test1) {
  // E -> •E + T, $
  LAItemSet actual = LAClosure({LAItem(r1, 0, Symbol::EOR().GetID())});

  LAItemSet expect(
      {
          LAItem(r1, 0, eor), // E -> •E plus T $ , $
          LAItem(r1, 0, plus), // E -> •E plus T $ , plus
          LAItem(r2, 0, plus), //  E -> •T $ , plus
          LAItem(r3, 0,), //  T -> •T multiply F $ , +
          LAItem(r6, 0), //  F -> •id $ ,
          LAItem(r5, 0), //  F -> •left_bracket E right_bracket $
          LAItem(r4, 0,), // T -> •F $
      });
//  DumpClosure(actual);
  EXPECT_EQ(expect, actual);
}

TEST_F(LAClosureBasic1, LAClosureBasic1_Test2) {
  // E -> E + •T
  LAItemSet actual = LAClosure({Item(r1, 2)});

//  F -> •id $
//  T -> •T multiply F $
//  F -> •left_bracket E right_bracket $
//  T -> •F $
//  E -> E plus •T $
//  DumpClosure(actual);
  LAItemSet expect(
      {
          LAItem(r6, 0),
          LAItem(r3, 0),
          LAItem(r5, 0),
          LAItem(r4, 0),
          LAItem(r1, 2)
      });
  EXPECT_EQ(expect, actual);
}

class LAClosureBasic2: public ::testing::Test {
 protected:

  virtual void SetUp() {
    RuleTable::Clear();

    Symbol::Make("S", Symbol::Type::NONTERMINAL);
    Symbol::Make("S_", Symbol::Type::NONTERMINAL);
    Symbol::Make("L", Symbol::Type::NONTERMINAL);
    Symbol::Make("R", Symbol::Type::NONTERMINAL);
    Symbol::Make("=", Symbol::Type::TERMINAL);
    Symbol::Make("*", Symbol::Type::TERMINAL);
    Symbol::Make("id", Symbol::Type::TERMINAL);
    Symbol::EOR();

    SymbolTable::Pack();

    SymbolID
        S_ = SymbolTable::GetSymbol("S_").GetID(),
        S = SymbolTable::GetSymbol("S").GetID(),
        L = SymbolTable::GetSymbol("L").GetID(),
        R = SymbolTable::GetSymbol("R").GetID(),
        equal = SymbolTable::GetSymbol("=").GetID(),
        multiply = SymbolTable::GetSymbol("*").GetID(),
        id = SymbolTable::GetSymbol("id").GetID();

//  S_ -> S $
//  S -> L = R $
//  S -> R $
//  L -> * R $
//  L -> id $
//  R -> L $
    r1 = Rule::Make(S_, {S}).GetID();
    r2 = Rule::Make(S, {L, equal, R}).GetID();
    r3 = Rule::Make(S, {R}).GetID();
    r4 = Rule::Make(L, {multiply, R}).GetID();
    r5 = Rule::Make(L, {id}).GetID();
    r6 = Rule::Make(R, {L}).GetID();
  }

  RuleID r1, r2, r3, r4, r5, r6;

};

TEST_F(LAClosureBasic2, LAClosureBasic2_Test1) {
  // S_ -> •S
  LAItemSet clsr = LAClosure({Item(r1, 0)});

//  S -> •L = R $
//  R -> •L $
//  S_ -> •S $
//  L -> •* R $
//  L -> •id $
//  S -> •R $
//  DumpClosure(clsr);
}
