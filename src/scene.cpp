//
// Created by artur on 4/11/21.
//
#include "scene.h"
#include "../inc/scene.h"


scene::scene() {
    GNU.ZmienTrybRys(PzG::TR_3D);
    this->XRange[0] = 0;
    this->XRange[1] = 0;
    this->YRange[0] = 0;
    this->YRange[1] = 0;

    vector3D initialPosDrone0 = vector3D(0,0,0.5);
    vector3D initialPosDrone1 = vector3D(10,10,0.5);
    Matrix3x3 initialOrientation = Matrix3x3();

    this->drone[0] = Drone("../data/drone0_deck.txt", "../data/drone0_rotor0.txt",
                           "../data/drone0_rotor1.txt", "../data/drone0_rotor2.txt",
                           "../data/drone0_rotor3.txt", initialPosDrone0, initialOrientation);

    this->drone[1] = Drone("../data/drone1_deck.txt", "../data/drone1_rotor0.txt",
                           "../data/drone1_rotor1.txt", "../data/drone1_rotor2.txt",
                           "../data/drone1_rotor3.txt", initialPosDrone1, initialOrientation);

}

scene::scene(double _XRange[2], double _YRange[2], double _ZRange[2]) {

    this->XRange[0] = _XRange[0];
    this->XRange[1] = _XRange[1];
    this->YRange[0] = _YRange[0];
    this->YRange[1] = _YRange[1];
    this->ZRange[0] = _ZRange[0];
    this->ZRange[1] = _ZRange[1];

    vector3D initialPosDrone0 = vector3D(20,20,1);
    vector3D initialPosDrone1 = vector3D(180,180,1);
    Matrix3x3 initialOrientation = Matrix3x3();

    this->drone[0] = Drone("../data/drone0_deck.txt", "../data/drone0_rotor0.txt",
                           "../data/drone0_rotor1.txt", "../data/drone0_rotor2.txt",
                           "../data/drone0_rotor3.txt", initialPosDrone0, initialOrientation);

    this->drone[1] = Drone("../data/drone1_deck.txt", "../data/drone1_rotor0.txt",
                   "../data/drone1_rotor1.txt", "../data/drone1_rotor2.txt",
                   "../data/drone1_rotor3.txt", initialPosDrone1, initialOrientation);


    GNU.UstawRotacjeXZ(60,30);


    for(int h = 0; h < NUMBER_OF_DRONES; ++h){
        /* rotors file*/
        for( int i = 0; i < NUMBER_OF_ROTORS; ++i){
            GNU.DodajNazwePliku(this->drone[h][i].getFileNameOfBlock().c_str())
                    .ZmienSposobRys(PzG::SR_Ciagly)
                    .ZmienSzerokosc(1)
                    .ZmienKolor(2);
        }
        /* deck file */
        GNU.DodajNazwePliku(this->drone[h].getDeck().getFileNameOfBlock().c_str())
                .ZmienSposobRys(PzG::SR_Ciagly)
                .ZmienSzerokosc(1)
                .ZmienKolor(2);
    }

    GNU.DodajNazwePliku(this->boardFileName.c_str())
            .ZmienSposobRys(PzG::SR_Ciagly)
            .ZmienSzerokosc(1)
            .ZmienKolor(1);

    GNU.ZmienTrybRys(PzG::TR_3D);
    GNU.UstawZakresX((this->XRange[0]),(this->XRange[1]));
    GNU.UstawZakresY((this->YRange[0]),(this->YRange[1]));
    GNU.UstawZakresZ((this->ZRange[0]),(this->ZRange[1]));
}

