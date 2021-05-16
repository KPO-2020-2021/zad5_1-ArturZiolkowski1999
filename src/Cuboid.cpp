//
// Created by artur on 5/13/21.
//
#include "Cuboid.h"



Cuboid::Cuboid() {
    this -> fileNameOfModel = "../data/CuboidModel.txt";
    this -> fileNameOfBlock = "../data/CuboidBlock.txt";
    this -> orientation = Matrix3x3();
    this -> positionOfCenterOfMass = vector3D();
}


Cuboid::Cuboid(std::string fileNameOfModel, std::string fileNameOfBlock,
               Matrix3x3 initialOrientation, vector3D initialPosition){

    this -> fileNameOfModel = fileNameOfModel;
    this -> fileNameOfBlock = fileNameOfBlock;
    this -> orientation = initialOrientation;
    this ->positionOfCenterOfMass = initialPosition;
}

void Cuboid::readModelVerticesPosition() {
// VERTICES_NUMBER have to be equal 8; there is no sort of vertices
//  Front  | Back <- vertices number
//  3   2  | 7   6
//  0   1  | 4   5
//
    std::string tmp;
    std::stringstream ss;
    int i = 0;
    std::ifstream is;
    is.open(this->fileNameOfModel);

    while(getline(is, tmp)){
        ss << tmp;
        ss >> this->vertices[i];
        i++;
        ss = std::stringstream();
    }
    is.close();
}

bool operator==(const Cuboid &cub1, const Cuboid &cub2){
    if(
            cub1.vertices[0] == cub2.vertices[0] &&
            cub1.vertices[1] == cub2.vertices[1] &&
            cub1.vertices[2] == cub2.vertices[2] &&
            cub1.vertices[3] == cub2.vertices[3] &&
            cub1.vertices[4] == cub2.vertices[4] &&
            cub1.vertices[5] == cub2.vertices[5] &&
            cub1.vertices[6] == cub2.vertices[6] &&
            cub1.vertices[7] == cub2.vertices[7] ){
        return true;
    }
    return false;
}


void Cuboid::translationByVector(vector3D &Vec){

    for(int i = 0; i < VERTICES_NUMBER_OF_CUBOID; ++i){
        this->vertices[i] = Vec + (this->vertices[i]);
    }
}


void Cuboid::rotationByMatrix(const Matrix3x3 &rotMatrix){

    for(int i = 0; i < VERTICES_NUMBER_OF_CUBOID; ++i){
        this->vertices[i] = rotMatrix * (this->vertices[i]);
    }
}


const vector3D &Cuboid::operator[](int index) const {
    switch (index) {
        case 0:
            return this->vertices[0];
        case 1:
            return this->vertices[1];
        case 2:
            return this->vertices[2];
        case 3:
            return this->vertices[3];
        case 4:
            return this->vertices[4];
        case 5:
            return this->vertices[5];
        case 6:
            return this->vertices[6];
        case 7:
            return this->vertices[7];
        default:
            throw std::invalid_argument("index out of range");
    }
}


vector3D &Cuboid::operator[](int index) {
    switch (index) {
        case 0:
            return this->vertices[0];
        case 1:
            return this->vertices[1];
        case 2:
            return this->vertices[2];
        case 3:
            return this->vertices[3];
        case 4:
            return this->vertices[4];
        case 5:
            return this->vertices[5];
        case 6:
            return this->vertices[6];
        case 7:
            return this->vertices[7];
        default:
            throw std::invalid_argument("index out of range");
    }
}


void Cuboid::calculateSidesLength(){

    //sides 0 - 3 one group , 4-7 second group 8-11 last group
    vector3D side = vector3D();
    side = this->vertices[0] - this->vertices[1];
    this->sidesLength[0] = side.getLength();
    side = this->vertices[2] - this->vertices[3];
    this->sidesLength[1] = side.getLength();
    side = this->vertices[4] - this->vertices[5];
    this->sidesLength[2] = side.getLength();
    side = this->vertices[6] - this->vertices[7];
    this->sidesLength[3] = side.getLength();


    side = this->vertices[0] - this->vertices[3];
    this->sidesLength[4] = side.getLength();
    side = this->vertices[1] - this->vertices[2];
    this->sidesLength[5] = side.getLength();
    side = this->vertices[4] - this->vertices[7];
    this->sidesLength[6] = side.getLength();
    side = this->vertices[5] - this->vertices[6];
    this->sidesLength[7] = side.getLength();


    side = this->vertices[0] - this->vertices[4];
    this->sidesLength[8] = side.getLength();
    side = this->vertices[1] - this->vertices[5];
    this->sidesLength[9] = side.getLength();
    side = this->vertices[2] - this->vertices[6];
    this->sidesLength[10] = side.getLength();
    side = this->vertices[3] - this->vertices[7];
    this->sidesLength[11] = side.getLength();
}


std::ostream &operator<<(std::ostream &ost, Cuboid &cub) {
    ost << std::setprecision(10) << std::fixed;

    //for the non empty cuboid but it doesnt work


    vector3D up = cub[2];
    up = up - cub[0];
    up = up/2;
    up = up + cub[0];
    vector3D down = cub[6];
    down = down - cub[4];
    down = down/2;
    down = down + cub[4];


    ost << up;
    ost << cub[2];
    ost << cub[6];
    ost << down << "#\n\n";

    ost << up;
    ost << cub[1];
    ost << cub[5];
    ost << down << "#\n\n";

    ost << up;
    ost << cub[0];
    ost << cub[4];
    ost << down << "#\n\n";

    ost << up;
    ost << cub[3];
    ost << cub[7];
    ost << down << "#\n\n";

    ost << up;
    ost << cub[2];
    ost << cub[6];
    ost << down << "#\n\n";

    return ost;
}

double Cuboid::getSideLength(unsigned int index) {
    if(index > SIDES_NUMBER_OF_CUBOID) throw std::invalid_argument("index out of range");
    return this->sidesLength[index];
}


vector3D Cuboid::calculateCenterOfMass() {

    this->centerOfMass = this->vertices[6] - this->vertices[0];
    this->centerOfMass = this->centerOfMass/2;
    this->centerOfMass = this->centerOfMass + this->vertices[0];

    return this->centerOfMass;
}


vector3D Cuboid::getCenterOfMass() {
    return this->centerOfMass;
}


void Cuboid::calculateActualPosition() {
    readModelVerticesPosition();
    for(int i = 0; i < VERTICES_NUMBER_OF_CUBOID; ++i){
        this->vertices[i] = this->orientation * (this->vertices[i]);
    }

    for(int j = 0; j < VERTICES_NUMBER_OF_CUBOID; ++j){
        this->vertices[j] = this->positionOfCenterOfMass + (this->vertices[j]);
    }
}
