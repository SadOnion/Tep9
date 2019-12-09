#pragma once
#include <vector>
#include <string>
template<typename T>
class Matrix
{
private:
	std::vector<std::vector<T>> matrix;
	int sizeI;
	int sizeJ;
public:
	Matrix(int i,int j);
	std::vector<T>& operator[](int i);
	std::string ToString();
};

template<typename T>
inline Matrix<T>::Matrix(int i, int j)
{
	matrix.resize(i);
	for (int x = 0; x < i; x++)
	{
		matrix[x].resize(j);
	}
}

template<typename T>
std::vector<T>& Matrix<T>::operator[](int i)
{
	return matrix[i];
}

template<typename T>
inline std::string Matrix<T>::ToString()
{
	std::string returnString ="";
	for (int i = 0; i < matrix.size(); i++)
	{
		returnString += "[ ";
		for (int j = 0; j < matrix[0].size(); j++)
		{
			returnString += matrix[i][j];
			returnString += ", ";
		}
		returnString += " ];";
	}
}


