// (C) 2013-2014, Sergei Zaychenko, KNURE, Kharkiv, Ukraine

#ifndef _MATRIX_HPP_
#define _MATRIX_HPP_

/*****************************************************************************/
#include <iostream>
#include <stdexcept>
#include <cfloat> // для проверки выхода за пределы типа double

class Matrix
{

/*-----------------------------------------------------------------*/
private:
	int rows, cols;
	double ** matrix;

	// Проверяет, чтобы количество строк и столбцов было положительно
	static bool isValidDimension(int rows, int cols);

	// Проверяет, чтобы переданное значение строки было в допустимых пределах
	bool isRowInRange(int row) const;

	// Проверяет, чтобы переданное значение столбца было в допустимых пределах
	bool isColInRange(int col) const;

	// Выделение памяти под матрицу. Условно считаем входные данные стирильными.
	bool allocateMemory(int rows, int cols);

	void setNumRows(int rows);

	void setNumColumns(int cols);

public:

	// =================================================================================
	// Конструкторы класса Matrix
	// ---------------------------------------------------------------------------------
	// Конструктор, принимающий количество строк и столбцов, заполняющий матрицу нулями. 
	// Если количество строк или столбцов не является положительным числом, 
	// генерируется исключение с текстом "Invalid dimensions".
	Matrix(int rows, int cols);

	// Конструктор, принимающий количество строк и столбцов, а также указатель на массив 
	// данных типа double.Если количество строк или столбцов не является положительным числом, 
	// генерируется исключение с текстом "Invalid dimensions", 
	// а при отсутствии переданных данных - с текстом "Bad data pointer".
	Matrix(int rows, int cols, const double * input);

	// Конструктор копий
	Matrix(const Matrix & _copy);

	// Конструктор перемещения
	Matrix(Matrix && _temporary);
	// =================================================================================

	~Matrix();

	// Перегруженные операторы сравнения на равенство == и неравенство != 
	bool operator==(const Matrix& right) const;
	bool operator!= (const Matrix& right) const;

	// Перегруженные операторы сложения и вычитания матриц: +, +=, -, -=.
	friend const Matrix operator+ ( const Matrix& left, const Matrix& right );
	friend const Matrix operator- ( const Matrix& left, const Matrix& right );
	friend Matrix& operator+= ( Matrix& left, const Matrix& right );
	friend Matrix& operator-= ( Matrix& left, const Matrix& right );

	// Перегруженные операторы умножения матриц: *, *=.
	Matrix operator * (const Matrix& _multiplier) const;
	Matrix& operator *= (const Matrix& _multiplier);

	// Перегруженные операторы умножения матрицы на скаляр: *, *=
	Matrix operator * (const double& _multiplier) const;
	Matrix& operator *= (const double& _multiplier);

	// Глобальный оператор вывода содержимого матрицы в стандартный поток. 
	// Столбцы должны разделяться символами табуляции (\t), 
	// строки - символами новой строки (\n).
	friend std::ostream& operator << (std::ostream &stream, Matrix& m);

	// Оператор присвоения
	Matrix & operator=(const Matrix & right);

	// Оператор перемещения
	// Заменяем старые ресурсы объекта this на ресурсы временного объекта
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
            
		// Операторы индексной выборки - версии для чтения и для записи
		double operator[] (int _columnIndex) const
        {
            if (!this->m_matrix.isColInRange(_columnIndex))
            {
                throw new Matrix::OutOfRangeException();
            }
            return this->m_matrix.matrix[this->m_rowIndex][_columnIndex];
        }
        
        
		double& operator[] (int _columnIndex)
        {
            if (!this->m_matrix.isColInRange(_columnIndex))
            {
                throw new Matrix::OutOfRangeException();
            }
            return this->m_matrix.matrix[this->m_rowIndex][_columnIndex];
        }
	};
    
	
/*****************************************************************************/

	template< typename > friend class MatrixRowAccessor;

/*------------------------------------------------------------------*/

	// Операторы индексной выборки для чтения и для записи. При попытке доступа по 
	// некорректному номеру строки или столбца должно генерироваться исключение с текстом "Out of range".
	//MatrixRowAccessor<double>& operator[ ](int row) {}
	MatrixRowAccessor< const Matrix > operator[] (int _rowIndex) const;

	MatrixRowAccessor< Matrix > operator[] ( int _rowIndex );

/*------------------------------------------------------------------*/

    struct Exception : std::exception
    {
        std::string msg;
        std::string msg_header = "Matrix exception ";
        Exception( std::string msg ) : msg(msg) {}
        ~Exception() throw () {}
        const char* what() const throw() 
        { 
            std::string output = msg_header + "'" + msg + "'";
            return output.c_str(); 
        }
    };
    
    struct OutOfRangeException : Matrix::Exception
    {
        OutOfRangeException() : Exception("Out of range") {}
    };
    
    struct ValsOutOfRangeException : Matrix::Exception
    {
        ValsOutOfRangeException() : Exception("Values are out of range") {}
    };
    
    struct ErrAllocException : Matrix::Exception
    {
        ErrAllocException() : Exception("Couldn't allocate memory") {}
    };
    
    struct InvalDimensionsException : Matrix::Exception
    {
        InvalDimensionsException() : Exception("Invalid dimensions") {}
    };
    
    struct BadDataPtrException : Matrix::Exception
    {
        BadDataPtrException() : Exception("Bad data pointer") {}
    };
  
    struct SizeMismatchException : Matrix::Exception
    {
        SizeMismatchException() : Exception("Size mismatch") {}
    };
};

/*****************************************************************************/

#endif //  _MATRIX_HPP_
