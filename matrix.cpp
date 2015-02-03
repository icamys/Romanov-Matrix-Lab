// (C) 2013-2014, Sergei Zaychenko, KNURE, Kharkiv, Ukraine

#include "matrix.hpp"

// Тестовый комментарий. Можно удалить.

// =================================================================================
// Служебные функции
// ---------------------------------------------------------------------------------
// Проверяет, чтобы количество строк и столбцов было положительным
bool Matrix::isValidDimension(int rows, int cols)
{
	return (rows > 0 && cols > 0);
}

// Проверяет, безопасно ли складывать два числа типа double (возможность переполнения)
// Максимальное и минимальное значение double определены как:
// 1.797693e+308 and 2.225074e-308 соответственно.
bool Matrix::isDoubleAdditionSafe(const double& left,  const double& right)
{
    // Для отрицательных чисел
    if ( left < 0.0 && right < 0.0 ) 
    {
        if ( (std::numeric_limits<double>::min() - left) > right)
        {
            return false;
        }
    }
    
    // Для левого отрицательного и правого положительного операнда проверка не нужна
    // if ( left < 0.0 && right > 0.0 ) { }
    
    // Для левого положительного и правого отрицательного операнда проверка не нужна
    // if ( left > 0.0 && right < 0.0 ) { }
    
    // Для нулевого левого операнда проверка не нужна
    // if ( left == 0.0 ) {}
    
    // Для нулевого правого операнда проверка не нужна
    // if ( right == 0.0 ) {}
    
    // Если оба числа положительны
    if ( left > 0.0 && right > 0.0 )
    {
        if ( (std::numeric_limits<double>::max() - left) < right)
        {
            return false;
        }
    }
    return true;
}

// Проверяет, безопасно ли вычитать два числа типа double (возможность переполнения)
// Максимальное и минимальное значение double определены как:
// 1.797693e+308 and 2.225074e-308 соответственно.
bool Matrix::isDoubleSubstractionSafe(const double& left,  const double& right)
{
    // Для отрицательных чисел
    if ( left < 0.0 && right < 0.0 )
    {
        if ( (right - left) <  -(std::numeric_limits<double>::max()) )
        {
            return false;
        }
    }
    
    // Для левого отрицательного и правого положительного операнда
    if ( left < 0.0 && right > 0.0 )
    {
        if ( (std::numeric_limits<double>::min() + right) > left )
        {
            return false;
        }
    }
    
    // Для левого положительного и правого отрицательного операнда
    if ( left > 0.0 && right < 0.0 )
    {
        if ( (left - std::numeric_limits<double>::max()) < right )
        {
            return false;
        }
    }
    
    // Для нулевого левого операнда
    if ( left == 0.0 ) 
    {
        // Если правый операнд отрицательный и больше максимального
        // положительного значения double, то в результате получаем переполнение
        // Максимальному double придаем отрицательный знак, т.к. из правого
        // операнда сделать положительное число не получится.
        if (right < 0.0 && right < -(std::numeric_limits<double>::max()) )
        {
            return false;
        }
    }
    
    // Для нулевого правого операнда проверка не нужна 
    // if ( right == 0.0 ) {}
    
    // Для положительных чисел проверка не нужна
    // if ( left > 0.0 && right > 0.0 ) { }
    
    return true;
}

