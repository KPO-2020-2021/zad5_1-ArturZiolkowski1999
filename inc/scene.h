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

    /*! animate upward and downward movement  'u' as argument means upward, 'd' means downward*/
    void animateUpwardsMovement(char direction);
    /*! write route to file, so this could be drawn by gnuplot */
    void writeRouteToFile(vector3D &translation);
    /*! delete written route from gnuplot file */
    void deleteRouteFromFile();

public:
    scene();
    scene(double _XRange[2], double _YRange[2], double _ZRange[2]);
    /*! draw every element of scene */
    void drawScene();
    /*! full animated drone translation with route drawing and moving up and down*/
    void animateDroneTranslation(double angleOfFlight, double lengthOfFlight);
    /*! simple animated drone flight without route drawing and moving up and down*/
    void animateSimpleDroneTranslation(double angleOfFlight, vector3D targetVec);
    /*! animate rotation by given degry around 'z'matrix */
    void animateRotation(double targetAngle, char axis);

    const Drone & operator[](int index) const;
    Drone & operator[](int index);
    int getIndex();
    void setIndex(int index);
    /*! changing color of chosen drone and not chosen drone */
    void changeDronesColors();
    /*! make circle shaped route with landing */
    void makeCircleWithDrone(double radius);
};

#endif //ROTATION3D_GNUPLOTDRAWINGS_H
