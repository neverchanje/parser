//
// Created by neverchanje on 12/23/15.
//

#include <gtest/gtest.h>
#include "LR0.h"
#include "AutomatonTestHelper.h"
#include "TestGrammar.h"

using namespace parser;

TEST_F(TestGrammar2, LR0_Basics1_Test) {
  auto actual = LR0::Automaton::Make(r1);

//  <from:8, sym:L, to:7>
//  <from:8, sym:R, to:9>
//  <from:8, sym:id, to:2>
//  <from:8, sym:*, to:1>
//  <from:1, sym:L, to:7>
//  <from:1, sym:R, to:6>
//  <from:1, sym:id, to:2>
//  <from:1, sym:*, to:1>
//  <from:5, sym:=, to:8>
//  <from:0, sym:L, to:5>
//  <from:0, sym:R, to:4>
//  <from:0, sym:S, to:3>
//  <from:0, sym:id, to:2>
//  <from:0, sym:*, to:1>
  actual.Dump();

  DFA expect;
  expect.AddTrans(8, L, 7);
  expect.AddTrans(8, R, 9);
  expect.AddTrans(8, id, 2);
  expect.AddTrans(8, multiply, 1);
  expect.AddTrans(1, L, 7);
  expect.AddTrans(1, R, 6);
  expect.AddTrans(1, id, 2);
  expect.AddTrans(1, multiply, 1);
  expect.AddTrans(5, equal, 8);
  expect.AddTrans(0, L, 5);
  expect.AddTrans(0, R, 4);
  expect.AddTrans(0, S, 3);
  expect.AddTrans(0, id, 2);
  expect.AddTrans(0, multiply, 1);
  EXPECT_PRED_FORMAT2 (AssertDFACmp, expect, actual.GetDFA());
}

TEST_F(TestGrammar4, LR0_Basics2_Test) {
  auto atm = LR0::Automaton::Make(r0);

//  <from:8, sym:T, to:11>
//  <from:8, sym:(, to:2>
//  <from:8, sym:F, to:3>
//  <from:8, sym:id, to:1>
//  <from:7, sym:(, to:2>
//  <from:7, sym:F, to:10>
//  <from:7, sym:id, to:1>
//  <from:6, sym:+, to:8>
//  <from:6, sym:), to:9>
//  <from:4, sym:*, to:7>
//  <from:2, sym:E, to:6>
//  <from:2, sym:T, to:4>
//  <from:2, sym:(, to:2>
//  <from:2, sym:F, to:3>
//  <from:2, sym:id, to:1>
//  <from:5, sym:+, to:8>
//  <from:11, sym:*, to:7>
//  <from:0, sym:E, to:5>
//  <from:0, sym:T, to:4>
//  <from:0, sym:(, to:2>
//  <from:0, sym:F, to:3>
//  <from:0, sym:id, to:1>
  atm.Dump();
}