void scene::drawScene(){
    std::ofstream os;

/* Drawing drones*/
    HexagonalPrism rotor;
    Cuboid deck;
    for(int f = 0; f < NUMBER_OF_DRONES; ++f){
        this->drone[f].calculatePosition();
        /* Draw deck of drone[f]*/
        os.open(this->drone[f].getDeck().getFileNameOfBlock());
        if(!os) {
            throw std::invalid_argument("openingDeckFile\n");
        }
        deck = this->drone[f].getDeck();
        os << deck;

        os.close();

        /* Draw rotors of drone[f]*/
        for(int h = 0; h < NUMBER_OF_ROTORS; ++h){
            os.open(this->drone[f][h].getFileNameOfBlock());
            if(!os) {
                throw std::invalid_argument("openingRotorFile\n");
            }
            rotor = this->drone[f][h];
            os << rotor;
            os.close();
        }
    }


    /* Drawing simple background */
    os.open(this->boardFileName);
    if(!os){
        throw std::exception();
    }
    for(int k = 0; k <= 200; k+= 10){
        for(int l = 0; l <= 200; l += 10){
        os << l << " " << k+10 << " 0\n";
        os << l << " " << k << " 0\n";
            if(l <200){
                os << "#\n\n";
            }
        }
        os << 0 << " " << k << " 0\n#\n\n";
    }
    os.close();

    GNU.Inicjalizuj();
    GNU.Rysuj();
}

//
//void scene::animateRotateCuboid( double &degree, char &axis) {
//    Cuboid oldCub = this->cub[this->chosenIndex];
//    Matrix3x3 rotMatrix = Matrix3x3();
//    Matrix3x3 oldMatrix = this->rotMatrix;
//    double singleDegree = 0;
//    while (std::abs(singleDegree) < std::abs(degree)){
//        singleDegree += 2;
//        if(degree >= 0){
//            rotMatrix = Matrix3x3(2,axis);
//            this->cub[this->chosenIndex].rotationByMatrix(rotMatrix);
//        }else{
//            rotMatrix = Matrix3x3(-2,axis);
//            this->cub[this->chosenIndex].rotationByMatrix(rotMatrix);
//        }
//        usleep(ANIMATION_SPEED);
//        drawScene();
//    }
//    this->cub[this->chosenIndex] = oldCub;
//    this->rotMatrix = Matrix3x3(degree, axis);
//    this->cub[this->chosenIndex].rotationByMatrix(this->rotMatrix);
//    this->rotMatrix = this->rotMatrix * oldMatrix;
//    drawScene();
//}
//
//void scene::animateTranslateRectangle() {
//    Cuboid oldCub = this->cub[this->chosenIndex];
//    vector3D animateTranslation = this->translation;
//    animateTranslation = animateTranslation/this->translation.getLength();
//    vector3D unityTranslation = this->translation;
//    unityTranslation = unityTranslation/this->translation.getLength();
//    unityTranslation = unityTranslation/RESOLUTION;
//    double i = 0;
//    while (animateTranslation.getLength() < this->translation.getLength()){
//        i++;
//        animateTranslation = unityTranslation * i;
//        this->cub[this->chosenIndex].translationByVector(animateTranslation);
//        usleep(ANIMATION_SPEED);
//        drawScene();
//        this->cub[this->chosenIndex] = oldCub;
////        animateTranslation = animateTranslation + unityTranslation;
//    }
//    this->cub[this->chosenIndex] = oldCub;
//    this->cub[this->chosenIndex].translationByVector(this->translation);
//    drawScene();
//}
//
//void scene::rotateByAmountOfRotation(int amountOfRotation) {
//
//    Matrix3x3 matrixGetForSingleRotation = this->rotMatrix;
//    for(int k = 1; k < amountOfRotation; ++k){
//        this->rotMatrix = matrixGetForSingleRotation * this->rotMatrix;
//    }
//    this->cub[this->chosenIndex].rotationByMatrix(this->rotMatrix);
//    drawScene();
//}

const Drone &scene::operator[](int index) const {
    switch (index) {
        case 0:
            return this->drone[0];
        case 1:
            return this->drone[1];
        default:
            throw std::invalid_argument("index out of range");
    }
}

Drone &scene::operator[](int index) {
    switch (index) {
        case 0:
            return this->drone[0];
        case 1:
            return this->drone[1];
        default:
            throw std::invalid_argument("index out of range");
    }
}