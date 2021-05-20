//
// Created by artur on 5/13/21.
//
#include "Vector3D.h"

int vector3D::Actual=0;
int vector3D::Total=0;

vector3D::vector3D() {
    this->vector[0] = 0;
    this->vector[1] = 0;
    this->vector[2] = 0;

    Actual++;
    Total++;
}

vector3D::vector3D(double x, double y, double z) {
    this->vector[0] = x;
    this->vector[1] = y;
    this->vector[2] = z;

    Actual++;
    Total++;
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

vector3D::vector3D(const vector3D &v) {
    Actual++;
    Total++;
    for(int i = 0; i < VECTOR_SIZE; ++i){
        vector[i] = v.vector[i];
    }
}

vector3D::~vector3D() {
    --Actual;
}

int vector3D::getActual() {
    return Actual;
}

int vector3D::getTotal() {
    return Total;
}
