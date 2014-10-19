// (C) 2013-2014, Sergei Zaychenko, KNURE, Kharkiv, Ukraine

#include "matrix.hpp"


// =================================================================================
// Служебные функции
// ---------------------------------------------------------------------------------
// Проверяет, чтобы количество строк и столбцов было положительным
bool Matrix::isValidDimension(int rows, int cols)
{
	return (rows > 0 && cols > 0);
}

// Проверяет, чтобы переданное значение строки было в допустимых пределах
bool Matrix::isRowInRange(int row) const
{
	return (row > 0 || row <= this->rows);
}

// Проверяет, чтобы переданное значение столбца было в допустимых пределах
bool Matrix::isColInRange(int col) const
{
	return (col > 0 || col <= this->cols);
}

// Выделение памяти под матрицу. Условно считаем входные данные стирильными.
bool Matrix::allocateMemory(int rows, int cols)
{
	try {
		this->matrix = new double*[rows];
		for (int r = 0; r < rows; r++)
		{
			this->matrix[r] = new double[cols];
		}
	}
	// Если системе не удалосы выделить память, обрабатываем исключение
	catch (std::bad_alloc& ba) {
		return false;
	}
	return true;
} // bool Matrix::allocateMemory(int rows, int cols)

void Matrix::setNumRows(int rows)
{
	this->rows = rows;
} // void Matrix::setNumRows(int rows)

void Matrix::setNumColumns(int cols)
{
	this->cols = cols;
} // void setNumColumns(int cols)

// =================================================================================




// =================================================================================
// Конструкторы класса Matrix
// ---------------------------------------------------------------------------------

// Конструктор копий
Matrix::Matrix(const Matrix & _copy)
{
	this->setNumRows(_copy.getNumRows());
	this->setNumColumns(_copy.getNumColumns());
	if (this->allocateMemory(rows, cols) == false)
	{
		throw new std::exception("Couldn't allocate memory.");
	}

	for (int r = 0; r < this->getNumRows(); r++)
	{
		for (int c = 0; c < this->getNumColumns(); c++)
		{
			this->matrix[r][c] = _copy[r][c];
		}
	}
}

// Конструктор перемещения (?)
Matrix::Matrix(Matrix && _temporary)
{
	this->setNumRows(_temporary.getNumRows());
	this->setNumColumns(_temporary.getNumColumns());
	if (this->allocateMemory(rows, cols) == false)
	{
		throw new std::exception("Couldn't allocate memory.");
	}

	for (int r = 0; r < this->getNumRows(); r++)
	{
		for (int c = 0; c < this->getNumColumns(); c++)
		{
			this->matrix[r][c] = _temporary[r][c];
		}
	}
}

// Конструктор, принимающий количество строк и столбцов, заполняющий матрицу нулями. 
// Если количество строк или столбцов не является положительным числом, 
// генерируется исключение с текстом "Invalid dimensions".
Matrix::Matrix(int rows, int cols) 
{
	if ( ! Matrix::isValidDimension(rows, cols))
	{
		throw new std::exception("Invalid dimensions.");
	}

	this->setNumRows(rows);
	this->setNumColumns(cols);

	if (this->allocateMemory(rows, cols) == false)
	{
		throw new std::exception("Couldn't allocate memory.");
	}

	for (int r = 0; r < rows; r++)
	{
		for (int c = 0; c < cols; c++)
		{
			this->matrix[r][c] = 0;
		}
	}
} // Matrix::Matrix(int rows, int cols)

