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
    std::string routeFileName = "../data/route.txt";
    PzG::LaczeDoGNUPlota GNU;
    double XRange[2];
    double YRange[2];
    double ZRange[2];
    Drone drone[NUMBER_OF_DRONES];

    int chosenIndex;

public:
    scene();
    scene(double _XRange[2], double _YRange[2], double _ZRange[2]);
    void drawScene();
    void animateDroneTranslation(double angleOfFlight, double lengthOfFlight);
    void animateSimpleDroneTranslation(double angleOfFlight, vector3D targetVec);
    void animateUpwardsMovement(char direction);
    void animateRotation(double targetAngle, char axis);
    void writeRouteToFile(vector3D &translation);
    void deleteRouteFromFile();
    const Drone & operator[](int index) const;
    Drone & operator[](int index);
    int getIndex();
    void setIndex(int index);
    void changeDronesColors();
    void makeCircleWithDrone(vector3D centreOfCircle, double radius);

};

#endif //ROTATION3D_GNUPLOTDRAWINGS_H
