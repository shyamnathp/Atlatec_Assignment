/*
This file tests the functions of both Vector and Matrix class. It uses some google test assertions and matchers.
*/

#include "Vector.h"
#include "Matrix.h"

#include <vector>
#include "gtest/gtest.h"
#include "gmock/gmock.h"

using namespace std;

int main()
{

	/*Random Test for Vector class*/
	Vector<int> vecOne({ 1,2 });
	Vector<int> vecTwo({ 1,2 });
	Vector<int> vecThree({ 1,2,3 });

	/*Vector Addition*/
	vecOne.Addition(vecTwo);
	EXPECT_THAT(vecOne.GetVector(), ::testing::ContainerEq(vector<int>({ 2,4 })));

	/*Scalar Multiplication*/
	//Since type of vecOne is int, even after multiplying with a double, the final type will be int
	vecOne.Multiply(2.5);
	EXPECT_THAT(vecOne.GetVector(), ::testing::ContainerEq(vector<int>({ 5,10 })));

	/*Vector Multiplication*/
	vecOne.Multiply(Vector<int>({ 1, 2 }));
	EXPECT_THAT(vecOne.GetVector(), ::testing::ContainerEq(vector<int>({ 5,20 })));

	vecOne.Multiply(vecThree); //Not possible, Message displayed on debug in visual studio

	/*Matrix Multiplication*/
	vecOne.Multiply(Matrix<int>({ {1,2},{3,4} }));
	EXPECT_THAT(vecOne.GetVector(), ::testing::ContainerEq(vector<int>({ 65,90 })));

	
	/*Test for Matrix class*/
	Matrix<int> mOne({ {1,2} , {1,2} });
	Matrix<int> mTwo({ {1,2} , {1,2} });
	Matrix<int> mThree({ {1,2} , {1,2}, {1,2}});

	/*Matrix Addition*/
	mOne.Addition(mTwo);
	EXPECT_THAT(mOne.GetMatrix(), ::testing::ContainerEq(vector<vector<int>>({ {2,4}, {2,4} })));

	/*Scalar Multipliction*/
	mOne.Multiply(2);
	EXPECT_THAT(mOne.GetMatrix(), ::testing::ContainerEq(vector<vector<int>>({ {4,8}, {4,8} })));

	/*Matrix Multiplication*/
	mOne.Multiply(mTwo);
	EXPECT_THAT(mOne.GetMatrix(), ::testing::ContainerEq(vector<vector<int>>({ {12,24}, {12,24} })));

	mOne.Multiply(mThree); //Not possible, Message displayed on debug in visual studio
}