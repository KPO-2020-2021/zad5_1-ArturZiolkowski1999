//
// Created by artur on 5/10/21.
//

#ifndef DRONE_SCENE_DRONE_H
#define DRONE_SCENE_DRONE_H
#include "Cuboid.h"
#include "Vector3D.h"

class Drone{
private:
    Cuboid deck;
    Cuboid rotors[NUMBER_OF_ROTORS];
public:
    /*! left up rotor ->0, right up->1, right down ->2, left down -> 3 */
    Drone();
    Drone(vector3D translation);
    void unitRotationOfRotors();
    const Cuboid & operator[](int index) const;
    Cuboid & operator[](int index);
};

#endif //DRONE_SCENE_DRONE_H
