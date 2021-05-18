//
// Created by artur on 5/10/21.
//
#include "Drone.h"

Drone::Drone() {
    Matrix3x3 initMat = Matrix3x3();
    vector3D initVec = vector3D(0,0,1);
    vector3D transInZ = vector3D(0,0,1);

    this->deck = Cuboid("../data/cuboidModel.txt", "../data/deck.txt", initMat, initVec);

    initVec = (this->deck)[3] + transInZ;
    this->rotors[0] = HexagonalPrism("../data/hexagonalPrismModel.txt",
                                     "../data/rotor0.txt", initMat, initVec);
    this->rotors[0].readModelVerticesPosition();

    initVec = (this->deck)[2] + transInZ;
    this->rotors[1] = HexagonalPrism("../data/hexagonalPrismModel.txt",
                                     "../data/rotor1.txt", initMat, initVec);

    initVec = (this->deck)[6] + transInZ;
    this->rotors[2] = HexagonalPrism("../data/hexagonalPrismModel.txt",
                                     "../data/rotor2.txt", initMat, initVec);

    initVec = (this->deck)[7] + transInZ;
    this->rotors[3] = HexagonalPrism("../data/hexagonalPrismModel.txt",
                                     "../data/rotor3.txt", initMat, initVec);
}

Drone::Drone(std::string fileNameOfDeck, std::string fileNameOfRotor0,
             std::string fileNameOfRotor1, std::string fileNameOfRotor2,
             std::string fileNameOfRotor3, vector3D initialTranslation, Matrix3x3 initialOrientation) {

    Matrix3x3 initMat = initialOrientation;;
    vector3D transInZ = vector3D(0,0,1);
    vector3D initVec = initialTranslation;

    this->deck = Cuboid("../data/cuboidModel.txt", fileNameOfDeck, initMat, initVec);
    this->deck.readModelVerticesPosition();

    initVec = (this->deck)[3] + transInZ;
    initVec = initVec + initialTranslation;
    this->rotors[0] = HexagonalPrism("../data/hexagonalPrismModel.txt",
                                     fileNameOfRotor0, initMat, initVec);

    initVec = (this->deck)[2] + transInZ;
    initVec = initVec + initialTranslation;
    this->rotors[1] = HexagonalPrism("../data/hexagonalPrismModel.txt",
                                     fileNameOfRotor1, initMat, initVec);

    initVec = (this->deck)[6] + transInZ;
    initVec = initVec + initialTranslation;
    this->rotors[2] = HexagonalPrism("../data/hexagonalPrismModel.txt",
                                     fileNameOfRotor2, initMat, initVec);

    initVec = (this->deck)[7] + transInZ;
    initVec = initVec + initialTranslation;
    this->rotors[3] = HexagonalPrism("../data/hexagonalPrismModel.txt",
                                     fileNameOfRotor3, initMat, initVec);

    calculatePosition();
}
//
//void Drone::unitRotationOfRotors(){
//    Matrix3x3 left = Matrix3x3(2,'z');
//    Matrix3x3 right = Matrix3x3(-2,'z');
//
//    for(int i = 0; i < NUMBER_OF_ROTORS; ++i){
//        if(i % 2 == 0){
//            this->rotors[i].rotationByMatrix(left);
//        }else{
//            this->rotors[i].rotationByMatrix(right);
//        }
//    }
//}

const HexagonalPrism &Drone::operator[](int index) const {
    switch (index) {
        case 0:
            return this->rotors[0];
        case 1:
            return this->rotors[1];;
        case 2:
            return this->rotors[2];
        case 3:
            return this->rotors[3];
        default:
            throw std::invalid_argument("index out of range");
    }
}


HexagonalPrism &Drone::operator[](int index) {
    switch (index) {
        case 0:
            return this->rotors[0];
        case 1:
            return this->rotors[1];;
        case 2:
            return this->rotors[2];
        case 3:
            return this->rotors[3];
        default:
            throw std::invalid_argument("index out of range");
    }
}
Cuboid Drone::getDeck() {
    return this->deck;
}

void Drone::calculatePosition() {
    this->deck.calculateActualPosition();
    for(int i = 0 ; i < NUMBER_OF_ROTORS; ++i){
        this->rotors[i].calculateActualPosition(this->deck.getPosition());
    }
}

void Drone::rotateDrone(Matrix3x3 rotMatrix) {

    Matrix3x3 orient;

/*rotate deck has to be before rotors*/
    orient = (this->deck.getOrientation());
    orient = rotMatrix * orient;
    this->deck.setOrientation(orient);


    /*rotate rotors*/
    for(int i = 0; i < NUMBER_OF_ROTORS; ++i){
        orient = this->rotors[i].getOrientation();
        orient = rotMatrix * orient;
        this->rotors[i].setOrientation(orient);
    }

}

void Drone::translateDrone(vector3D vec) {
    vector3D pos = (this->deck.getPosition());
    pos = pos + vec;
    this->deck.setPosition(pos);
    for(int i = 0; i < NUMBER_OF_ROTORS; ++i){
        pos = (this->rotors[i].getPosition());
        pos = pos + vec;
        this->rotors[i].setPosition(pos);
    }
}


void Drone::rotateRotors(const Matrix3x3 &rotLeft, const Matrix3x3 &rotRight, const int &numberOfRotation) {
    vector3D pos;
    vector3D deckCenterCords = this->deck.getPosition();
    Matrix3x3 matrixToAnimateLeft = Matrix3x3();
    Matrix3x3 matrixToAnimateRight = Matrix3x3();
//    numberOfRotation = numberOfRotation % 360;

    /* creating proper matrix */
    for(int i = 0; i <numberOfRotation; ++i){
        matrixToAnimateLeft = rotLeft * matrixToAnimateLeft;
        matrixToAnimateRight = rotRight * matrixToAnimateRight;
    }



    /*rotating by this matrix and going back to proper position */
    for(int r = 0; r < NUMBER_OF_ROTORS; ++r){
        this->rotors[r].readModelVerticesPosition();
    /* rotate rotor in his center of mass */
        if(r%2 == 0){
            this->rotors[r].rotationByMatrix(matrixToAnimateRight);
        }else{
            this->rotors[r].rotationByMatrix(matrixToAnimateLeft);
        }
        /*translate to deck coord system */
        pos = this->rotors[r].getPosition();
        pos = pos - deckCenterCords;
        this->rotors[r].translationByVector(pos);
        /* rotate by orientation*/
        this->rotors[r].rotationByMatrix(this->rotors[r].getOrientation());
        /*translate rotors back to main coord system*/
        this->rotors[r].translationByVector(this->deck.getPosition());
    }
}
