//#include "tmatrix.h"

#include "gtest.h"
#include "../Polinom/TPolinom.h"

TEST(Polinom, Created_polinom_is_empty) {
    TPolinom polinom;
    EXPECT_EQ(0, polinom.GetLength());
}

TEST(TPolinomTest, EmptyStringConstructor) {
    TPolinom p("");
    EXPECT_EQ(p.GetLength(), 0);
}

TEST(TPolinomTest, SingleMonomConstructor) {
    TPolinom p("3x^2y");
    EXPECT_EQ(p.GetLength(), 1);
    //EXPECT_EQ(p.GetCurrentItem().GetCoef(), 3);
    
}

TEST(TPolinomTest, Addition) {
    TPolinom p1("2x^2y + 3xy^2");
    TPolinom p2("4x^2y - xy^2");
    TPolinom result = p1 + p2;
    EXPECT_EQ(result.GetLength(), 2);
    
}

TEST(TPolinomTest, MultiplicationByScalar) {
    TPolinom p("3x^2y + 2xy^2");
    TPolinom result = p * 2;
    EXPECT_EQ(result.GetLength(), 2);
    
}

TEST(TPolinomTest, Equality) {
    TPolinom p1("2x^2y + 3xy^2");
    TPolinom p2("2x^2y + 3xy^2");
    ASSERT_ANY_THROW(p1 = p2);
}

TEST(TPolinomTest, AddMonom) {
    TPolinom p("2x^2y");
    TMonom newMonom(3, 1, 2, 1);
    p.AddMonom(newMonom);
    EXPECT_EQ(p.GetLength(), 2);
}

TEST(TPolinomTest, ToStringAndFromString) {
    TPolinom p("2x^2y + 3xy^2 - xy");
    string str = p.ToString();
    TPolinom newPolinom(str);
    EXPECT_EQ(p, newPolinom);
}

TEST(TListTest, GetCurrentItem) {
    TList<int> list;
    list.InsertFirst(42);
    list.InsertLast(99);
    list.GoNext();
    EXPECT_EQ(list.GetCurrentItem(), 99);
}