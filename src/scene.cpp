//
// Created by artur on 4/11/21.
//
#include "scene.h"
#include "../inc/scene.h"


scene::scene() {
    GNU.ZmienTrybRys(PzG::TR_3D);
    this->fileName[0] = "../data/data.txt";
    this->fileName[1] = "../data/data1.txt";
    this->fileName[2] = "../data/data2.txt";
    this->fileName[3] = "../data/data3.txt";
    this->fileName[4] = "../data/data4.txt";
    this->XRange[0] = 0;
    this->XRange[1] = 0;
    this->YRange[0] = 0;
    this->YRange[1] = 0;
    this->drone1FileName[0] = "../data/drone1_rotor0.txt";
    this->drone1FileName[1] = "../data/drone1_rotor1.txt";
    this->drone1FileName[2] = "../data/drone1_rotor2.txt";
    this->drone1FileName[3] = "../data/drone1_rotor3.txt";
    this->drone1FileName[4] = "../data/drone1_deck.txt";
}

scene::scene(double _XRange[2], double _YRange[2], double _ZRange[2]) {
    this->fileName[0] = "../data/data.txt";
    this->fileName[1] = "../data/data1.txt";
    this->fileName[2] = "../data/data2.txt";
    this->fileName[3] = "../data/data3.txt";
    this->fileName[4] = "../data/data4.txt";

    this->drone1FileName[0] = "../data/drone1_rotor0.txt";
    this->drone1FileName[1] = "../data/drone1_rotor1.txt";
    this->drone1FileName[2] = "../data/drone1_rotor2.txt";
    this->drone1FileName[3] = "../data/drone1_rotor3.txt";
    this->drone1FileName[4] = "../data/drone1_deck.txt";

    this->boardFileName = "../data/board.txt";

    this->XRange[0] = _XRange[0];
    this->XRange[1] = _XRange[1];
    this->YRange[0] = _YRange[0];
    this->YRange[1] = _YRange[1];
    this->ZRange[0] = _ZRange[0];
    this->ZRange[1] = _ZRange[1];


    GNU.UstawRotacjeXZ(60,30);
    for( int i = 0; i < 5; ++i){
        GNU.DodajNazwePliku(this->fileName[i].c_str())
                .ZmienSposobRys(PzG::SR_Ciagly)
                .ZmienSzerokosc(1)
                .ZmienKolor(i + 1);
    }

    for( int i = 0; i < 5; ++i){
        GNU.DodajNazwePliku(this->drone1FileName[i].c_str())
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
    for(int i = 0; i < 5; i++){
        os.open(this->fileName[i]);
        if(!os){
            throw std::exception();
        }
        os << cub[i];
        os.close();
    }

    for(int i = 0; i < 5; i++){
        os.open(this->drone1FileName[i]);
        if(!os){
            throw std::exception();
        }
        os << drone1[i];
        os.close();
    }

    /* drawing hex*/
    os.open(hex.getFileNameOfBlock());
    if(!os){
        throw std::exception();
    }
    os << hex;
    os.close();

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


void scene::animateRotateCuboid( double &degree, char &axis) {
    Cuboid oldCub = this->cub[this->chosenIndex];
    Matrix3x3 rotMatrix = Matrix3x3();
    Matrix3x3 oldMatrix = this->rotMatrix;
    double singleDegree = 0;
    while (std::abs(singleDegree) < std::abs(degree)){
        singleDegree += 2;
        if(degree >= 0){
            rotMatrix = Matrix3x3(2,axis);
            this->cub[this->chosenIndex].rotationByMatrix(rotMatrix);
        }else{
            rotMatrix = Matrix3x3(-2,axis);
            this->cub[this->chosenIndex].rotationByMatrix(rotMatrix);
        }
        usleep(ANIMATION_SPEED);
        drawScene();
    }
    this->cub[this->chosenIndex] = oldCub;
    this->rotMatrix = Matrix3x3(degree, axis);
    this->cub[this->chosenIndex].rotationByMatrix(this->rotMatrix);
    this->rotMatrix = this->rotMatrix * oldMatrix;
    drawScene();
}

void scene::animateTranslateRectangle() {
    Cuboid oldCub = this->cub[this->chosenIndex];
    vector3D animateTranslation = this->translation;
    animateTranslation = animateTranslation/this->translation.getLength();
    vector3D unityTranslation = this->translation;
    unityTranslation = unityTranslation/this->translation.getLength();
    unityTranslation = unityTranslation/RESOLUTION;
    double i = 0;
    while (animateTranslation.getLength() < this->translation.getLength()){
        i++;
        animateTranslation = unityTranslation * i;
        this->cub[this->chosenIndex].translationByVector(animateTranslation);
        usleep(ANIMATION_SPEED);
        drawScene();
        this->cub[this->chosenIndex] = oldCub;
//        animateTranslation = animateTranslation + unityTranslation;
    }
    this->cub[this->chosenIndex] = oldCub;
    this->cub[this->chosenIndex].translationByVector(this->translation);
    drawScene();
}

void scene::rotateByAmountOfRotation(int amountOfRotation) {

    Matrix3x3 matrixGetForSingleRotation = this->rotMatrix;
    for(int k = 1; k < amountOfRotation; ++k){
        this->rotMatrix = matrixGetForSingleRotation * this->rotMatrix;
    }
    this->cub[this->chosenIndex].rotationByMatrix(this->rotMatrix);
    drawScene();
}
