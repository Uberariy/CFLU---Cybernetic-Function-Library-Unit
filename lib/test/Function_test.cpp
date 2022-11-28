/**
 * @file Function_test.cpp
 * @author your name (you@domain.com)
 * @brief 
 * @version 0.1
 * @date 2022-11-24
 * 
 * @copyright Copyright (c) 2022
 * 
 */

#include "gtest/gtest.h"
#include <iostream>

#include "../Factory.hpp"

class Function_test : public testing::Test {};

TEST(Function_test, Factory) {
    FunctionFactory F;

    auto A1 = F.Create("ident", {});
    Identical A2;
    ASSERT_EQ(typeid(*A1), typeid(A2));

    auto B1 = F.Create("power", {1, 2, 3});
    Power B2(5);
    ASSERT_EQ(typeid(*B1), typeid(B2));

    auto C1 = F.Create("exp");
    Exponential C2(10);
    ASSERT_EQ(typeid(*C1), typeid(C2));

    auto D1 = F.Create("const", {1});
    Constant D2;
    ASSERT_EQ(typeid(*D1), typeid(D2));

    auto E1 = F.Create("polynomial");
    Polynomial E2({1, 2, 3});
    ASSERT_EQ(typeid(*E1), typeid(E2));
}

TEST(Function_test, FunctionSemanticsORString) {
    FunctionFactory F;

    auto A1 = F.Create("polynomial", {0, 2});
    auto A2 = F.Create("ident", 2);
    ASSERT_EQ((*A1).ToString(), (*A2).ToString());

    auto B1 = F.Create("polynomial", {0, 0, 1, 0, 1});
    auto B2 = F.Create("power", {2, 4});
    ASSERT_EQ((*B1).ToString(), (*B2).ToString());

    auto C1 = F.Create("polynomial", {10});
    auto C2 = F.Create("const", 10);
    ASSERT_EQ((*C1).ToString(), (*C2).ToString());

    auto D1 = F.Create("exp", {10});
    auto D2 = F.Create("exp", 10);
    ASSERT_EQ((*D1).ToString(), (*D2).ToString());
}
