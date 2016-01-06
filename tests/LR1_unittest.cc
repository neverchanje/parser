//
// Created by neverchanje on 12/23/15.
//

#include "LR1.h"
#include "TestGrammar.h"
#include "AutomatonTestHelper.h"

using namespace parser;

TEST_F(TestGrammar3, LR1_Basics1_Test) {
  auto actual = LR1::Automaton::Make(r1);

  DFA expect;
  expect.AddTrans(0, S, 3);
  expect.AddTrans(0, C, 4);
  expect.AddTrans(0, c, 1);
  expect.AddTrans(0, d, 2);
  expect.AddTrans(4, C, 8);
  expect.AddTrans(4, c, 6);
  expect.AddTrans(4, d, 7);
  expect.AddTrans(1, C, 5);
  expect.AddTrans(1, c, 1);
  expect.AddTrans(1, d, 2);
  expect.AddTrans(6, C, 9);
  expect.AddTrans(6, c, 6);
  expect.AddTrans(6, d, 7);

  EXPECT_PRED_FORMAT2 (AssertDFACmp, expect, actual.GetDFA());
}