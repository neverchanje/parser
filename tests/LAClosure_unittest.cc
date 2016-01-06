//
// Created by neverchanje on 12/27/15.
//
#include <gtest/gtest.h>
#include "LAClosure.h"
#include "ItemSetTestHelper.h"
#include "TestGrammar.h"

using namespace parser;

#define EXPECT_INSERT_LAITEM(r, off, la) assert(expect.insert(LAItem::MakeUnique(r, off, la)).second)

TEST_F(TestGrammar1, LAClosureBasic1_Test1) {
  // E -> •E + T, $
  ItemSet actual = Closure({LAItem(r1, 0, eor)});

  ItemSet expect;
  EXPECT_INSERT_LAITEM(r1, 0, eor); // E -> •E plus T $ , $
  EXPECT_INSERT_LAITEM(r1, 0, plus); // E -> •E plus T $ , plus
  EXPECT_INSERT_LAITEM(r2, 0, plus); // E -> •T $ , plus
  EXPECT_INSERT_LAITEM(r3, 0, plus); // T -> •T multiply F $ , plus
  EXPECT_INSERT_LAITEM(r3, 0, multiply); // T -> •T multiply F $ , multiply
  EXPECT_INSERT_LAITEM(r4, 0, multiply); // T -> •F $ , multiply
  EXPECT_INSERT_LAITEM(r4, 0, plus); // T -> •F $ , plus
  EXPECT_INSERT_LAITEM(r6, 0, plus); //  F -> •id $ , plus
  EXPECT_INSERT_LAITEM(r5, 0, plus); //  F -> •left_bracket E right_bracket $ , plus
  EXPECT_INSERT_LAITEM(r6, 0, multiply); //  F -> •id $ , multiply
  EXPECT_INSERT_LAITEM(r5, 0, multiply); //  F -> •left_bracket E right_bracket $ , multiply

  EXPECT_PRED_FORMAT2 (AssertItemSetCmp, expect, actual);
}

TEST_F(TestGrammar1, LAClosureBasic1_Test2) {
  // E -> E + •T , $
  ItemSet actual = Closure({LAItem(r1, 2, eor)});

//  DumpClosure(actual);
  ItemSet expect;

  EXPECT_INSERT_LAITEM(r1, 2, eor); //  E -> E plus •T $ , $
  EXPECT_INSERT_LAITEM(r3, 0, eor); //  T -> •T multiply F $ , $
  EXPECT_INSERT_LAITEM(r4, 0, eor); //  T -> •F $ , $
  EXPECT_INSERT_LAITEM(r3, 0, multiply); //  T -> •T multiply F $ , multiply
  EXPECT_INSERT_LAITEM(r4, 0, multiply); //  T -> •F $ , multiply
  EXPECT_INSERT_LAITEM(r5, 0, eor); //  F -> •left_bracket E right_bracket $, $
  EXPECT_INSERT_LAITEM(r6, 0, eor); //  F -> •id $, $
  EXPECT_INSERT_LAITEM(r5, 0, multiply); //  F -> •left_bracket E right_bracket $, multiply
  EXPECT_INSERT_LAITEM(r6, 0, multiply); //  F -> •id $, multiply

  EXPECT_PRED_FORMAT2 (AssertItemSetCmp, expect, actual);
}

TEST_F(TestGrammar2, LAClosureBasic2_Test1) {
  // S_ -> •S, $
  ItemSet actual = Closure({LAItem(r1, 0, eor)});

  ItemSet expect;

  EXPECT_INSERT_LAITEM(r1, 0, eor); //  S_ -> •S $ , $
  EXPECT_INSERT_LAITEM(r2, 0, eor); //  S -> •L = R $ , $
  EXPECT_INSERT_LAITEM(r3, 0, eor); //  S -> •R $ , $
  EXPECT_INSERT_LAITEM(r4, 0, equal); //  L -> •* R $ , =
  EXPECT_INSERT_LAITEM(r5, 0, equal); //  L -> •id $ , =
  EXPECT_INSERT_LAITEM(r6, 0, eor); //  R -> •L $
  EXPECT_INSERT_LAITEM(r4, 0, eor); //  L -> •* R $ , $
  EXPECT_INSERT_LAITEM(r5, 0, eor); //  L -> •id $ , $

  EXPECT_PRED_FORMAT2 (AssertItemSetCmp, expect, actual);
}

// TODO: Add an unit test from https://en.wikipedia.org/wiki/Canonical_LR_parser

TEST_F(TestGrammar3, LAClosureBasic3_Test1) {
  // C -> c •C, c
  // C -> c •C, d
  ItemSet actual = Closure({LAItem(r3, 1, c), LAItem(r3, 1, d)});

  ItemSet expect;

  EXPECT_INSERT_LAITEM(r3, 1, c); //  C -> c •C, c
  EXPECT_INSERT_LAITEM(r3, 1, d); //  C -> c •C, d
  EXPECT_INSERT_LAITEM(r4, 0, c); //  C -> d, c
  EXPECT_INSERT_LAITEM(r4, 0, d); //  C -> d, d
  EXPECT_INSERT_LAITEM(r3, 0, c); //  C -> •c C, c
  EXPECT_INSERT_LAITEM(r3, 0, d); //  C -> •c C, d

  EXPECT_PRED_FORMAT2 (AssertItemSetCmp, expect, actual);
}
