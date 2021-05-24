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

    this->chosenIndex = 0;

    vector3D initialPosDrone0 = vector3D(0,0,HALF_OF_DRONE_HEIGHT);
    vector3D initialPosDrone1 = vector3D(10,10,HALF_OF_DRONE_HEIGHT);
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

    vector3D initialPosDrone0 = vector3D(20,20,HALF_OF_DRONE_HEIGHT);
    vector3D initialPosDrone1 = vector3D(180,180,HALF_OF_DRONE_HEIGHT);
    Matrix3x3 initialOrientation = Matrix3x3();

    this->drone[0] = Drone("../data/drone0_deck.txt", "../data/drone0_rotor0.txt",
                           "../data/drone0_rotor1.txt", "../data/drone0_rotor2.txt",
                           "../data/drone0_rotor3.txt", initialPosDrone0, initialOrientation);

    this->drone[1] = Drone("../data/drone1_deck.txt", "../data/drone1_rotor0.txt",
                   "../data/drone1_rotor1.txt", "../data/drone1_rotor2.txt",
                   "../data/drone1_rotor3.txt", initialPosDrone1, initialOrientation);


    GNU.UstawRotacjeXZ(80,70);


    for(int h = 0; h < NUMBER_OF_DRONES; ++h){
        /* rotors file*/
        for( int i = 0; i < NUMBER_OF_ROTORS; ++i){
            GNU.DodajNazwePliku(this->drone[h][i].getFileNameOfBlock().c_str())
                    .ZmienSposobRys(PzG::SR_Ciagly)
                    .ZmienSzerokosc(1)
                    .ZmienKolor(CHOSEN_DRONE_COLOR);
        }
        /* deck file */
        GNU.DodajNazwePliku(this->drone[h].getDeck().getFileNameOfBlock().c_str())
                .ZmienSposobRys(PzG::SR_Ciagly)
                .ZmienSzerokosc(1)
                .ZmienKolor(CHOSEN_DRONE_COLOR);
    }

    /*route and board files*/
    GNU.DodajNazwePliku(this->routeFileName.c_str())
            .ZmienSposobRys(PzG::SR_Ciagly)
            .ZmienSzerokosc(1)
            .ZmienKolor(CHOSEN_DRONE_COLOR);

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
//        this->drone[f].calculatePosition();
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

int scene::getIndex() {
    return this->chosenIndex;
}

void scene::setIndex(int index) {
    switch (index) {
        case 0:
            this->chosenIndex = 0;
            break;
        case 1:
            this->chosenIndex = 1;
            break;
        default:
            throw std::invalid_argument("index out of range :(");
    }
}


void scene::animateDroneTranslation(double angleOfFlight, double lengthOfFlight) {
    vector3D targetPosFromDroneCenter;
    vector3D unitTargetPos;
    vector3D animateVector;
    Matrix3x3 targetOrient = Matrix3x3(angleOfFlight, 'z');

    /*animate rotation*/
    animateRotation(angleOfFlight, 'z'),

    /* create vector of proper len but only x cord*/
    targetPosFromDroneCenter = vector3D(lengthOfFlight,0,0);
    /* draw route */
    writeRouteToFile(targetPosFromDroneCenter);
    /* rotating this vec by orientation of drone*/
    targetPosFromDroneCenter = drone[chosenIndex].getDeck().getOrientation() * targetPosFromDroneCenter;

    /* draw route */
    writeRouteToFile(targetPosFromDroneCenter);

    /*translate upwards */
    animateUpwardsMovement('u');

    /* creating auxiliary vectors */
    unitTargetPos = targetPosFromDroneCenter / targetPosFromDroneCenter.getLength();
    unitTargetPos = unitTargetPos * 2;
    animateVector = unitTargetPos;
    while(animateVector.getLength() < targetPosFromDroneCenter.getLength()){
        animateVector = animateVector + unitTargetPos;
        drone[chosenIndex].translateDrone(unitTargetPos);
        drone[chosenIndex].calculatePosition();
        /* animating rotation of rotors */
        /* 10 * 6
         * = 60 -> its important because hexagonal prism after 60 degree rotation are look the same */
        for(int i = 0; i < (60/RESOLUTION); ++i){
            drone[chosenIndex].rotateRotors(Matrix3x3(RESOLUTION, 'z'),Matrix3x3(-RESOLUTION, 'z'), i);
            if(!DO_YOU_HAVE_OLD_AND_VERY_SLOW_PC_IF_YES_SWITCH_TO_TRUE){
                            usleep(ANIMATION_SPEED);
            }
            drawScene();
        }

    }
    animateVector = animateVector * -1;
    drone[chosenIndex].translateDrone(animateVector);
    /* translate drone by this vec*/
    drone[chosenIndex].translateDrone(targetPosFromDroneCenter);
    drone[chosenIndex].calculatePosition();
    drawScene();

    /*translate downwards */
    animateUpwardsMovement('d');

    /* delete route*/
    deleteRouteFromFile();
}

