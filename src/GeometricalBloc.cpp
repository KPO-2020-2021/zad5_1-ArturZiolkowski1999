//
// Created by artur on 5/13/21.
//
#include "GeometricalBlock.h"

GeometricalBloc::GeometricalBloc() {
    this -> fileNameOfBlock = "../data/filenameOfBlock";
    this -> fileNameOfModel = "../data/filenameOfModel";
    this -> orientation = Matrix3x3();
    this ->positionOfCenterOfMass = vector3D();
}

GeometricalBloc::GeometricalBloc(std::string fileNameOfModel, std::string fileNameOfBlock){
    this -> fileNameOfModel = fileNameOfModel;
    this -> fileNameOfBlock = fileNameOfBlock;
    this -> orientation = Matrix3x3();
    this ->positionOfCenterOfMass = vector3D();
}

std::string GeometricalBloc::getFileNameOfModel() {
    return this->fileNameOfModel;
}

std::string GeometricalBloc::getFileNameOfBlock() {
    return this->fileNameOfBlock;
}