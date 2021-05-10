//
// Created by artur on 5/10/21.
//

#ifndef DRONE_SCENE_DRONE_H
#define DRONE_SCENE_DRONE_H
#include "Cuboid.h"

class Drone{
private:
    Cuboid<double> deck;
    Cuboid<double> rotors[NUMBER_OF_ROTORS];

public:
    /*! left up rotor ->0, right up->1, right down ->2, left down -> 3 */
    Drone();
    Drone(Vector<double, 3> translation);
    void unitRotationOfRotors();
    const Cuboid<double> & operator[](int index) const;
    Cuboid<double> & operator[](int index);
};


#endif //DRONE_SCENE_DRONE_H