void scene::animateUpwardsMovement(char direction) {
    vector3D targetPosFromDroneCenter;
    vector3D unitTargetPos;
    vector3D animateVector;
    /* create vector upwards/downwards */
    if(direction == 'u'){
        targetPosFromDroneCenter = vector3D(0,0,ALTITUDE_OF_FLIGHT);
    }else if(direction == 'd'){
        targetPosFromDroneCenter = vector3D(0,0,-ALTITUDE_OF_FLIGHT);
    }else{
        throw std::invalid_argument("unknown direction");
    }

    /* creating auxiliary vectors */
    unitTargetPos = targetPosFromDroneCenter / targetPosFromDroneCenter.getLength();
    unitTargetPos = unitTargetPos * 2;
    animateVector = unitTargetPos;
    while(animateVector.getLength() < targetPosFromDroneCenter.getLength()){
        animateVector = animateVector + unitTargetPos;
        drone[chosenIndex].translateDrone(unitTargetPos);
        drone[chosenIndex].calculatePosition();
        /* animating rotation of rotors */
        /* 10 * 6 = 60 -> its important */
        for(int i = 0; i < (60/RESOLUTION); ++i){
            drone[chosenIndex].rotateRotors(Matrix3x3(RESOLUTION, 'z'),Matrix3x3(-RESOLUTION, 'z'), i);
            if(!DO_YOU_HAVE_OLD_AND_VERY_SLOW_PC_IF_YES_SWITCH_TO_TRUE){
                usleep(ANIMATION_SPEED);
            }
            drawScene();
        }

    }
    animateVector = animateVector * -1;
    drone[chosenIndex].translateDrone(animateVector);
    /* translate drone by this vec*/
    drone[chosenIndex].translateDrone(targetPosFromDroneCenter);
    drone[chosenIndex].calculatePosition();
    drawScene();
}

void scene::writeRouteToFile(vector3D &translation) {
    vector3D upWard = vector3D(0,0, ALTITUDE_OF_FLIGHT);
    vector3D pos;
    std::ofstream os;
    os.open(this->routeFileName);
    if(!os){
        throw std::exception();
    }
    /*Starting point */
    os << this->drone[this->chosenIndex].getDeck().getPosition();

    /*upward position */
    pos = this->drone[this->chosenIndex].getDeck().getPosition() ;
    pos = pos + upWard;
    os << pos;
    /*translated position */
    pos = pos + translation;
    os << pos;
    /* downward position*/
    pos = pos - upWard;
    os << pos;
    os.close();
}

void scene::deleteRouteFromFile() {
    std::ofstream os;
    os.open(this->routeFileName);
    if(!os){
        throw std::exception();
    }

    os.close();
}

