//
// Created by neverchanje on 12/27/15.
//
#include <gtest/gtest.h>
#include "LAClosure.h"
#include "Rule.h"
#include "First.h"

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
  LAItemSet actual = LAClosure({LAItem(r1, 0, eor)});

  LAItemSet expect(
      {
          LAItem(r1, 0, eor), // E -> •E plus T $ , $
          LAItem(r1, 0, plus), // E -> •E plus T $ , plus
          LAItem(r2, 0, plus), // E -> •T $ , plus
          LAItem(r3, 0, plus), // T -> •T multiply F $ , plus
          LAItem(r4, 0, plus), // T -> •F $ , plus
          LAItem(r3, 0, multiply), // T -> •T multiply F $ , multiply
          LAItem(r4, 0, multiply), // T -> •F $ , multiply
          LAItem(r6, 0, plus), //  F -> •id $ , plus
          LAItem(r6, 0, plus), //  F -> •id $ , multiply
          LAItem(r5, 0, plus), //  F -> •left_bracket E right_bracket $ , plus
          LAItem(r5, 0, multiply) //  F -> •left_bracket E right_bracket $ , multiply
      });

  EXPECT_EQ(expect, actual);
}

TEST_F(LAClosureBasic1, LAClosureBasic1_Test2) {
  // E -> E + •T , $
  LAItemSet actual = LAClosure({LAItem(r1, 2, eor)});

//  DumpClosure(actual);
  LAItemSet expect(
      {
          LAItem(r1, 2, eor), //  E -> E plus •T $ , $
          LAItem(r3, 0, eor), //  T -> •T multiply F $
          LAItem(r4, 0, eor), //  T -> •F $
          LAItem(r3, 0, multiply), //  T -> •T multiply F $
          LAItem(r4, 0, multiply), //  T -> •F $
          LAItem(r5, 0, eor), //  F -> •left_bracket E right_bracket $
          LAItem(r6, 0, eor) //  F -> •id $
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

    S_ = SymbolTable::GetSymbol("S_").GetID();
    S = SymbolTable::GetSymbol("S").GetID();
    L = SymbolTable::GetSymbol("L").GetID();
    R = SymbolTable::GetSymbol("R").GetID();
    equal = SymbolTable::GetSymbol("=").GetID();
    multiply = SymbolTable::GetSymbol("*").GetID();
    id = SymbolTable::GetSymbol("id").GetID();
    eor = SymbolTable::GetSymbol("$").GetID();

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
  SymbolID S_, S, L, R, equal, multiply, id, eor;
};

TEST_F(LAClosureBasic2, LAClosureBasic2_Test1) {
  // S_ -> •S, $
  LAItemSet actual = LAClosure({LAItem(r1, 0, eor)});

  LAItemSet expect(
      {
          LAItem(r1, 0, eor), //  S_ -> •S $ , $
          LAItem(r2, 0, eor), //  S -> •L = R $ , $
          LAItem(r3, 0, eor), //  S -> •R $ , $
          LAItem(r4, 0, equal), //  L -> •* R $ , =
          LAItem(r5, 0, equal), //  L -> •id $ , =
          LAItem(r6, 0, eor) //  R -> •L $
      });

  EXPECT_EQ(expect, actual);
}
