/*
This function defines the Vector class along with its functions.
*/
#pragma once
#include<type_traits>
#include<vector>
#include<algorithm>
#include <functional> 
#include <any>
#include <windows.h>

#include "Matrix.h"

using namespace std;

//SFINAE to restrict types to only arithmetic types
template<typename T>
using IsArithmetic = std::enable_if_t<std::is_arithmetic<T>::value>;

template<typename T, typename Enable = void>
class Vector;

template <typename T>
class Vector<T, IsArithmetic<T>>
{
	vector<T> m_vector;
	public:
	Vector(vector<T> vec) : m_vector(vec) {};
	Vector(std::initializer_list<T> vec) : m_vector(vec) {};

	/*size of m_vector*/
	size_t size() const;

	/*Gets m_vector*/
	vector<T> GetVector() const;

	/*Adds addVector(same size) to m_vector and updates the m_vector*/
	void Addition(const Vector& addVector);

	/*Scalar Multiplication - multiplies m_vector with value and updates m_vector*/
	void Multiply(double value);

	/*Multiplies two vectors together and updates m_vector*/
	void Multiply(const Vector& mulVector);

	/*Multiplies a vector with a matrix and updates m_vector*/
	template <typename T_>
	void Multiply(const Matrix<T_>& mulMatrix);
};


/*Implementation of Vector class*/

template<typename T>
size_t Vector<T, IsArithmetic<T>>::size() const
{
	return m_vector.size();
}

template<typename T>
vector<T> Vector<T, IsArithmetic<T>>::GetVector() const
{
	return m_vector;
}

template <typename T>
void Vector<T, IsArithmetic<T>>::Multiply(double value)
{
	std::transform(m_vector.begin(), m_vector.end(), m_vector.begin(), [&value](const auto& element)
	{
		return element * value;
	});
}

template <typename T>
void Vector<T, IsArithmetic<T>>::Addition(const Vector& addVector)
{

	auto m_addVector = addVector.GetVector();

	if (addVector.size() == m_vector.size())
	{
		std::transform(m_vector.begin(), m_vector.end(), m_addVector.begin(), m_vector.begin(), std::plus<T>());
	}
	else
	{
		OutputDebugString("Addition - Vectors not the same size\n");
	}
}

template <typename T>
void Vector<T, IsArithmetic<T>>::Multiply(const Vector& mulVector)
{
	auto m_multVector = mulVector.GetVector();
	if (m_vector.size() == m_multVector.size())
	{
		std::transform(m_vector.begin(), m_vector.end(), m_multVector.begin(), m_vector.begin(), std::multiplies<T>());
	}
	else
	{
		OutputDebugString("Multiply - Vectors not the same size\n");
	}

}

template <typename T>
template <typename T_>
void Vector<T, IsArithmetic<T>>::Multiply(const Matrix<T_>& mulMatrix)
{
	auto m_mulMatrix = mulMatrix.GetMatrix();
	auto [m_mulRowSize, m_mulColSize] = mulMatrix.size();

	if (m_vector.size() == m_mulRowSize)
	{
		vector<T> m_prodVector(m_vector.size(), 0);

		for (auto i = 0; i < m_vector.size(); ++i)
		{
			for (auto j = 0; j < m_mulRowSize; ++j)
			{
				m_prodVector[i] += m_vector[j]*m_mulMatrix[j][i];
			}
		}

		m_vector = m_prodVector;

	}
	else
	{
		OutputDebugString("Multiply - Vector and Matrix not the same size\n");
	}
}