void scene::changeDronesColors() {
    if(this->chosenIndex == 0){
        for(int i = 0; i < NUMBER_OF_ROTORS; ++ i){
            GNU.DodajNazwePliku(this->drone[0][i].getFileNameOfBlock().c_str())
                    .ZmienSposobRys(PzG::SR_Ciagly)
                    .ZmienSzerokosc(1)
                    .ZmienKolor(CHOSEN_DRONE_COLOR);
        }
        GNU.DodajNazwePliku(this->drone[0].getDeck().getFileNameOfBlock().c_str())
                .ZmienSposobRys(PzG::SR_Ciagly)
                .ZmienSzerokosc(1)
                .ZmienKolor(CHOSEN_DRONE_COLOR);

        for(int i = 0; i < NUMBER_OF_ROTORS; ++ i){
            GNU.DodajNazwePliku(this->drone[1][i].getFileNameOfBlock().c_str())
                    .ZmienSposobRys(PzG::SR_Ciagly)
                    .ZmienSzerokosc(1)
                    .ZmienKolor(NOT_CHOSEN_DRONE_COLOR);
        }
        GNU.DodajNazwePliku(this->drone[1].getDeck().getFileNameOfBlock().c_str())
                .ZmienSposobRys(PzG::SR_Ciagly)
                .ZmienSzerokosc(1)
                .ZmienKolor(NOT_CHOSEN_DRONE_COLOR);
    }else if(this->chosenIndex = 1){
        for(int i = 0; i < NUMBER_OF_ROTORS; ++ i){
            GNU.DodajNazwePliku(this->drone[1][i].getFileNameOfBlock().c_str())
                    .ZmienSposobRys(PzG::SR_Ciagly)
                    .ZmienSzerokosc(1)
                    .ZmienKolor(CHOSEN_DRONE_COLOR);
        }
        GNU.DodajNazwePliku(this->drone[1].getDeck().getFileNameOfBlock().c_str())
                .ZmienSposobRys(PzG::SR_Ciagly)
                .ZmienSzerokosc(1)
                .ZmienKolor(CHOSEN_DRONE_COLOR);

        for(int i = 0; i < NUMBER_OF_ROTORS; ++ i){
            GNU.DodajNazwePliku(this->drone[0][i].getFileNameOfBlock().c_str())
                    .ZmienSposobRys(PzG::SR_Ciagly)
                    .ZmienSzerokosc(1)
                    .ZmienKolor(NOT_CHOSEN_DRONE_COLOR);
        }
        GNU.DodajNazwePliku(this->drone[0].getDeck().getFileNameOfBlock().c_str())
                .ZmienSposobRys(PzG::SR_Ciagly)
                .ZmienSzerokosc(1)
                .ZmienKolor(NOT_CHOSEN_DRONE_COLOR);
    }else{
        throw std::invalid_argument("out of index");
    }
}

void scene::animateRotation(double targetAngle, char axis) {

    if(axis != 'x' && axis != 'y' && axis != 'z'){
        throw std::invalid_argument("unknown axis");
    }
    /* create single degree rotation matrix */
    Matrix3x3 targetMatrix = Matrix3x3(targetAngle, axis);
    Matrix3x3 reverseAnimateMatrix = Matrix3x3();
    Matrix3x3 unitMatrixMinus = Matrix3x3(-2, axis);
    Matrix3x3 unitMatrixPlus = Matrix3x3(2, axis);

    double animateDegree = 0;

    /* animation */

    while(fabs(animateDegree) < targetAngle){

        if(targetAngle < 0){
            animateDegree -= 2;
            reverseAnimateMatrix = unitMatrixPlus * reverseAnimateMatrix;
        }else{
            animateDegree += 2;
            reverseAnimateMatrix = unitMatrixMinus * reverseAnimateMatrix;
            drone[chosenIndex].rotateDrone(unitMatrixPlus);
        }
        drone[chosenIndex].calculatePosition();

        /* animating rotation of rotors */
        /* 10 * 6 = 60 -> its important */
        for(int i = 0; i < (60/RESOLUTION); ++i){
            drone[chosenIndex].rotateRotors(Matrix3x3(RESOLUTION, 'z'),Matrix3x3(-RESOLUTION, 'z'), i);
//            usleep(ANIMATION_SPEED);
            drawScene();
        }

    }
    drone[chosenIndex].rotateDrone(reverseAnimateMatrix);
    drone[chosenIndex].calculatePosition();;
    drone[chosenIndex].rotateDrone(targetMatrix);
    /* translate drone by this vec*/
    drone[chosenIndex].calculatePosition();
    drawScene();
}

