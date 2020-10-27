#include "pch.h"
#include"E:\Проекты\Программы\StaticSnailLibrary\StaticSnailLibrary\PascalSnail.h"
#include "gtest/gtest.h"

TEST(PascalSnail, WithParameter)
{
	Prog2::PascalSnail X(3,3);
	ASSERT_EQ(3, X.GetL());
	ASSERT_EQ(3, X.GetA());
	ASSERT_ANY_THROW(Prog2::PascalSnail Y(-3, -3));
}

TEST(PascalSnailConstructor, WithoutParameter)
{
	Prog2::PascalSnail X;
	ASSERT_EQ(1, X.GetA());
	ASSERT_EQ(1, X.GetL());
}

TEST(PascalSnailMethods, Setters)
{
	const double err = 0.0001;

	Prog2::PascalSnail X;
	X.SetA(5);
	X.SetL(5);
	ASSERT_EQ(5, X.GetL());
	ASSERT_EQ(5, X.GetA());
	Prog2::Point T;
	X.SetAll(T, 3, 3);
	ASSERT_EQ(3, X.GetL());
	ASSERT_EQ(3, X.GetA());
	ASSERT_NEAR(0, X.GetCenter().x, err);
	ASSERT_NEAR(0, X.GetCenter().y, err);
	ASSERT_ANY_THROW(X.SetA(-1));
	ASSERT_ANY_THROW(X.SetL(-1));

}

TEST(PascalSnailMethods, Functions)
{
	Prog2::PascalSnail X;
	const double err = 0.0001, pi = 3.14159;

	//PolarDistance
	ASSERT_NEAR(1, X.PolarDistance(pi/2), err);
	ASSERT_NEAR((X.GetA() + 1), X.PolarDistance(0), err);
	//Curvature
	Prog2::Radius T;
	Prog2::PascalSnail Y(4, 2);
	Y.RadСurv(T);
	ASSERT_NEAR(4,5, T.radiusA, err);
	ASSERT_NEAR(0, T.radiusC, err);
	ASSERT_NEAR(0, T.radiusO, err);
	//PolarArea
	Prog2::PascalSnail Z(2, 4), W(4, 3);
	ASSERT_NEAR(pi * 18, Y.PolarArea(), err);
	ASSERT_NEAR(pi * 1.5, X.PolarArea(), err);
	ASSERT_NEAR(pi * 20.5, W.PolarArea(), err);
	//Form
	ASSERT_NEAR(4, Y.Form(), err);
	ASSERT_NEAR(2, X.Form(), err);
	ASSERT_NEAR(1, Z.Form(), err);
	ASSERT_NEAR(3, W.Form(), err);
}

int main(int argc, char* argv[])
{
	::testing::InitGoogleTest(&argc, argv);
	return RUN_ALL_TESTS();
}