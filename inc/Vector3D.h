//
// Created by artur on 5/13/21.
//

#ifndef DRONE_SCENE_VECTOR3D_H
#define DRONE_SCENE_VECTOR3D_H
#include "Vector.h"


class vector3D
        :public Vector<double ,3>{
public:
    vector3D();
    vector3D(double x, double y, double z);
    vector3D& operator=(const vector3D vec);
    vector3D& operator=(const Vector<double, 3> vec);
};
#endif //DRONE_SCENE_VECTOR3D_H
