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
public:
    Cuboid();
    Cuboid(std::string fileNameOfModel, std::string fileNameOfBlock = "../data/CuboidBlock.txt",
           Matrix3x3 initialOrientation = Matrix3x3(), vector3D initialPosition = vector3D());
    /*! read position from model file */
    void readModelVerticesPosition();
    /*! calculate actual position, using model position in model file, and saved position and orientation */
    void calculateActualPosition();
    friend bool operator==(const Cuboid &cub1, const Cuboid &cub2);
    /*! Translate all vertices by vector, but doesnt touch center vector of cuboid and orientation*/
    void translationByVector(vector3D &Vec);
    /*! Rotate all vertices by matrix, but doesnt touch center vector of cuboid and orientation*/
    void rotationByMatrix(const Matrix3x3 &rotMatrix);
    const vector3D & operator[](int index) const;
    vector3D & operator[](int index);
    /*! write readable  for gnuplot positions that are interpreted as non empty cuboid*/
    friend std::ostream & operator<<(std::ostream & ost, Cuboid &cub);
};

#endif //ROTATION3D_CUBOID_H
