//
// Created by artur on 5/13/21.
//
#include "GeometricalBlock.h"

geometricalBloc::geometricalBloc() {
    this -> fileNameOfBlock = "../data/filenameOfBlock";
    this -> fileNameOfModel = "../data/filenameOfModel";
}

geometricalBloc::geometricalBloc(std::string fileNameOfModel, std::string fileNameOfBlock){
    this -> fileNameOfModel = fileNameOfModel;
    this -> fileNameOfBlock = fileNameOfBlock;
}

std::string geometricalBloc::getFileNameOfModel() {
    return this->fileNameOfModel;
}

std::string geometricalBloc::getFileNameOfBlock() {
    return this->fileNameOfBlock;
}