// Конструктор, принимающий количество строк и столбцов, а также указатель на массив 
// данных типа double.Если количество строк или столбцов не является положительным числом, 
// генерируется исключение с текстом "Invalid dimensions", 
// а при отсутствии переданных данных - с текстом "Bad data pointer".
Matrix::Matrix(int rows, int cols, const double * input)
{
	// Проверка входных данных
	if ( ! Matrix::isValidDimension(rows, cols) )
	{
		throw new std::exception("Invalid dimensions.");
	}

	if ( input == NULL )
	{
		throw new std::exception("Bad data pointer.");
	}

	this->setNumRows(rows);
	this->setNumColumns(cols);

	if (this->allocateMemory(rows, cols) == false)
	{
		throw new std::exception("Couldn't allocate memory.");
	}

	for (int r = 0; r < rows; r++)
	{
		for (int c = 0; c < cols; c++)
		{
			this->matrix[r][c] = input[c + r*cols];
		}
	}
} // Matrix::Matrix(int rows, int cols, const double * input)
// =================================================================================


// =================================================================================
// Деструктор класса Matrix
// ---------------------------------------------------------------------------------
Matrix::~Matrix(){
	for (int r = 0; r < this->getNumRows(); r++)
	{
		delete[] this->matrix[r];
	}
	delete[] this->matrix;
	this->matrix = NULL;
}
// =================================================================================


// =================================================================================
// Перегруженные операторы сравнения на равенство == и неравенство !=
// ---------------------------------------------------------------------------------


// =================================================================================


// =================================================================================
// Геттеры класса Matrix
// ---------------------------------------------------------------------------------
int Matrix::getNumRows(void) const
{
	return this->rows;
}

int Matrix::getNumColumns(void) const
{
	return this->cols;
}
// =================================================================================


// =================================================================================
// Операторы индексной выборки для чтения и для записи. При попытке доступа по 
// некорректному номеру строки или столбца должно генерироваться исключение с 
// текстом "Out of range".
// ---------------------------------------------------------------------------------
// Оператор индексной выборки для чтения.
// Возвращает: Объект типа Matrix::MatrixRowAccessor
Matrix::MatrixRowAccessor< const Matrix > Matrix::operator[] (int _rowIndex) const
{
	if ( ! this->isRowInRange(_rowIndex)) 
	{
		throw new std::exception("Out of range.");
	}
	return MatrixRowAccessor< const Matrix >(*this, _rowIndex);
}

// Оператор индексной выборки для записи.
// Возвращает: Объект типа Matrix::MatrixRowAccessor
Matrix::MatrixRowAccessor< Matrix > Matrix::operator[] (int _rowIndex)
{
	if (!this->isRowInRange(_rowIndex))
	{
		throw new std::exception("Out of range.");
	}
	return MatrixRowAccessor< Matrix >(*this, _rowIndex);
}
// =================================================================================



// =================================================================================
// Операторы индексной выборки MatrixRowAccessor - версии для чтения и для записи
// ---------------------------------------------------------------------------------

// Реализация метода уточненного класса class MatrixRowAccessor<const Matrix>
double Matrix::MatrixRowAccessor< const Matrix >::operator[](int _columnIndex) const
{
	if (!this->m_matrix.isColInRange(_columnIndex))
	{
		throw new std::exception("Out of range.");
	}
	return this->m_matrix.matrix[this->m_rowIndex][_columnIndex];
}

// Реализация метода уточненного класса class MatrixRowAccessor<Matrix>
double& Matrix::MatrixRowAccessor< Matrix >::operator[](int _columnIndex)
{
	if (!this->m_matrix.isColInRange(_columnIndex))
	{
		throw new std::exception("Out of range.");
	}
	return this->m_matrix.matrix[this->m_rowIndex][_columnIndex];
}
// =================================================================================



// =================================================================================
// Глобальный оператор вывода содержимого матрицы в стандартный поток. 
// Столбцы должны разделяться символами табуляции (\t), 
// строки - символами новой строки (\n).
// ---------------------------------------------------------------------------------

std::ostream& operator << (std::ostream &stream, Matrix& m)
{
	for (int r = 0; r < m.getNumRows(); r++)
	{
		for (int c = 0; c < m.getNumColumns(); c++)
		{
			stream << m[r][c] << '\t';
		}
		stream << '\n';
	}
	return stream;
}
// =================================================================================
