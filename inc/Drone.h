//
// Created by artur on 5/10/21.
//

#ifndef DRONE_SCENE_DRONE_H
#define DRONE_SCENE_DRONE_H
#include "Cuboid.h"
#include "HexagonalPrism.h"
#include "Vector3D.h"

class Drone{
protected:
    Cuboid deck;
    HexagonalPrism rotors[NUMBER_OF_ROTORS];
public:
    /*! left up rotor ->0, right up->1, right down ->2, left down -> 3 */
    Drone();
    Drone(std::string fileNameOfDeck, std::string fileNameOfRotor0,
          std::string fileNameOfRotor1, std::string fileNameOfRotor2,
          std::string fileNameOfRotor3, vector3D initialTranslation, Matrix3x3 initialOrientation);
//    void unitRotationOfRotors();
    const HexagonalPrism & operator[](int index) const;
    HexagonalPrism & operator[](int index);
    Cuboid getDeck();
    void calculatePosition();
};

#endif //DRONE_SCENE_DRONE_H
