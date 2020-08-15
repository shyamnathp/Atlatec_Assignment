/*
This function defines the Matrix class along with its functions.
*/
#pragma once
#include<type_traits>
#include<vector>
#include<algorithm>
#include <functional> 
#include <tuple>
#include <windows.h>

using namespace std;

//SFINAE to restrict types to only arithmetic types
template<typename T>
using IsArithmetic = std::enable_if_t<std::is_arithmetic<T>::value>;

template<typename T, typename Enable = void>
class Matrix;

template <typename T>
class Matrix<T, IsArithmetic<T>>
{
	vector<vector<T>> m_matrix;
public:
	Matrix(vector<vector<T>> matrix) : m_matrix(matrix) {};
	Matrix(std::initializer_list<std::initializer_list<T>> matrix){
	for (const auto& row : matrix)
	{
		m_matrix.emplace_back(row);
	}
	};

	/*Gets m_matrix size*/
	std::tuple<int, int> size() const;

	/*Gets m_matrix*/
	vector<vector<T>> GetMatrix() const;

	/*Adds to vectors of same size and updates the m_matrix*/
	void Addition(const Matrix& addMatrix);

	/*Scalar Multiplication - multiplies m_matrix with value and updates m_matrix*/
	void Multiply(double value);

	/*Multiply with mulMatrix and updates m_matrix*/
	void Multiply(const Matrix& mulMatrix);
};

/*Implementation of Matrix class*/

template<typename T>
std::tuple<int, int> Matrix<T, IsArithmetic<T>>::size() const
{
	int rowSize = m_matrix.size();
	int colSize = m_matrix[0].size();
	return make_tuple(rowSize, colSize);
}

template<typename T>
vector<vector<T>> Matrix<T, IsArithmetic<T>>::GetMatrix() const
{
	return m_matrix;
}

template <typename T>
void Matrix<T, IsArithmetic<T>>::Addition(const Matrix& addMatrix)
{
	if (this->size() == addMatrix.size())
	{
		auto m_addMatrix = addMatrix.GetMatrix();
		int i = 0;
		for_each(m_matrix.begin(), m_matrix.end(), [&](auto& row)
		{
			std::transform(row.begin(), row.end(), m_addMatrix[i].begin(), row.begin(), std::plus<T>());
			++i;
		});
	}
	else
	{
		OutputDebugString("Addition - Both matrix not the same size\n");
	}
}

template <typename T>
void Matrix<T, IsArithmetic<T>>::Multiply(double value)
{
	for_each(m_matrix.begin(), m_matrix.end(), [&value](auto& row)
	{
		std::transform(row.begin(), row.end(), row.begin(), [&value](auto& element)
		{
			return element * value;
		});
	});
}

template <typename T>
void Matrix<T, IsArithmetic<T>>::Multiply(const Matrix& mulMatrix)
{
	auto m_mulMatrix = mulMatrix.GetMatrix();

	auto [rowSize, colSize] = this->size();
	auto [mulRowSize, mulColSize] = mulMatrix.size();

	if (colSize == mulRowSize)
	{
		vector<vector<T>> m_prodMatrix(rowSize, vector<T>(mulColSize, 0));

		for (auto j = 0; j < mulColSize; ++j)
		{
			for (auto k = 0; k < colSize; ++k)
			{
				for (auto i = 0; i < rowSize; ++i)
				{
					m_prodMatrix[i][j] += m_matrix[i][k] * m_mulMatrix[k][j];
				}
			}
		}

		m_matrix = std::move(m_prodMatrix);
	}
	else
	{
		OutputDebugString("Multiply - Both Matrix cannot be multiplied\n");
	}
}