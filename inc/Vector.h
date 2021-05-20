//
// Created by artur on 3/18/21.
//
#ifndef ROTATION3D_VECTOR_H
#define ROTATION3D_VECTOR_H
#include "Constants.h"
#include <iostream>
#include <iomanip>
#include <cmath>

template <typename T, unsigned int dimension>
class Vector {

protected:
    T vector[dimension];
public:

    Vector();

    Vector(T _x, T _y);

    Vector(T _x, T _y, T _z);

    template<typename T1, unsigned int dimension1>
    friend bool operator==(const Vector<T1, dimension1> &Vec1, const Vector<T1, dimension1> &Vec2);

    template<typename T1, unsigned int dimension1>
    friend Vector<T1, dimension1> operator+(Vector<T1, dimension1> &Vec1, Vector<T1, dimension1> &Vec2);

    template<typename T1, unsigned int dimension1>
    friend Vector<T1, dimension1> operator-(Vector<T1, dimension1> &Vec1, Vector<T1, dimension1> &Vec2);

    template<typename T1, unsigned int dimension1>
    friend Vector<T1, dimension1> operator/(Vector<T1, dimension1> &Vec, const double &Num);

    template<typename T1, unsigned int dimension1>
    friend Vector<T1, dimension1> operator*(Vector<T1, dimension1> &Vec, const double &Num);

    const T &operator[](int index) const;

    T &operator[](int index);

    T getLength();

    template<typename T1, unsigned int dimension1>
    friend std::ostream &operator<<(std::ostream &ost, const Vector<T1, dimension1> &Vec);

    template<typename T1, unsigned int dimension1>
    friend std::istream &operator>>(std::istream &ist, Vector<T, dimension> &Vec);

    void setX(T _x);

    void setY(T _y);

