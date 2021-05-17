//
// Created by artur on 4/11/21.
//

#ifndef ROTATION3D_GNUPLOTDRAWINGS_H
#define ROTATION3D_GNUPLOTDRAWINGS_H
#include <unistd.h>
#include "Drone.h"
#include <lacze_do_gnuplota.hh>
#include <fstream>
#include "HexagonalPrism.h"

class scene{
private:
    std::string boardFileName = "../data/board.txt";
    PzG::LaczeDoGNUPlota GNU;
    double XRange[2];
    double YRange[2];
    double ZRange[2];
    Drone drone[NUMBER_OF_DRONES];
    Matrix3x3 rotMatrix = Matrix3x3();
    vector3D translation = vector3D();
    int chosenIndex;

public:
    scene();
    scene(double _XRange[2], double _YRange[2], double _ZRange[2]);
    void drawScene();
//    void animateRotateCuboid(double &degree, char &axis);
//    void animateTranslateRectangle();
//    void rotateByAmountOfRotation(int amountOfRotation);
    const Drone & operator[](int index) const;
    Drone & operator[](int index);
    int getIndex();
    void setIndex(int index);
    void setTranslation(vector3D translation);
    vector3D getTranslation();
    void setRotation(Matrix3x3 rotMatrix);
    Matrix3x3 getRotation();
};

#endif //ROTATION3D_GNUPLOTDRAWINGS_H
