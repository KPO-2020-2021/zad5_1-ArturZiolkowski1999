//
// Created by artur on 5/13/21.
//

#ifndef DRONE_SCENE_HEXAGONALPRISM_H
#define DRONE_SCENE_HEXAGONALPRISM_H

#include <fstream>
#include "GeometricalBlock.h"
#include "sstream"

class HexagonalPrism
        : public GeometricalBloc{
protected:
    vector3D vertices[VERTICES_NUMBER_OF_HEXAGONAL_PRISM];
public:
    HexagonalPrism();
    HexagonalPrism(std::string fileNameOfModel, std::string fileNameOfBlock = "../data/hexagonalPrismBlock.txt",
                   Matrix3x3 initialOrientation = Matrix3x3(), vector3D initialPosition = vector3D());
    friend std::ostream & operator<<(std::ostream & ost, HexagonalPrism &hex);
    void readModelVerticesPosition();
    const vector3D & operator[](int index) const;
    vector3D & operator[](int index);
};
#endif //DRONE_SCENE_HEXAGONALPRISM_H
