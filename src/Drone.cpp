//
// Created by artur on 5/10/21.
//
#include "Drone.h"

Drone::Drone() {
    double xMax = 3, xMin = -3, yMax = 3, yMin = -3, zMax = 1, zMin = -1;

    Vector<double, 3> Ver0 = Vector<double, 3>(xMin,yMin,zMin);
    Vector<double, 3> Ver1 = Vector<double, 3>(xMax,yMin,zMin);
    Vector<double, 3> Ver2 = Vector<double, 3>(xMax,yMin,zMax);
    Vector<double, 3> Ver3 = Vector<double, 3>(xMin,yMin,zMax);

    Vector<double, 3> Ver4 = Vector<double, 3>(xMin,yMax,zMin);
    Vector<double, 3> Ver5 = Vector<double, 3>(xMax,yMax,zMin);
    Vector<double, 3> Ver6 = Vector<double, 3>(xMax,yMax,zMax);
    Vector<double, 3> Ver7 = Vector<double, 3>(xMin,yMax,zMax);

    Vector<double, 3> vertices[VERTICES_NUMBER] = {Ver0, Ver1, Ver2, Ver3, Ver4, Ver5, Ver6, Ver7};
    this->deck = Cuboid<double>(vertices);

    for(int i = 0; i < NUMBER_OF_ROTORS; ++i){
        switch (i) {
            case 0:
                xMax = -1; xMin = -5; yMax = 5; yMin = 1; zMax = 2; zMin = 1.2;
                break;
            case 1:
                xMax = 5; xMin = 1; yMax = 5; yMin = 1; zMax = 2; zMin = 1.2;
                break;
            case 2:
                xMax = 5; xMin = 1; yMax = -1; yMin = -5; zMax = 2; zMin = 1.2;
                break;
            case 3:
                xMax = -1; xMin = -5; yMax = -1; yMin = -5; zMax = 2; zMin = 1.2;
                break;
        }
        Ver0 = Vector<double, 3>(xMin,yMin,zMin);
        Ver1 = Vector<double, 3>(xMax,yMin,zMin);
        Ver2 = Vector<double, 3>(xMax,yMin,zMax);
        Ver3 = Vector<double, 3>(xMin,yMin,zMax);
        Ver4 = Vector<double, 3>(xMin,yMax,zMin);
        Ver5 = Vector<double, 3>(xMax,yMax,zMin);
        Ver6 = Vector<double, 3>(xMax,yMax,zMax);
        Ver7 = Vector<double, 3>(xMin,yMax,zMax);

        vertices[0] = Ver0; vertices[1] = Ver1; vertices[2] = Ver2; vertices[3] = Ver3,
        vertices[4] = Ver4; vertices[5] = Ver5; vertices[6] = Ver6; vertices[7] = Ver7;
        this->rotors[i] = Cuboid<double>(vertices);
    }
}

Drone::Drone(Vector<double, 3> translation) {
    *this = Drone();
    this->deck.translationByVector(translation);
    for(int i = 0; i < NUMBER_OF_ROTORS; ++i){
        this->rotors[i].translationByVector(translation);
    }
}

void Drone::unitRotationOfRotors(){
    Matrix3x3 left =Matrix3x3(2,'z');
    Matrix3x3 right =Matrix3x3(-2,'z');

    for(int i = 0; i < NUMBER_OF_ROTORS; ++i){
        if(i % 2 == 0){
            this->rotors[i].rotationByMatrix(left);
        }else{
            this->rotors[i].rotationByMatrix(right);
        }
    }
}

const Cuboid<double> &Drone::operator[](int index) const {
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


Cuboid<double> &Drone::operator[](int index) {
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