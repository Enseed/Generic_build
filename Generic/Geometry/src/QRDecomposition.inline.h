/*******************************************************************************
 Original code from Leo Singleton
 http://www.leosingleton.com/projects/courses/math2601/qr/
*******************************************************************************/

#ifndef __GEOMETRY_QRDECOMPOSITION_INLINE__
#define __GEOMETRY_QRDECOMPOSITION_INLINE__

// Factorise a matrix A into a Q and R matrices such that A = Q*R, Q being
// orthogonal (Q^t = Q^-1 or Q^tQ = I) and R is an upper triangle matrix

//==============================================================================
// CLASS LUDecomposition
//==============================================================================
#include "../Matrix.h"
#include <cstdlib>

namespace seed {


namespace {
// from http://www.leosingleton.com/projects/courses/math2601/qr/
// (i.e. THIS CODE IS COPYRIGHTED - as in REPLACE THIS CODE!!!!) 

/* special subtraction routine used only by Householder reflections;
   subtracts two matrics of different sizes, the smaller being aligned with
   the bottom-right corner of the larger matrix; stores in left_large */

/* the precision of the matrix operations can be modified by changing the
   following typedef */
typedef double matrix_element;


/* the matrix structure */
typedef struct
{
    matrix_element *elements;
    unsigned int rows, cols;
} matrix;

inline static matrix_element vector_row_dot_row(const matrix *vector1,
                                         const matrix *vector2);
inline static matrix_element vector_row_dot_col(const matrix *vector1,
                                         const matrix *vector2);
inline static matrix_element vector_col_dot_row(const matrix *vector1,
                                         const matrix *vector2);
inline static matrix_element vector_col_dot_col(const matrix *vector1,
                                         const matrix *vector2);

/* matrix element accessor */
#define MATRIX_GET_ELEMENT(M, row, col) \
    ((M)->elements[((col) * (M)->rows) + (row)])



	
	
static inline void matrix_empty(matrix *ptr)
{
    /* make ptr an empty matrix */
    ptr->elements = NULL;
    ptr->rows = 0;
    ptr->cols = 0;
}

static inline void matrix_malloc(matrix *ptr, const unsigned int rows,
                          const unsigned int cols)
{
    /* allocate memory for the elements */
    if ((ptr->elements = (matrix_element*)malloc(rows * cols * sizeof(matrix_element))) ==
        NULL)
	{
        ptr->rows = 0;
		ptr->cols = 0;
		return;
	}
	
    /* set the dimensions of the matrix */
    ptr->rows = rows;
    ptr->cols = cols;
}

static inline void matrix_realloc(matrix *ptr, const unsigned int rows,
                           const unsigned int cols)
{
    matrix_element *new_elements;

    /* try to reallocate the matrix */
    if ((new_elements = (matrix_element*)realloc(ptr->elements, rows * cols *
        sizeof(matrix_element))) == NULL)
        return;

    /* the old pointer is no longer valid; replace it with the new one */
    ptr->elements = new_elements;

    /* update the matrix dimensions */
    ptr->rows = rows;
    ptr->cols = cols;
}

static inline void matrix_free(matrix *ptr)
{
    /* free the elements */
    free(ptr->elements);

    /* set the dimensions to zero */
    ptr->rows = 0;
    ptr->cols = 0;
}


static inline void matrix_identity(matrix *result)
{
    unsigned int row, col;

    /* fill the matrix with the identity */
    for (row=0; row<result->rows; row++)
    {
        for (col=0; col<result->cols; col++)
        {
            if (row == col)
                MATRIX_GET_ELEMENT(result, row, col) = (matrix_element)1;
            else
                MATRIX_GET_ELEMENT(result, row, col) = (matrix_element)0;
        }
    }
}


static inline void matrix_addition(const matrix *left, const matrix *right,
                            matrix *result)
{
    unsigned int row, col;

#ifdef __CHECK_DIMENSIONS__
    /* make sure the dimensions of the matrices are correct */
    if ((left->cols != right->cols) || (left->rows != right->rows) ||
        (left->cols != result->cols) || (left->rows != result->rows))
    {
        error("Invalid matrix dimensions for matrix addition!");
        return;
    }
#endif /* __CHECK_DIMENSIONS__ */

    /* iterate through the elements of the matrix */
    for (row=0; row<left->rows; row++)
    {
        for (col=0; col<left->cols; col++)
        {
            /* add individual elements */
            MATRIX_GET_ELEMENT(result, row, col) =
                MATRIX_GET_ELEMENT(left, row, col) +
                MATRIX_GET_ELEMENT(right, row, col);
        }
    }
}

static inline void matrix_subtraction(const matrix *left, const matrix *right,
                               matrix *result)
{
    unsigned int row, col;

#ifdef __CHECK_DIMENSIONS__
    /* make sure the dimensions of the matrices are correct */
    if ((left->cols != right->cols) || (left->rows != right->rows) ||
        (left->cols != result->cols) || (left->rows != result->rows))
    {
        error("Invalid matrix dimensions for matrix subtraction!");
        return;
    }
#endif /* __CHECK_DIMENSIONS__ */

    /* iterate through the elements of the matrix */
    for (row=0; row<left->rows; row++)
    {
        for (col=0; col<left->cols; col++)
        {
            /* add individual elements */
            MATRIX_GET_ELEMENT(result, row, col) =
                MATRIX_GET_ELEMENT(left, row, col) -
                MATRIX_GET_ELEMENT(right, row, col);
        }
    }
}


static inline void matrix_multiplication(const matrix *left, const matrix *right,
                                  matrix *result)
{
    unsigned int row, col, pos;
    matrix_element value;

#ifdef __CHECK_DIMENSIONS__
    /* make sure the dimensions of the matrices are correct */
    if ((left->cols != right->rows) || (result->rows != left->rows) ||
        (result->cols != right->cols))
    {
        error("Invalid matrix dimensions for matrix multiplication!");
        return;
    }
#endif /* __CHECK_DIMENSIONS__ */

    /* iterate through each element of the result matrix */
    for (row=0; row<result->rows; row++)
    {
        for (col=0; col<result->cols; col++)
        {
            /* multiply the corresponding row of left by the corresponding
               column of right */
            value = (matrix_element)0;
            for (pos=0; pos<left->cols; pos++)
                value += MATRIX_GET_ELEMENT(left, row, pos) *
                    MATRIX_GET_ELEMENT(right, pos, col);
            MATRIX_GET_ELEMENT(result, row, col) = value;
        }
    }
}


static inline void matrix_constant_multiplication(const matrix *original,
                                           const matrix_element constant,
                                           matrix *result)
{
    unsigned int row, col;

#ifdef __CHECK_DIMENSIONS__
    /* make sure the dimensions of the matrices are correct */
    if ((original->rows != result->rows) || (original->cols != result->cols))
    {
        error("Invalid dimensions for matrix multiplication by a constant!");
        return;
    }
#endif /* __CHECK_DIMENSIONS__ */

    /* iterate through the elements of the matrix */
    for (row=0; row<original->rows; row++)
    {
        for (col=0; col<original->cols; col++)
        {
            /* multiply individual elements by the constant*/
            MATRIX_GET_ELEMENT(result, row, col) =
                MATRIX_GET_ELEMENT(original, row, col) * constant;
        }
    }
}

static inline void matrix_constant_division(const matrix *original,
                                     const matrix_element constant,
                                     matrix *result)
{
    unsigned int row, col;

#ifdef __CHECK_DIMENSIONS__
    /* make sure the dimensions of the matrices are correct */
    if ((original->rows != result->rows) || (original->cols != result->cols))
    {
        error("Invalid dimensions for matrix division by a constant!");
        return;
    }
#endif /* __CHECK_DIMENSIONS__ */

    /* iterate through the elements of the matrix */
    for (row=0; row<original->rows; row++)
    {
        for (col=0; col<original->cols; col++)
        {
            /* multiply individual elements by the constant*/
            MATRIX_GET_ELEMENT(result, row, col) =
                MATRIX_GET_ELEMENT(original, row, col) / constant;
        }
    }
}


static inline matrix_element vector_dot_product(const matrix *vector1,
                                         const matrix *vector2)
{
    /* determine the orientation of the first vector */
    if (vector1->cols == 1)
    {
        /* determine the orientation of the second vector */
        if (vector2->cols == 1)
            return vector_col_dot_col(vector1, vector2);
        else if (vector2->rows == 1)
            return vector_col_dot_row(vector1, vector2);
    }
    else if (vector1->rows == 1)
    {
        /* determine the orientation of the second vector */
        if (vector2->cols == 1)
            return vector_row_dot_col(vector1, vector2);
        else if (vector2->rows == 1)
            return vector_row_dot_row(vector1, vector2);
    }

    /* if the matrices didn't fit one of the above four orientations, they
       can't be dot-multiplied */
#ifdef __CHECK_DIMENSIONS__
    error("Invalid matrix dimensions for vector dot product!");
#endif /* __CHECK_DIMENSIONS__ */
    return (matrix_element)0;
}

static inline matrix_element vector_col_dot_col(const matrix *vector1,
                                         const matrix *vector2)
{
    matrix_element result = (matrix_element)0;
    unsigned int pos;

#ifdef __CHECK_DIMENSIONS__
    /* check dimension of vectors */
    if ((vector1->rows != vector2->rows) || (vector1->cols != 1) ||
        (vector2->cols != 1))
    {
        error("Invalid matrix dimensions for vector dot product!");
        return (matrix_element)0;
    }
#endif /* __CHECK_DIMENSIONS__ */

    /* dot product column vector with column vector */
    for (pos=0; pos<vector1->rows; pos++)
        result += MATRIX_GET_ELEMENT(vector1, pos, 0) *
        MATRIX_GET_ELEMENT(vector2, pos, 0);

    /* return result */
    return result;
}

static inline matrix_element vector_col_dot_row(const matrix *vector1,
                                         const matrix *vector2)
{
    matrix_element result = (matrix_element)0;
    unsigned int pos;

#ifdef __CHECK_DIMENSIONS__
    /* check dimension of vectors */
    if ((vector1->rows != vector2->cols) || (vector1->cols != 1) ||
        (vector2->rows != 1))
    {
        error("Invalid matrix dimensions for vector dot product!");
        return (matrix_element)0;
    }
#endif /* __CHECK_DIMENSIONS__ */

    /* dot product column vector with column vector */
    for (pos=0; pos<vector1->rows; pos++)
        result += MATRIX_GET_ELEMENT(vector1, pos, 0) *
        MATRIX_GET_ELEMENT(vector2, 0, pos);

    /* return result */
    return result;
}

static inline matrix_element vector_row_dot_col(const matrix *vector1,
                                         const matrix *vector2)
{
    matrix_element result = (matrix_element)0;
    unsigned int pos;

#ifdef __CHECK_DIMENSIONS__
    /* check dimension of vectors */
    if ((vector1->cols != vector2->rows) || (vector1->rows != 1) ||
        (vector2->cols != 1))
    {
        error("Invalid matrix dimensions for vector dot product!");
        return (matrix_element)0;
    }
#endif /* __CHECK_DIMENSIONS__ */

    /* dot product column vector with column vector */
    for (pos=0; pos<vector1->cols; pos++)
        result += MATRIX_GET_ELEMENT(vector1, 0, pos) *
        MATRIX_GET_ELEMENT(vector2, pos, 0);

    /* return result */
    return result;
}

static inline matrix_element vector_row_dot_row(const matrix *vector1,
                                         const matrix *vector2)
{
    matrix_element result = (matrix_element)0;
    unsigned int pos;

#ifdef __CHECK_DIMENSIONS__
    /* check dimension of vectors */
    if ((vector1->cols != vector2->cols) || (vector1->rows != 1) ||
        (vector2->rows != 1))
    {
        error("Invalid matrix dimensions for vector dot product!");
        return (matrix_element)0;
    }
#endif /* __CHECK_DIMENSIONS__ */

    /* dot product column vector with column vector */
    for (pos=0; pos<vector1->cols; pos++)
        result += MATRIX_GET_ELEMENT(vector1, 0, pos) *
        MATRIX_GET_ELEMENT(vector2, 0, pos);

    /* return result */
    return result;
}


static inline matrix_element vector_norm(const matrix *vector)
{
    /* we don't have to worry about checking dimensions, because the dot
       product will do that for us */
    return (matrix_element)sqrt((double)vector_dot_product(vector, vector));
}

static inline matrix_element vector_col_norm(const matrix *vector)
{
    /* we don't have to worry about checking dimensions, because the dot
       product will do that for us */
    return (matrix_element)sqrt((double)vector_col_dot_col(vector, vector));
}

static inline matrix_element vector_row_norm(const matrix *vector)
{
    /* we don't have to worry about checking dimensions, because the dot
       product will do that for us */
    return (matrix_element)sqrt((double)vector_row_dot_row(vector, vector));
}


static inline void matrix_copy(const matrix *src, matrix *dest)
{
#ifdef __CHECK_DIMENSIONS__
    /* check matrix dimensions */
    if ((src->rows != dest->rows) || (src->cols != dest->cols))
    {
        error("Invalid matrix dimensions in matrix_copy()!");
        return;
    }
#endif /* __CHECK_DIMENSIONS__ */

    /* copy the elements */
    (void)memcpy(dest->elements, src->elements, src->rows * src->cols *
        sizeof(matrix_element));
}

static inline void matrix_transpose(const matrix *src, matrix *dest)
{
    unsigned int row, col;

#ifdef __CHECK_DIMENSIONS__
    /* check matrix dimensions */
    if ((src->rows != dest->cols) || (src->cols != dest->rows))
    {
        error("Invalid matrix dimensions in matrix_transpose()!");
        return;
    }
#endif /* __CHECK_DIMENSIONS__ */

    /* transpose the matrix element-by-element */
    for (row=0; row<src->rows; row++)
    {
        for (col=0; col<src->cols; col++)
        {
            MATRIX_GET_ELEMENT(dest, col, row) = MATRIX_GET_ELEMENT(src, row,
                col);
        }
    }
}


static inline void matrix_get_col_vector(const matrix *source,
                                  const unsigned int col,
                                  const unsigned int row_start,
                                  const unsigned int elements,
                                  matrix *vector)
{
    unsigned int row;

#ifdef __CHECK_DIMENSIONS__
    /* check matrix dimensions */
    if ((vector->cols != 1) || (vector->rows != elements) ||
        (source->cols <= col) || (source->rows < row_start + elements))
    {
        error("Invalid matrix dimensions in matrix_get_col_vector()!");
        return;
    }
#endif /* __CHECK_DIMENSIONS__ */

    /* get elements from matrix and store them in the column vector */
    for (row=0; row<elements; row++)
        MATRIX_GET_ELEMENT(vector, row, 0) =
            MATRIX_GET_ELEMENT(source, row + row_start, col);
}

static inline void matrix_get_row_vector(const matrix *source,
                                  const unsigned int row,
                                  const unsigned int col_start,
                                  const unsigned int elements,
                                  matrix *vector)
{
    unsigned int col;

#ifdef __CHECK_DIMENSIONS__
    /* check matrix dimensions */
    if ((vector->rows != 1) || (vector->cols != elements) ||
        (source->rows <= row) || (source->cols < col_start + elements))
    {
        error("Invalid matrix dimensions in matrix_get_row_vector()!");
        return;
    }
#endif /* __CHECK_DIMENSIONS__ */

    /* get elements from matrix and store them in the column vector */
    for (col=0; col<elements; col++)
        MATRIX_GET_ELEMENT(vector, 0, col) =
            MATRIX_GET_ELEMENT(source, row, col + col_start);
}


static inline void matrix_col_vector_transpose_multiplication(const matrix *vector,
                                                       matrix *result)
{
    unsigned int row, col;

#ifdef __CHECK_DIMENSIONS__
    /* check matrix dimensions */
    if ((vector->cols != 1) || (result->rows != vector->rows) ||
        (result->cols != vector->rows))
    {
        error("Invalid matrix dimensions in \
matrix_col_vector_transpose_multiplication()!");
        return;
    }
#endif /* __CHECK_DIMENSIONS__ */

    /* iterate through the elements of the matrix */
    for (row=0; row<vector->rows; row++)
    {
        for (col=0; col<vector->rows; col++)
        {
            MATRIX_GET_ELEMENT(result, row, col) =
                MATRIX_GET_ELEMENT(vector, row, 0) *
                MATRIX_GET_ELEMENT(vector, col, 0);
        }
    }
}

static inline void matrix_row_vector_transpose_multiplication(const matrix *vector,
                                                       matrix *result)
{
    unsigned int row, col;

#ifdef __CHECK_DIMENSIONS__
    /* check matrix dimensions */
    if ((vector->rows != 1) || (result->rows != vector->cols) ||
        (result->cols != vector->cols))
    {
        error("Invalid matrix dimensions in \
matrix_row_vector_transpose_multiplication()!");
        return;
    }
#endif /* __CHECK_DIMENSIONS__ */

    /* iterate through the elements of the matrix */
    for (row=0; row<vector->cols; row++)
    {
        for (col=0; col<vector->cols; col++)
        {
            MATRIX_GET_ELEMENT(result, row, col) =
                MATRIX_GET_ELEMENT(vector, 0, row) *
                MATRIX_GET_ELEMENT(vector, 0, col);
        }
    }
}


static inline double matrix_get_max_element(const matrix *src)
{
    unsigned int row, col;
    double max_value = 0.0;
    double element_value;

    /* find the maximum value in the matrix */
    for (row=0; row<src->rows; row++)
    {
        for (col=0; col<src->cols; col++)
        {
            /* get element value */
            element_value = MATRIX_GET_ELEMENT(src, row, col);
            
            /* make absolute value */
            if (element_value < 0.0)
                element_value = -element_value;

            /* compare with max */
            if (element_value > max_value)
                max_value = element_value;
        }
    }

    /* return the maximum element value (absolute value) */
    return max_value;
}

/* special subtraction routine used only by Householder reflections;
   subtracts two matrics of different sizes, the smaller being aligned with
   the bottom-right corner of the larger matrix; stores in left_large */
static inline void householder_corner_subtraction(matrix *left_large,
                                           const matrix *right_small)
{
    unsigned int row, col;
    unsigned int row_offset, col_offset;

#ifdef __CHECK_DIMENSIONS__
    /* check the dimensions of the result matrices */
    if ((left_large->rows < right_small->rows) ||
        (left_large->cols < right_small->cols))
    {
        error("Invalid matrix dimensions in matrix_corner_subtraction()!");
        return;
    }
#endif /* __CHECK_DIMENSIONS__ */

    /* calculate start offsets for the large matrix */
    row_offset = left_large->rows - right_small->rows;
    col_offset = left_large->cols - right_small->cols;

    /* subtract the elements individually */
    for (row=0; row<right_small->rows; row++)
    {
        for (col=0; col<right_small->cols; col++)
        {
            MATRIX_GET_ELEMENT(left_large, row_offset + row, col_offset +
                col) -= MATRIX_GET_ELEMENT(right_small, row, col);
        }
    }
}


extern void qr_householder(const matrix *a, matrix *q, matrix *r)
{
    matrix q_copy, r_copy;
    matrix x, h, h_temp;
    unsigned int col;

#ifdef __CHECK_DIMENSIONS__
    /* check the dimensions of the result matrices */
    if ((a->rows != a->cols) || (q->rows != q->cols) ||
        (r->rows != r->cols) || (a->rows != q->rows) || (a->rows != r->rows))
    {
        error("Invalid matrix dimensions in qr_householder()!");
        return;
    }
#endif /* __CHECK_DIMENSIONS__ */

    /* initialize the matrices */
    matrix_malloc(&q_copy, q->rows, q->cols);
    matrix_malloc(&r_copy, r->rows, r->cols);
    matrix_malloc(&h, a->rows, a->cols);
    matrix_empty(&x);
    matrix_empty(&h_temp);
    matrix_identity(q);
    matrix_copy(a, r);

    /* find each of the Householder reflection matrices */
    for (col=0; col<a->cols-1; col++)
    {
        /* get the x vector */
        matrix_realloc(&x, a->cols - col, 1);
        matrix_get_col_vector(r, col, col, r->cols - col, &x);

        /* make x into u~ (it only involves changing one element, so there's
           no point in allocating memory for a brand new vector) */
        if (MATRIX_GET_ELEMENT(&x, 0, 0) >= 0)
            MATRIX_GET_ELEMENT(&x, 0, 0) += vector_col_norm(&x);
        else
            MATRIX_GET_ELEMENT(&x, 0, 0) -= vector_col_norm(&x);

        /* create h_temp (the 2uu^t part of h) */
        matrix_realloc(&h_temp, x.rows, x.rows);
        matrix_col_vector_transpose_multiplication(&x, &h_temp);
        matrix_constant_multiplication(&h_temp, (matrix_element)2 /
            vector_col_dot_col(&x, &x), &h_temp);

        /* create h (I - 2uu^t) */
        matrix_identity(&h);
        householder_corner_subtraction(&h, &h_temp);

        /* "add" h to the q and r matrices */
        matrix_copy(q, &q_copy);
        matrix_copy(r, &r_copy);
        matrix_multiplication(&q_copy, &h, q);
        matrix_multiplication(&h, &r_copy, r);
    }

    /* free memory */
    matrix_free(&q_copy);
    matrix_free(&r_copy);
    matrix_free(&h);
    matrix_free(&x);
    matrix_free(&h_temp);
}


}

template<class _T, int _SIZE>
bool QRDecomposition::decompose(const Matrix<_T, _SIZE, _SIZE> &m, Matrix<_T, _SIZE, _SIZE> *q, Matrix<_T, _SIZE, _SIZE> *r) 
{

	matrix _a;
	matrix_malloc(&_a, _SIZE, _SIZE);
	matrix _q;
	matrix_malloc(&_q, _SIZE, _SIZE);
	matrix _r;
	matrix_malloc(&_r, _SIZE, _SIZE);

	for (int j = 0; j < _SIZE; ++j)
	{
		for (int i = 0; i < _SIZE; ++i)
		{
			MATRIX_GET_ELEMENT(&_a, j, i) = m[j][i];
		}
	}
	qr_householder(&_a, &_q, &_r);

	for (int j = 0; j < _SIZE; ++j)
	{
		for (int i = 0; i < _SIZE; ++i)
		{
//			m[j][i] = MATRIX_GET_ELEMENT(&_a, j, i);
			(*q)[j][i] = MATRIX_GET_ELEMENT(&_q, j, i);
			(*r)[j][i] = MATRIX_GET_ELEMENT(&_r, j, i);
		}
	}

	matrix_free(&_r);
	matrix_free(&_q);
	matrix_free(&_a);
	return true;
}




} // namespace seed


#endif // __GEOMETRY_QRDECOMPOSITION_INLINE__
