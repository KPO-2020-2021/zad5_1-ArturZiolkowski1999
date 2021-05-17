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

vector3D GeometricalBloc::getPosition() {
    return this->positionOfCenterOfMass;
}

Matrix3x3 GeometricalBloc::getOrientation() {
    return this->orientation;
}

GeometricalBloc &GeometricalBloc::operator+=(vector3D vec) {
    this->positionOfCenterOfMass = this->positionOfCenterOfMass + vec;
    return *this;
}

GeometricalBloc &GeometricalBloc::operator*=(Matrix3x3 rotMat) {
    this->orientation = rotMat * this->orientation;
    return *this;
}

GeometricalBloc &GeometricalBloc::operator-=(vector3D vec) {
    this->positionOfCenterOfMass = this->positionOfCenterOfMass - vec;
    return *this;
}

void GeometricalBloc::setOrientation(Matrix3x3 orient) {
    this->orientation =orient;
}

void GeometricalBloc::setPosition(vector3D pos) {
    this->positionOfCenterOfMass = pos;
}