// Проверяет, безопасно ли перемножать два числа типа double (возможность переполнения)
// Максимальное и минимальное значение double определены как:
// 1.797693e+308 and 2.225074e-308 соответственно.
bool Matrix::isDoubleMultiplicationSafe(const double& left,  const double& right)
{
    // Для отрицательных чисел
    if ( left < 0.0 && right < 0.0 )
    {
        if ( (std::numeric_limits<double>::min() / (-left) ) > right )
        {
            return false;
        }
    }
    
    // Для левого отрицательного и правого положительного операнда
    if ( left < 0.0 && right > 0.0 )
    {
        if ( (std::numeric_limits<double>::min() / right) > left )
        {
            return false;
        }
    }
    
    // Для левого положительного и правого отрицательного операнда
    if ( left > 0.0 && right < 0.0 )
    {
         if ( (std::numeric_limits<double>::min() / left) > right )
        {
            return false;
        }
    }
    
    // Для нулевого левого операнда проверка не нужна
    // if ( left == 0.0 ) { }
    
    // Для нулевого правого операнда проверка не нужна 
    // if ( right == 0.0 ) { }
    
    // Для положительных чисел проверка
    if ( left > 0.0 && right > 0.0 ) 
    {
        if ( (std::numeric_limits<double>::max() / left ) < right )
        {
            return false;
        }
    }
    
    return true;
}

// Проверяет, чтобы переданное значение строки было в допустимых пределах
bool Matrix::isRowInRange(int row) const
{
	return (row >= 0 && row < this->rows);
}

// Проверяет, чтобы переданное значение столбца было в допустимых пределах
bool Matrix::isColInRange(int col) const
{
	return (col >= 0 && col < this->cols);
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
        throw new Matrix::ErrAllocException(__func__, __LINE__, __FILE__);
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
	this->rows      = std::move(_temporary.rows);
	this->cols      = std::move(_temporary.cols);
    this->matrix    = std::move(_temporary.matrix);
}