    void setZ(T _z);
    friend class vector3D;

};


    template<typename T, unsigned int dimension>
    Vector<T, dimension>::Vector() {
        unsigned int i = 0;
        while (i < dimension) {
            this->vector[i] = 0;
            i++;
        }
    }

    template<typename T, unsigned int dimension>
    Vector<T, dimension>::Vector(T _x, T _y) {
        if (dimension != 2) throw std::invalid_argument("dimension is not equal 2");
        this->vector[0] = _x;
        this->vector[1] = _y;
        int i = 2;
        while (i < dimension) {
            this->vector[i] = 0;
            i++;
        }
    }

    template<typename T, unsigned int dimension>
    Vector<T, dimension>::Vector(T _x, T _y, T _z) {
        if (dimension < 2) throw std::invalid_argument("to short vector");
        this->vector[0] = _x;
        this->vector[1] = _y;
        unsigned int i = 2;
        if (dimension >= 3) {
            this->vector[2] = _z;
            i = 3;
        }
        while (i < dimension) {
            this->vector[i] = 0;
            i++;
        }
    }

    template<typename T, unsigned int dimension>
    void Vector<T, dimension>::setX(T _x) {
        if (dimension >= 1) this->vector[0] = _x;
    }

    template<typename T, unsigned int dimension>
    void Vector<T, dimension>::setY(T _y) {
        if (dimension >= 2) this->vector[1] = _y;
    }

    template<typename T, unsigned int dimension>
    void Vector<T, dimension>::setZ(T _z) {
        if (dimension >= 3) this->vector[2] = _z;
    }

    template<typename T, unsigned int dimension>
    bool operator==(const Vector<T, dimension> &Vec1, const Vector<T, dimension> &Vec2) {
        if (dimension > 2) {
            if ((std::abs(Vec1[0] - Vec2[0]) < MIN_THRESHOLD) &&
                (std::abs(Vec1[1] - Vec2[1]) < MIN_THRESHOLD) &&
                (std::abs(Vec1[2] - Vec2[2]) < MIN_THRESHOLD)) {
                return true;
            } else {
                return false;
            }
        } else if (dimension > 1) {
            if ((std::abs(Vec1[0] - Vec2[0]) < MIN_THRESHOLD) &&
                (std::abs(Vec1[1] - Vec2[1]) < MIN_THRESHOLD)) {
                return true;
            } else {
                return false;
            }
        } else {
            throw std::invalid_argument("vector is to short");
        }
    }

    template<typename T, unsigned int dimension>
    const T &Vector<T, dimension>::operator[](int index) const {
        switch (index) {
            case 0:
                return this->vector[0];
                break;
            case 1:
                if (dimension > 1) return this->vector[1];
                throw std::invalid_argument("out of range");
            case 2:
                if (dimension > 2) return this->vector[2];
                throw std::invalid_argument("out of range");
            default:
                throw std::invalid_argument("index out of range");

        }
    }

    template<typename T, unsigned int dimension>
    T &Vector<T, dimension>::operator[](int index) {
        switch (index) {
            case 0:
                return this->vector[0];
            case 1:
                if (dimension > 1) return this->vector[1];
                break;
            case 2:
                if (dimension > 2) return this->vector[2];
                break;
            default:
                throw std::invalid_argument("index out of range");
                break;
        }
    }

    template<typename T, unsigned int dimension>
    Vector<T, dimension> operator+(Vector<T, dimension> &Vec1, Vector<T, dimension> &Vec2) {
        Vector<T, dimension> result;
        result[0] = (Vec1[0] + Vec2[0]);
        if (dimension > 1) result[1] = (Vec1[1] + Vec2[1]);
        if (dimension > 2) result[2] = (Vec1[2] + Vec2[2]);
        return result;
    }

    template<typename T, unsigned int dimension>
    Vector<T, dimension> operator-(Vector<T, dimension> &Vec1, Vector<T, dimension> &Vec2) {
        Vector<T, dimension> result;
        result[0] = (Vec1[0] - Vec2[0]);
        if (dimension > 1) result[1] = (Vec1[1] - Vec2[1]);
        if (dimension > 2) result[2] = (Vec1[2] - Vec2[2]);
        return result;
    }

    template<typename T, unsigned int dimension>
    Vector<T, dimension> operator*(Vector<T, dimension> &Vec, const double &Num) {
        Vector<T, dimension> result;
        result[0] = (Vec[0] * Num);
        if (dimension > 1) result[1] = (Vec[1] * Num);
        if (dimension > 2) result[2] = (Vec[2] * Num);
        return result;
    }

    template<typename T, unsigned int dimension>
    Vector<T, dimension> operator/(Vector<T, dimension> &Vec, const double &Num) {
        if (Num == 0) {
            throw std::invalid_argument("division by zero");
        }
        Vector<T, dimension> result;
        result[0] = (Vec[0] / Num);
        if (dimension > 1) result[1] = (Vec[1] / Num);
        if (dimension > 2) result[2] = (Vec[2] / Num);
        return result;
    }

    template<typename T, unsigned int dimension>
    T Vector<T, dimension>::getLength() {
        if (dimension < 3) {
            double length = sqrt((this->vector[0]) * (this->vector[0]) + (this->vector[1]) * (this->vector[1]));
            return length;
        }
        double length = sqrt((this->vector[0]) * (this->vector[0]) + (this->vector[1]) * (this->vector[1])
                             + (this->vector[2] * this->vector[2]));
        return length;
    }

    template<typename T, unsigned int dimension>
    std::istream &operator>>(std::istream &ist, Vector<T, dimension> &Vec) {
        T x, y, z;
        ist >> x;
        Vec[0] = x;
        if (dimension < 2) return ist;
        ist >> y;
        Vec[1] = y;
        if (dimension < 3) return ist;
        ist >> z;
        Vec[2] = z;
        return ist;
    }

    template<typename T, unsigned int dimension>
    std::ostream &operator<<(std::ostream &ost, const Vector<T, dimension> &Vec) {
        std::cout << std::fixed;
        std::cout << std::setprecision(VECTOR_PRECISION);
        ost << Vec.vector[0] << " ";
        ost << Vec.vector[1] << " ";
        ost << Vec.vector[2] << std::endl;
        return ost;
    }


#endif //ROTATION3D_VECTOR_H
