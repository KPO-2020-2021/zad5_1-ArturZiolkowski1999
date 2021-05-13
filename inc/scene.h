//
// Created by artur on 4/11/21.
//

#ifndef ROTATION3D_GNUPLOTDRAWINGS_H
#define ROTATION3D_GNUPLOTDRAWINGS_H
#include <unistd.h>
#include "Drone.h"
#include <lacze_do_gnuplota.hh>
#include <fstream>

class scene{
private:
    std::string drone1FileName[5];
    std::string boardFileName;
    std::string fileName[5];
    PzG::LaczeDoGNUPlota GNU;
    double XRange[2];
    double YRange[2];
    double ZRange[2];

public:
    Drone drone1;
    int chosenIndex;
    Matrix3x3 rotMatrix = Matrix3x3();
    vector3D translation;
    Cuboid cub[5];
    scene();
    scene(double _XRange[2], double _YRange[2], double _ZRange[2]);
    void drawScene();
    void animateRotateCuboid(double &degree, char &axis);
    void animateTranslateRectangle();
    void rotateByAmountOfRotation(int amountOfRotation);
};

#endif //ROTATION3D_GNUPLOTDRAWINGS_H