// Конструктор, принимающий количество строк и столбцов, заполняющий матрицу нулями. 
// Если количество строк или столбцов не является положительным числом, 
// генерируется исключение с текстом "Invalid dimensions".
Matrix::Matrix(int rows, int cols) 
{
	if ( ! Matrix::isValidDimension(rows, cols))
	{
		throw new Matrix::InvalDimensionsException(__func__, __LINE__, __FILE__);
	}

	this->setNumRows(rows);
	this->setNumColumns(cols);

	if (this->allocateMemory(rows, cols) == false)
	{
		throw new Matrix::ErrAllocException(__func__, __LINE__, __FILE__);
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
		throw new Matrix::InvalDimensionsException(__func__, __LINE__, __FILE__);
	}

	if ( input == NULL )
	{
		throw new Matrix::BadDataPtrException(__func__, __LINE__, __FILE__);
	}

	this->setNumRows(rows);
	this->setNumColumns(cols);

	if (this->allocateMemory(rows, cols) == false)
	{
		throw new Matrix::ErrAllocException(__func__, __LINE__, __FILE__);
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
	this->matrix = nullptr;
}
// =================================================================================


// =================================================================================
// Перегруженные операторы сравнения на равенство == и неравенство !=
// ---------------------------------------------------------------------------------
bool operator == (const Matrix& left, const Matrix& right)
{
    // Если размеры матриц не совпадают, они точно не равны
    if ( left.getNumColumns() != right.getNumColumns() ||
         left.getNumRows() != right.getNumRows() )
    {
        return false;
    }
    
    // Поэлементное сравнение элементов матриц
    for (int row = 0; row < left.getNumRows(); row++)
    {
        for (int col = 0; col < left.getNumColumns(); col++) 
        {
            if ( left.matrix[row][col] != right.matrix[row][col]) return false;
        }
    }
    
    return true;
}

bool operator != ( const Matrix& left, const Matrix& right )
{
    return !(left == right);
}

// =================================================================================

// =================================================================================
// Перегруженные операторы сложения и вычитания матриц: +, +=, -, -=.
// ---------------------------------------------------------------------------------
const Matrix operator + ( const Matrix& left, const Matrix& right )
{
    if (left.getNumColumns()   != right.getNumColumns() ||
        left.getNumRows()      != right.getNumRows() )
    {
        throw new Matrix::SizeMismatchException(__func__, __LINE__, __FILE__);
    }
    
    Matrix sum_result = Matrix(left.getNumRows(), left.getNumColumns());
    
    for (int row = 0; row < left.getNumRows(); row++)
    {
        for (int col = 0; col < left.getNumColumns(); col++) 
        {
            if ( ! Matrix::isDoubleAdditionSafe(left.matrix[row][col], right.matrix[row][col]) )
            {
                throw new Matrix::ValsOutOfRangeException(__func__, __LINE__, __FILE__);
            }
            sum_result[row][col] = left.matrix[row][col] + right.matrix[row][col];
        }
    }
    
    return sum_result; 
}

const Matrix operator - ( const Matrix& left, const Matrix& right )
{
    if (left.getNumColumns()   != right.getNumColumns() ||
        left.getNumRows()      != right.getNumRows() )
    {
        throw new Matrix::SizeMismatchException(__func__, __LINE__, __FILE__);
    }
    
    Matrix sum_result = Matrix(left.getNumRows(), left.getNumColumns());
    
    for (int row = 0; row < left.getNumRows(); row++)
    {
        for (int col = 0; col < left.getNumColumns(); col++) 
        {
            if ( ! Matrix::isDoubleSubstractionSafe(left.matrix[row][col], right.matrix[row][col]) )
            {
                throw new Matrix::ValsOutOfRangeException(__func__, __LINE__, __FILE__);
            }
            sum_result[row][col] = left.matrix[row][col] - right.matrix[row][col];
        }
    }
    
    return sum_result; 
}

Matrix& Matrix::operator += ( const Matrix& right )
{
    if (this->getNumColumns()   != right.getNumColumns() ||
        this->getNumRows()      != right.getNumRows() )
    {
        throw new Matrix::SizeMismatchException(__func__, __LINE__, __FILE__);
    }
    
    for (int row = 0; row < this->getNumRows(); row++)
    {
        for (int col = 0; col < this->getNumColumns(); col++) 
        {
            if ( ! Matrix::isDoubleAdditionSafe(this->matrix[row][col], right.matrix[row][col]) )
            {
                throw new Matrix::ValsOutOfRangeException(__func__, __LINE__, __FILE__);
            }
            this->matrix[row][col] += right.matrix[row][col];
        }
    }
    
    return *this; 
}

Matrix& Matrix::operator -= ( const Matrix& right )
{
    if (this->getNumColumns()   != right.getNumColumns() ||
        this->getNumRows()      != right.getNumRows() )
    {
        throw new Matrix::SizeMismatchException(__func__, __LINE__, __FILE__);
    }
    
    for (int row = 0; row < this->getNumRows(); row++)
    {
        for (int col = 0; col < this->getNumColumns(); col++) 
        {
            if ( ! Matrix::isDoubleSubstractionSafe(this->matrix[row][col], right.matrix[row][col]) )
            {
                throw new Matrix::ValsOutOfRangeException(__func__, __LINE__, __FILE__);
            }
            this->matrix[row][col] -= right.matrix[row][col];
        }
    }
    
    return *this; 
}
// =================================================================================


// =================================================================================
// Перегруженные операторы умножения матриц: *, *=.
// ---------------------------------------------------------------------------------
const Matrix operator * ( const Matrix& left, const Matrix& right )
{
    // Если количество столбцов левой матрицы не соответствует количеству строк 
    // правой матрицы - выбрасываем исключение
    if ( left.getNumColumns() != right.getNumRows() )
    {
        throw new Matrix::SizeMismatchException(__func__, __LINE__, __FILE__);
    }
    double temp = 0;
    Matrix mul_result = Matrix(left.getNumRows(), right.getNumColumns());
    
    // Проходимся по строкам и столбцам результирующей матрицы
    // и заполняем ее
    for (int row = 0; row < mul_result.getNumRows(); row++)
    {
        for (int col = 0; col < mul_result.getNumColumns(); col++) 
        {
            for (int col_left = 0; col_left < left.getNumColumns(); col_left++) 
            {
                if ( ! Matrix::isDoubleMultiplicationSafe(
                        left.matrix[row][col_left], right.matrix[col_left][col]))
                {
                    throw new Matrix::ValsOutOfRangeException(__func__, __LINE__, __FILE__);
                }
                
                temp = left.matrix[row][col_left] * right.matrix[col_left][col];
                
                if ( ! Matrix::isDoubleAdditionSafe(mul_result[row][col],temp))
                {
                    throw new Matrix::ValsOutOfRangeException(__func__, __LINE__, __FILE__);
                }
                mul_result[row][col] =  mul_result[row][col] + temp;
            }
        }
    }
    
    return mul_result; 
}


// =================================================================================


// =================================================================================
// Перегруженные операторы умножения матрицы на скаляр: *, *=.
// ---------------------------------------------------------------------------------
const Matrix operator * ( const Matrix& m, const double& _multiplier )
{
    Matrix mul_result = Matrix(m.getNumRows(), m.getNumColumns());
    
    for (int row = 0; row < m.getNumRows(); row++)
    {
        for (int col = 0; col < m.getNumColumns(); col++) 
        {
            if ( ! Matrix::isDoubleMultiplicationSafe(m.matrix[row][col],_multiplier))
            {
                throw new Matrix::ValsOutOfRangeException(__func__, __LINE__, __FILE__);
            }
            mul_result[row][col] = m.matrix[row][col] * _multiplier;
        }
    }
    return mul_result; 
}

const Matrix operator * ( const double& _multiplier, const Matrix& m )
{
    return Matrix(m * _multiplier); 
}

Matrix& Matrix::operator *= ( const double& _multiplier )
{
    for (int row = 0; row < this->getNumRows(); row++)
    {
        for (int col = 0; col < this->getNumColumns(); col++) 
        {
            if ( ! Matrix::isDoubleMultiplicationSafe(this->matrix[row][col], _multiplier))
            {
                throw new Matrix::ValsOutOfRangeException(__func__, __LINE__, __FILE__);
            }
            this->matrix[row][col] *= _multiplier;
        }
    }
    return *this;  
}
// =================================================================================



// =================================================================================
// Операторы присвоения и перемещения
// ---------------------------------------------------------------------------------

// Оператор присвоения
Matrix& Matrix::operator =(const Matrix& right)
{
    this->setNumRows(right.getNumRows());
	this->setNumColumns(right.getNumColumns());
	if (this->allocateMemory(rows, cols) == false)
	{
        throw new Matrix::ErrAllocException(__func__, __LINE__, __FILE__);
	}

	for (int r = 0; r < this->getNumRows(); r++)
	{
		for (int c = 0; c < this->getNumColumns(); c++)
		{
			this->matrix[r][c] = right[r][c];
		}
	}
    return *this;
}


// Оператор перемещения
Matrix& Matrix::operator =(Matrix && right)
{
    this->rows      = std::move(right.rows);
	this->cols      = std::move(right.cols);
    this->matrix    = std::move(right.matrix);
}


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
		throw new Matrix::OutOfRangeException(__func__, __LINE__, __FILE__);
	}
	return MatrixRowAccessor< const Matrix >(*this, _rowIndex);
}

// Оператор индексной выборки для записи.
// Возвращает: Объект типа Matrix::MatrixRowAccessor
Matrix::MatrixRowAccessor< Matrix > Matrix::operator[] (int _rowIndex)
{
	if (!this->isRowInRange(_rowIndex))
	{
		throw new Matrix::OutOfRangeException(__func__, __LINE__, __FILE__);
	}
	return MatrixRowAccessor< Matrix >(*this, _rowIndex);
}
// =================================================================================



// =================================================================================
// Операторы индексной выборки MatrixRowAccessor - версии для чтения и для записи
// ---------------------------------------------------------------------------------

// Реализация метода уточненного класса class MatrixRowAccessor<const Matrix>


// Реализация метода уточненного класса class MatrixRowAccessor<Matrix>

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
