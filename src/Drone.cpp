//
// Created by artur on 5/10/21.
//
#include "Drone.h"

Drone::Drone() {
    double xMax = 3, xMin = -3, yMax = 3, yMin = -3, zMax = 1, zMin = -1;

    vector3D Ver0 = vector3D(xMin,yMin,zMin);
    vector3D Ver1 = vector3D(xMax,yMin,zMin);
    vector3D Ver2 = vector3D(xMax,yMin,zMax);
    vector3D Ver3 = vector3D(xMin,yMin,zMax);

    vector3D Ver4 = vector3D(xMin,yMax,zMin);
    vector3D Ver5 = vector3D(xMax,yMax,zMin);
    vector3D Ver6 = vector3D(xMax,yMax,zMax);
    vector3D Ver7 = vector3D(xMin,yMax,zMax);

    vector3D vertices[VERTICES_NUMBER_OF_CUBOID] = {Ver0, Ver1, Ver2, Ver3, Ver4, Ver5, Ver6, Ver7};
    this->deck = Cuboid(vertices);

    for(int i = 0; i < NUMBER_OF_ROTORS; ++i){
        switch (i) {
            case 0:
                xMax = -2; xMin = -4; yMax = 4; yMin = 2; zMax = 2; zMin = 1.2;
                break;
            case 1:
                xMax = 4; xMin = 2; yMax = 4; yMin = 2; zMax = 2; zMin = 1.2;
                break;
            case 2:
                xMax = 4; xMin = 2; yMax = -2; yMin = -4; zMax = 2; zMin = 1.2;
                break;
            case 3:
                xMax = -2; xMin = -4; yMax = -2; yMin = -4; zMax = 2; zMin = 1.2;
                break;
        }
        Ver0 = vector3D(xMin,yMin,zMin);
        Ver1 = vector3D(xMax,yMin,zMin);
        Ver2 = vector3D(xMax,yMin,zMax);
        Ver3 = vector3D(xMin,yMin,zMax);
        Ver4 = vector3D(xMin,yMax,zMin);
        Ver5 = vector3D(xMax,yMax,zMin);
        Ver6 = vector3D(xMax,yMax,zMax);
        Ver7 = vector3D(xMin,yMax,zMax);

        vertices[0] = Ver0; vertices[1] = Ver1; vertices[2] = Ver2; vertices[3] = Ver3,
        vertices[4] = Ver4; vertices[5] = Ver5; vertices[6] = Ver6; vertices[7] = Ver7;
        this->rotors[i] = Cuboid(vertices);
    }
}

Drone::Drone(vector3D translation) {
    *this = Drone();
    this->deck.translationByVector(translation);
    for(int i = 0; i < NUMBER_OF_ROTORS; ++i){
        this->rotors[i].translationByVector(translation);
    }
}

void Drone::unitRotationOfRotors(){
    Matrix3x3 left = Matrix3x3(2,'z');
    Matrix3x3 right = Matrix3x3(-2,'z');

    for(int i = 0; i < NUMBER_OF_ROTORS; ++i){
        if(i % 2 == 0){
            this->rotors[i].rotationByMatrix(left);
        }else{
            this->rotors[i].rotationByMatrix(right);
        }
    }
}

const Cuboid &Drone::operator[](int index) const {
    switch (index) {
        case 0:
            return this->rotors[0];
        case 1:
            return this->rotors[1];;
        case 2:
            return this->rotors[2];
        case 3:
            return this->rotors[3];
        case 4:
            return this->deck;
        default:
            throw std::invalid_argument("index out of range");
    }
}


Cuboid &Drone::operator[](int index) {
    switch (index) {
        case 0:
            return this->rotors[0];
        case 1:
            return this->rotors[1];;
        case 2:
            return this->rotors[2];
        case 3:
            return this->rotors[3];
        case 4:
            return this->deck;
        default:
            throw std::invalid_argument("index out of range");
    }
}