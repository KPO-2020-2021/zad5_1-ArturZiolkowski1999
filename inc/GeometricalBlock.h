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
    vector3D getPosition();
    Matrix3x3 getOrientation();
    void setOrientation(Matrix3x3 orient);
    void setPosition(vector3D pos);
    /*! adds vector to position */
    GeometricalBloc &operator+=(vector3D vec);
    /*! subtract vector from position */
    GeometricalBloc &operator-=(vector3D vec);
    /*! multiply matrix by orienation*/
    GeometricalBloc &operator*=(Matrix3x3 rotMat);
};



#endif //DRONE_SCENE_GEOMETRICALBLOCK_H
