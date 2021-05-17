//
// Created by artur on 3/17/21.
//

#ifndef ROTATION3D_CUBOID_H
#define ROTATION3D_CUBOID_H
#include <iostream>
#include <utility>
#include <cmath>
#include <float.h>
#include <fstream>
#include "GeometricalBlock.h"
#include "sstream"

class Cuboid: public GeometricalBloc{
protected:
    vector3D vertices[VERTICES_NUMBER_OF_CUBOID];
    double sidesLength[SIDES_NUMBER_OF_CUBOID];

public:
    Cuboid();
    Cuboid(std::string fileNameOfModel, std::string fileNameOfBlock = "../data/CuboidBlock.txt",
           Matrix3x3 initialOrientation = Matrix3x3(), vector3D initialPosition = vector3D());
    /* Set all parameters strictly */
    void readModelVerticesPosition();
    void calculateActualPosition();

    friend bool operator==(const Cuboid &cub1, const Cuboid &cub2);
    void translationByVector(vector3D &Vec);
    void rotationByMatrix(const Matrix3x3 &rotMatrix);

    const vector3D & operator[](int index) const;
    vector3D & operator[](int index);

    friend std::ostream & operator<<(std::ostream & ost, Cuboid &cub);

    double getSideLength(unsigned int index);
    void calculateSidesLength();
};

#endif //ROTATION3D_CUBOID_H
