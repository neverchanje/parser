//
// Created by neverchanje on 12/23/15.
//

#include <gtest/gtest.h>
#include "LR0.h"
#include "Symbol.h"
#include "Rule.h"

using namespace parser;

TEST(LR0_Basics, LR0_Basics_Test) {
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
  RuleID
      r1 = Rule::Make(S_, {S}).GetID(),
      r2 = Rule::Make(S, {L, equal, R}).GetID(),
      r3 = Rule::Make(S, {R}).GetID(),
      r4 = Rule::Make(L, {multiply, R}).GetID(),
      r5 = Rule::Make(L, {id}).GetID(),
      r6 = Rule::Make(R, {L}).GetID();

  auto atm = LR0::Automaton::Make(r1);
  atm.Dump();
}