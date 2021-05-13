//
// Created by artur on 5/13/21.
//
#include "Vector3D.h"

vector3D::vector3D() {
    this->vector[0] = 0;
    this->vector[1] = 0;
    this->vector[2] = 0;
}

vector3D::vector3D(double x, double y, double z) {
    this->vector[0] = x;
    this->vector[1] = y;
    this->vector[2] = z;
}

vector3D &vector3D::operator=(const vector3D vec) {
    this->vector[0] = vec[0];
    this->vector[1] = vec[1];
    this->vector[2] = vec[2];
    return *this;
}

vector3D &vector3D::operator=(const Vector<double, 3> vec) {
    this->vector[0] = vec[0];
    this->vector[1] = vec[1];
    this->vector[2] = vec[2];
    return *this;
}

