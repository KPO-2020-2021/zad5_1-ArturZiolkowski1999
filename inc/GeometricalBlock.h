//
// Created by artur on 5/13/21.
//


#ifndef DRONE_SCENE_GEOMETRICALBLOCK_H
#define DRONE_SCENE_GEOMETRICALBLOCK_H
#include "Matrix3x3.h"
#include "Vector3D.h"
#include "Constants.h"

class GeometricalBloc{
protected:
    std::string fileNameOfModel;
    std::string fileNameOfBlock;
    Matrix3x3 orientation;
    vector3D positionOfCenterOfMass;
public:
    GeometricalBloc();
    GeometricalBloc(std::string fileNameOfModel, std::string fileNameOfBlock);
    std::string getFileNameOfModel();
    std::string getFileNameOfBlock();
};
#endif //DRONE_SCENE_GEOMETRICALBLOCK_H