void scene::makeCircleWithDrone(double radius) {


    int numberOfAngles = 20;
    int angleOfCurve = 180 - (180 * numberOfAngles - 360 )/ numberOfAngles;

    vector3D centerOfCircle = this->drone[this->chosenIndex].getDeck().getPosition();
    /* switch z coord to max altitude*/
    centerOfCircle[2] = ALTITUDE_OF_FLIGHT;
    /*translate upwards */
    animateUpwardsMovement('u');
    /*translate by radius */
    vector3D radiusVec = vector3D(radius, 0 ,0);
    Matrix3x3 unitRotation = Matrix3x3(-angleOfCurve, 'z');
    Matrix3x3 rot90 = Matrix3x3(90, 'z');

    animateSimpleDroneTranslation(0,radiusVec);

    vector3D targetPosition = vector3D(0,10,0);
    targetPosition = this->drone[this->chosenIndex].getDeck().getOrientation() * targetPosition;
    targetPosition = rot90 * targetPosition;


    /* calculate vector from centre of circle to drone */

    vector3D distance = this->drone[this->chosenIndex].getDeck().getPosition();
    distance = distance - centerOfCircle;
    for(int i = 0; i < numberOfAngles; i ++){
            animateSimpleDroneTranslation(-angleOfCurve, targetPosition);
            targetPosition = unitRotation * targetPosition;
            /* idz o wektor do przodu */

    }

    radiusVec = radiusVec * -1;
    animateSimpleDroneTranslation(0,radiusVec);

    /*translate downwards */
    animateUpwardsMovement('d');
    this->drone[this->chosenIndex].calculatePosition();


}

void scene::animateSimpleDroneTranslation(double angleOfFlight, vector3D targetVec) {
    vector3D targetPosFromDroneCenter;
    vector3D unitTargetPos;
    vector3D animateVector = vector3D();
    Matrix3x3 targetOrient = Matrix3x3(angleOfFlight, 'z');

    /*animate rotation*/
    animateRotation(angleOfFlight, 'z');


    /* creating auxiliary vectors */
    unitTargetPos = targetVec / targetVec.getLength();
    unitTargetPos = unitTargetPos * 2;
    animateVector = unitTargetPos;
    while(animateVector.getLength() < targetVec.getLength()){
        animateVector = animateVector + unitTargetPos;
        drone[chosenIndex].translateDrone(unitTargetPos);
        drone[chosenIndex].calculatePosition();
        /* animating rotation of rotors */
        /* 10 * 6
         * = 60 -> its important because hexagonal prism after 60 degree rotation are look the same */
        for(int i = 0; i < (60/RESOLUTION); ++i){
            drone[chosenIndex].rotateRotors(Matrix3x3(RESOLUTION, 'z'),Matrix3x3(-RESOLUTION, 'z'), i);
            if(!DO_YOU_HAVE_OLD_AND_VERY_SLOW_PC_IF_YES_SWITCH_TO_TRUE){
                usleep(ANIMATION_SPEED);
            }
            drawScene();
        }

    }
    animateVector = animateVector * -1;
    drone[chosenIndex].translateDrone(animateVector);
    /* translate drone by this vec*/
    drone[chosenIndex].translateDrone(targetVec);
    drone[chosenIndex].calculatePosition();
    drawScene();

}

