
#ifndef ROTATION3D_MATRIX_H
#define ROTATION3D_MATRIX_H

#include <ios>
#include "Vector.h"

template <typename T, unsigned int dimension>
class Matrix {
protected:
    T matrix[dimension][dimension];
    double degreeToRadians(double degree);
public:
    Matrix();

    template<typename T1, unsigned int dimension1>
    friend bool operator==(const Matrix<T1, dimension1> &matrix1, const Matrix<T1, dimension1> &matrix2);

    template<typename T1, unsigned int dimension1>
    friend Vector<T1,dimension1> operator*(const Matrix<T1, dimension1> &matrix, Vector<T1, dimension1> &vec);

    template<typename T1, unsigned int dimension1>
    friend Matrix<T1,dimension1> operator*(const Matrix<T1, dimension1> &matrix1, const Matrix<T1, dimension1> &matrix2);

    T &operator()(unsigned int row, unsigned int column);
    const T &operator()(unsigned int row, unsigned int column) const;

    void matrixDisplay();
    template<typename T1, unsigned int dimension1>
    friend std::ostream & operator<<(std::ostream & ost, Matrix<T1, dimension1> &matrix);

    friend class Matrix3x3;
    friend class Matrix4x4;
};


template <typename T, unsigned int dimension>
Matrix<T, dimension>::Matrix() {
    this->matrix[0][0] = 1;
    this->matrix[0][1] = 0;
    if(dimension > 2) this->matrix[0][2] = 0;
    this->matrix[1][0] = 0;
    this->matrix[1][1] = 1;
    if(dimension > 2) this->matrix[1][2] = 0;
    if(dimension > 2) this->matrix[2][0] = 0;
    if(dimension > 2) this->matrix[2][1] = 0;
    if(dimension > 2) this->matrix[2][2] = 1;
}


template <typename T, unsigned int dimension>
double Matrix<T, dimension>::degreeToRadians(double degree){
    return degree * M_PI / 180;
}

template <typename T, unsigned int dimension>
bool operator==(const Matrix<T, dimension> &matrix1, const Matrix<T, dimension> &matrix2){
    int i = 0;
    int j = 0;
    while(i < dimension){
        while(j < dimension){
            if(std::abs(matrix1.matrix[i][j] - matrix2.matrix[i][j]) > MIN_THRESHOLD){
                return false;
            }
            j++;
        }
        i++;
    }
    return true;
}

template <typename T, unsigned int dimension>
Vector<T,dimension> operator*(const Matrix<T, dimension> &matrix, Vector<T, dimension> &vec){
    Vector<T, dimension> result = Vector<T,dimension>();
    if(dimension > 2){
        result[0] = (vec[0] * matrix.matrix[0][0] + vec[1] * matrix.matrix[0][1] + vec[2] * matrix.matrix[0][2]);
        result[1] = (vec[0] * matrix.matrix[1][0] + vec[1] * matrix.matrix[1][1] + vec[2] * matrix.matrix[1][2]);
        result[2] = (vec[0] * matrix.matrix[2][0] + vec[1] * matrix.matrix[2][1] + vec[2] * matrix.matrix[2][2]);
    }else{
        result[0] = (vec[0] * matrix.matrix[0][0] + vec[1] * matrix.matrix[0][1]);
        result[1] = (vec[0] * matrix.matrix[1][0] + vec[1] * matrix.matrix[1][1]);
    }

    return result;
}

template <typename T, unsigned int dimension>
T &Matrix<T,dimension>::operator()(unsigned int row, unsigned int column) {
    if(row >= dimension || row < 0 || column >= dimension || column < 0){
        throw std::invalid_argument("index out of range");
    }
    return matrix[row][column];
}

template <typename T, unsigned int dimension>
const T &Matrix<T, dimension>::operator()(unsigned int row, unsigned int column) const {
    if(row >= dimension || row < 0 || column >= dimension || column < 0){
        throw std::invalid_argument("index out of range");
    }
    return matrix[row][column];
}

template<typename T, unsigned int dimension>
Matrix<T, dimension> operator*(const Matrix<T, dimension> &matrix1, const Matrix<T, dimension> &matrix2) {
    Matrix<T,3> result = Matrix<T,3>();
    for(unsigned int i = 0; i < dimension; i++){
        for(unsigned int j = 0; j < dimension; j++){
            result(i,j) = 0;
            for(unsigned int k = 0; k < dimension; k++){
                result(i,j) += matrix1(i,k) * matrix2(k,j);
            }
        }
    }
    return result;
}

template<typename T, unsigned int dimension>
void Matrix<T, dimension>::matrixDisplay() {
    std::cout << std::fixed;
    std::cout << std::setprecision(10);
    for (int i = 0; i < dimension; ++i) {
        for (int j = 0; j < dimension; ++j) {
            std::cout << this->matrix[i][j] << " ";
        }
        std::cout << std::endl;
    }
}

template<typename T, unsigned int dimension>
std::ostream &operator<<(std::ostream &ost, Matrix<T, dimension> &matrix1) {
    std::cout << std::fixed;
    std::cout << std::setprecision(10);
    for (unsigned int i = 0; i < dimension; ++i) {
        for (unsigned int j = 0; j < dimension; ++j) {
            std::cout << matrix1.matrix[i][j] << " ";
        }
        std::cout << std::endl;
    }
    return ost;
}


#endif //ROTATION3D_MATRIX_H