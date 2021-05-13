//
// Created by artur on 5/13/21.
//


#ifndef DRONE_SCENE_GEOMETRICALBLOCK_H
#define DRONE_SCENE_GEOMETRICALBLOCK_H
#include "Matrix3x3.h"
class geometricalBloc{
protected:
    std::string fileNameOfModel;
    std::string fileNameOfBlock;
public:
    geometricalBloc();
    geometricalBloc(std::string fileNameOfModel, std::string fileNameOfBlock);
    std::string getFileNameOfModel();
    std::string getFileNameOfBlock();
};
#endif //DRONE_SCENE_GEOMETRICALBLOCK_H
