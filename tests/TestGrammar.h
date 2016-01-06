//
// Created by neverchanje on 1/6/16.
//

#ifndef PARSER_TESTGRAMMAR_H
#define PARSER_TESTGRAMMAR_H

#include <gtest/gtest.h>
#include "Rule.h"

namespace parser {

class TestGrammar1: public ::testing::Test {
 protected:

  virtual void SetUp() {

    Symbol::Make("E", Symbol::Type::NONTERMINAL);
    Symbol::Make("T", Symbol::Type::NONTERMINAL);
    Symbol::Make("F", Symbol::Type::NONTERMINAL);
    Symbol::Make("plus", Symbol::Type::TERMINAL);
    Symbol::Make("multiply", Symbol::Type::TERMINAL);
    Symbol::Make("left_bracket", Symbol::Type::TERMINAL);
    Symbol::Make("right_bracket", Symbol::Type::TERMINAL);
    Symbol::Make("id", Symbol::Type::TERMINAL);

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

  virtual void TearDown() {
    RuleTable::Clear();
  }

  RuleID r1, r2, r3, r4, r5, r6;
  SymbolID E, T, F, plus, multiply, left_bracket, right_bracket, id, eor;
};

class TestGrammar2: public ::testing::Test {
 protected:

  virtual void SetUp() {
    Symbol::Make("S", Symbol::Type::NONTERMINAL);
    Symbol::Make("S_", Symbol::Type::NONTERMINAL);
    Symbol::Make("L", Symbol::Type::NONTERMINAL);
    Symbol::Make("R", Symbol::Type::NONTERMINAL);
    Symbol::Make("=", Symbol::Type::TERMINAL);
    Symbol::Make("*", Symbol::Type::TERMINAL);
    Symbol::Make("id", Symbol::Type::TERMINAL);

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

  virtual void TearDown() {
    RuleTable::Clear();
  }

  RuleID r1, r2, r3, r4, r5, r6;
  SymbolID S_, S, L, R, equal, multiply, id, eor;
};

class TestGrammar3: public ::testing::Test {
 protected:

  virtual void SetUp() {
    Symbol::Make("S_", Symbol::Type::NONTERMINAL);
    Symbol::Make("S", Symbol::Type::NONTERMINAL);
    Symbol::Make("C", Symbol::Type::NONTERMINAL);
    Symbol::Make("c", Symbol::Type::TERMINAL);
    Symbol::Make("d", Symbol::Type::TERMINAL);

    SymbolTable::Pack();

    S_ = SymbolTable::GetSymbol("S_").GetID();
    S = SymbolTable::GetSymbol("S").GetID();
    C = SymbolTable::GetSymbol("C").GetID();
    c = SymbolTable::GetSymbol("c").GetID();
    d = SymbolTable::GetSymbol("d").GetID();
    eor = SymbolTable::GetSymbol("$").GetID();

//  S_ → S
//  S → CC
//  C → cC
//  C → d
    r1 = Rule::Make(S_, {S}).GetID();
    r2 = Rule::Make(S, {C, C}).GetID();
    r3 = Rule::Make(C, {c, C}).GetID();
    r4 = Rule::Make(C, {d}).GetID();
  }

  virtual void TearDown() {
    RuleTable::Clear();
  }

  RuleID r1, r2, r3, r4;
  SymbolID S_, S, C, c, d, eor;
};

class TestGrammar4: public ::testing::Test {
 protected:

  virtual void SetUp() {

    Symbol::Make("E_", Symbol::Type::NONTERMINAL);
    Symbol::Make("E", Symbol::Type::NONTERMINAL);
    Symbol::Make("T", Symbol::Type::NONTERMINAL);
    Symbol::Make("F", Symbol::Type::NONTERMINAL);
    Symbol::Make("+", Symbol::Type::TERMINAL);
    Symbol::Make("*", Symbol::Type::TERMINAL);
    Symbol::Make("(", Symbol::Type::TERMINAL);
    Symbol::Make(")", Symbol::Type::TERMINAL);
    Symbol::Make("id", Symbol::Type::TERMINAL);
    Symbol::EOR();

    SymbolTable::Pack();

    E_ = SymbolTable::GetSymbol("E_").GetID();
    E = SymbolTable::GetSymbol("E").GetID();
    T = SymbolTable::GetSymbol("T").GetID();
    F = SymbolTable::GetSymbol("F").GetID();
    plus = SymbolTable::GetSymbol("+").GetID();
    right_bracket = SymbolTable::GetSymbol(")").GetID();
    left_bracket = SymbolTable::GetSymbol("(").GetID();
    multiply = SymbolTable::GetSymbol("*").GetID();
    id = SymbolTable::GetSymbol("id").GetID();

    // E_ -> E
    // E -> E + T
    // E -> T
    // T -> T * F
    // T -> F
    // F -> (E)
    // F -> id
    r0 = Rule::Make(E_, {E}).GetID();
    r1 = Rule::Make(E, {E, plus, T}).GetID();
    r2 = Rule::Make(E, {T}).GetID();
    r3 = Rule::Make(T, {T, multiply, F}).GetID();
    r4 = Rule::Make(T, {F}).GetID();
    r5 = Rule::Make(F, {left_bracket, E, right_bracket}).GetID();
    r6 = Rule::Make(F, {id}).GetID();
  }

  virtual void TearDown() {
    RuleTable::Clear();
  }

  RuleID r0, r1, r2, r3, r4, r5, r6;
  SymbolID E_, E, T, F, plus, multiply, left_bracket, right_bracket, id;
};

} // namespace parser

#endif //PARSER_TESTGRAMMAR_H
