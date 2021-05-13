//
// Created by artur on 3/17/21.
//



#ifndef ROTATION3D_CUBOID_H
#define ROTATION3D_CUBOID_H
#include <iostream>
#include <utility>
#include <cmath>
#include <float.h>
#include "Matrix3x3.h"
#include "GeometricalBlock.h"
#include "Constants.h"
#include "Vector3D.h"

class Cuboid: public geometricalBloc{
protected:
    vector3D vertices[VERTICES_NUMBER_OF_CUBOID];
    double sidesLength[SIDES_NUMBER_OF_CUBOID];
    vector3D centerOfMass;
    /*! Simple sort algorithm looks the further and the closer vertices, and
     * return center of mass vector */
    vector3D calculateCenterOfMass();
public:
    Cuboid();
    Cuboid(vector3D *ver);
    /* Set all parameters strictly */

    friend bool operator==(const Cuboid &cub1, const Cuboid &cub2);
    void translationByVector(vector3D &Vec);
    void rotationByMatrix(const Matrix3x3 &rotMatrix);

    const vector3D & operator[](int index) const;
    vector3D & operator[](int index);

    friend std::ostream & operator<<(std::ostream & ost, Cuboid &cub);
    double getSideLength(unsigned int index);
    void calculateSidesLength();
    vector3D getCenterOfMass();
};

#endif //ROTATION3D_CUBOID_H
