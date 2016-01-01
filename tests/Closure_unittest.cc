//
// Created by neverchanje on 12/20/15.
//

#include <gtest/gtest.h>
#include "ItemSetTestHelper.h"
#include "Closure.h"

using namespace parser;

#define EXPECT_INSERT_ITEM(r, off) assert(expect.insert(Item::MakeUnique(r, off)).second)

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
  ItemSet actual = Closure({Item(r1, 0)});

  DumpClosure(actual);

  ItemSet expect;
  EXPECT_INSERT_ITEM(r1, 0); //  E -> •E plus T $
  EXPECT_INSERT_ITEM(r2, 0); //  E -> •T $
  EXPECT_INSERT_ITEM(r3, 0); //  T -> •T multiply F $
  EXPECT_INSERT_ITEM(r4, 0); //  T -> •F $
  EXPECT_INSERT_ITEM(r5, 0); //  F -> •left_bracket E right_bracket $
  EXPECT_INSERT_ITEM(r6, 0); //  F -> •id $

  EXPECT_PRED_FORMAT2 (AssertItemSetCmp, expect, actual);
}

TEST_F(ClosureBasic1, ClosureBasic1_Test2) {
  // E -> E + •T
  ItemSet actual = Closure({Item(r1, 2)});

  DumpClosure(actual);

  ItemSet expect;
  EXPECT_INSERT_ITEM(r1, 2); //  E -> E plus •T $
  EXPECT_INSERT_ITEM(r3, 0); //  T -> •T multiply F $
  EXPECT_INSERT_ITEM(r4, 0); //  T -> •F $
  EXPECT_INSERT_ITEM(r6, 0); //  F -> •id $
  EXPECT_INSERT_ITEM(r5, 0); //  F -> •left_bracket E right_bracket $

  EXPECT_PRED_FORMAT2 (AssertItemSetCmp, expect, actual);
}

class ClosureBasic2: public ::testing::Test {
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

TEST_F(ClosureBasic2, ClosureBasic2_Test1) {
  // S_ -> •S
  ItemSet actual = Closure({Item(r1, 0)});

  DumpClosure(actual);

  ItemSet expect;
  EXPECT_INSERT_ITEM(r6, 0); //  R -> •L $
  EXPECT_INSERT_ITEM(r3, 0); //  S -> •R $
  EXPECT_INSERT_ITEM(r5, 0); //  L -> •id $
  EXPECT_INSERT_ITEM(r4, 0); //  L -> •* R $
  EXPECT_INSERT_ITEM(r1, 0); //  S_ -> •S $
  EXPECT_INSERT_ITEM(r2, 0); //  S -> •L = R $

  EXPECT_PRED_FORMAT2 (AssertItemSetCmp, expect, actual);
}