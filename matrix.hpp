// (C) 2013-2014, Sergei Zaychenko, KNURE, Kharkiv, Ukraine

#ifndef _MATRIX_HPP_
#define _MATRIX_HPP_

/*****************************************************************************/
#include <iostream>

class Matrix
{

/*-----------------------------------------------------------------*/
private:
	int rows, cols;
	double ** matrix;

	// ���������, ����� ���������� ����� � �������� ���� ������������
	static bool isValidDimension(int rows, int cols);

	// ���������, ����� ���������� �������� ������ ���� � ���������� ��������
	bool isRowInRange(int row) const;

	// ���������, ����� ���������� �������� ������� ���� � ���������� ��������
	bool isColInRange(int col) const;

	// ��������� ������ ��� �������. ������� ������� ������� ������ �����������.
	bool allocateMemory(int rows, int cols);

	void setNumRows(int rows);

	void setNumColumns(int cols);

public:

	// =================================================================================
	// ������������ ������ Matrix
	// ---------------------------------------------------------------------------------
	// �����������, ����������� ���������� ����� � ��������, ����������� ������� ������. 
	// ���� ���������� ����� ��� �������� �� �������� ������������� ������, 
	// ������������ ���������� � ������� "Invalid dimensions".
	Matrix(int rows, int cols);

	// �����������, ����������� ���������� ����� � ��������, � ����� ��������� �� ������ 
	// ������ ���� double.���� ���������� ����� ��� �������� �� �������� ������������� ������, 
	// ������������ ���������� � ������� "Invalid dimensions", 
	// � ��� ���������� ���������� ������ - � ������� "Bad data pointer".
	Matrix(int rows, int cols, const double * input);

	// ����������� �����
	Matrix(const Matrix & _copy);

	// ����������� �����������
	Matrix(Matrix && _temporary);
	// =================================================================================

	~Matrix();

	// ������������� ��������� ��������� �� ��������� == � ����������� != 
	bool operator==(const Matrix& right) const;
	bool operator!= (const Matrix& right) const;

	// ������������� ��������� �������� � ��������� ������: +, +=, -, -=.
	Matrix operator+ (const Matrix& right) const;
	Matrix operator- (const Matrix& right) const;
	Matrix& operator+=(const Matrix& right);
	Matrix& operator-=(const Matrix& right);

	// ������������� ��������� ��������� ������: *, *=.
	Matrix operator * (const Matrix& _multiplier) const;
	Matrix& operator *= (const Matrix& _multiplier);

	// ������������� ��������� ��������� ������� �� ������: *, *=
	Matrix operator * (const double& _multiplier) const;
	Matrix& operator *= (const double& _multiplier);

	// ���������� �������� ������ ����������� ������� � ����������� �����. 
	// ������� ������ ����������� ��������� ��������� (\t), 
	// ������ - ��������� ����� ������ (\n).
	friend std::ostream& operator << (std::ostream &stream, Matrix& m);

	// �������� ����������
	Matrix & operator=(const Matrix & right);

	// �������� �����������
	// �������� ������ ������� ������� this �� ������� ���������� �������
	Matrix & operator= (Matrix && _right);


	int getNumRows(void) const;

	int getNumColumns(void) const;

/*------------------------------------------------------------------*/

	template< typename _MatrixType >
	class MatrixRowAccessor
	{
		_MatrixType & m_matrix;
		const int m_rowIndex;
	public:
		MatrixRowAccessor ( _MatrixType & _matrix, int _rowIndex )
			:	m_matrix( _matrix )
			,	m_rowIndex( _rowIndex )
		{}
		// �������� ��������� ������� - ������ ��� ������ � ��� ������
		double operator[] (int _columnIndex) const;
		double& operator[] (int _columnIndex);
	};

	
/*****************************************************************************/

	template< typename > friend class MatrixRowAccessor;

/*------------------------------------------------------------------*/

	// ��������� ������� ������ MatrixRowAccessor<Matrix>
	template<>
	class MatrixRowAccessor<Matrix>
	{
		Matrix & m_matrix;
		const int m_rowIndex;
	public:
		MatrixRowAccessor(Matrix & _matrix, int _rowIndex)
			: m_matrix(_matrix)
			, m_rowIndex(_rowIndex)
		{}
		// �������� ��������� ������� - ������ ��� ������ � ��� ������
		//double operator[] (int _columnIndex) const;
		double& operator[] (int _columnIndex);
	};

	// ��������� ������� ������ MatrixRowAccessor<const Matrix>
	template<>
	class MatrixRowAccessor<const Matrix>
	{
		const Matrix & m_matrix;
		const int m_rowIndex;
	public:
		MatrixRowAccessor(const Matrix & _matrix, int _rowIndex)
			: m_matrix(_matrix)
			, m_rowIndex(_rowIndex)
		{}
		// �������� ��������� ������� - ������ ��� ������ � ��� ������
		double operator[] (int _columnIndex) const;
		//double& operator[] (int _columnIndex);
	};

	// ��������� ��������� ������� ��� ������ � ��� ������. ��� ������� ������� �� 
	// ������������� ������ ������ ��� ������� ������ �������������� ���������� � ������� "Out of range".
	//MatrixRowAccessor<double>& operator[ ](int row) {}
	MatrixRowAccessor< const Matrix > operator[] (int _rowIndex) const;

	MatrixRowAccessor< Matrix > operator[] ( int _rowIndex );

	// TODO ...

/*------------------------------------------------------------------*/

};

/*****************************************************************************/

#endif //  _MATRIX_HPP_
