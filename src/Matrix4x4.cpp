//
// Created by artur on 5/6/21.
//
#include "../inc/Matrix4x4.h"


Matrix4x4::Matrix4x4(double jaw, double pitch, double roll, Vector<double, 3> axis) {
//jaw pitch and roll are in degrees
    // fill 4x4 matrix
    jaw = degreeToRadians(jaw);
    pitch = degreeToRadians(pitch);
    roll = degreeToRadians(roll);


    this->matrix[0][0] = cos(jaw) * cos(pitch);
    this->matrix[0][1] = cos(jaw)*sin(pitch)*sin(roll) - sin(jaw) * cos(roll);
    this->matrix[0][2] = cos(jaw)*sin(pitch)*cos(roll) + sin(jaw) * sin(roll);
    this->matrix[0][3] = axis[0];

    this->matrix[1][0] = sin(jaw) * cos(pitch);
    this->matrix[1][1] = sin(jaw) * sin(pitch) * sin(roll) + cos(jaw) * cos(roll);
    this->matrix[1][2] = sin(jaw) * sin(pitch) * cos(roll) - cos(jaw) * sin(roll);
    this->matrix[1][3] = axis[1];

    this->matrix[2][0] = -sin(pitch);
    this->matrix[2][1] = cos(pitch) * sin(roll);
    this->matrix[2][2] = cos(pitch) * cos(roll);
    this->matrix[2][3] = axis[2];


    this->matrix[3][0] = 0;
    this->matrix[3][1] = 0;
    this->matrix[3][2] = 0;
    this->matrix[3][3] = 1;
}

Matrix4x4::Matrix4x4() {
    this->matrix[0][0] = 1;
    this->matrix[0][1] = 0;
    this->matrix[0][2] = 0;
    this->matrix[0][3] = 0;

    this->matrix[1][0] = 0;
    this->matrix[1][1] = 1;
    this->matrix[1][2] = 0;
    this->matrix[1][3] = 0;

    this->matrix[2][0] = 0;
    this->matrix[2][1] = 0;
    this->matrix[2][2] = 1;
    this->matrix[2][3] = 0;

    this->matrix[3][0] = 0;
    this->matrix[3][1] = 0;
    this->matrix[3][2] = 0;
    this->matrix[3][3] = 1;
}

Matrix4x4 &Matrix4x4::operator=(const Matrix4x4 matrix4x4) {
    for(int i = 0; i < 4; i++){
        for(int j = 0; j < 4; j++){
            this->matrix[i][j] = matrix4x4.matrix[i][j];
        }
    }
    return *this;
}

Matrix4x4 &Matrix4x4::operator=(const Matrix<double, 4> matrix4x4) {
    for(int i = 0; i < 4; i++){
        for(int j = 0; j < 4; j++){
            this->matrix[i][j] = matrix4x4.matrix[i][j];
        }
    }
    return *this;
}

