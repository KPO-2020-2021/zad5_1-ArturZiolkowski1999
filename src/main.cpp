#include <iostream>
#include <fstream>
#include <lacze_do_gnuplota.hh>
#include <utility>
#include "../inc/Matrix3x3.h"
#include "Cuboid.h"
#include "Vector3D.h"
#include "scene.h"



void menuDisplay();
//void getRotationMatrix(scene &gnu);
//void chooseIndex(scene &gnu);

int main() {


    /* Initialize "Lacze do gnuplota" to work with in class scene*/
    double XRange[2] = {0, 200};
    double YRange[2] = {0, 200};
    double ZRange[2] = {0, 200};
    scene gnu = scene(XRange, YRange, ZRange);


    /*display menu*/
    menuDisplay();
    gnu.changeDronesColors();
    gnu.drawScene();

    double lengthOfFlight; double angleOfFlight;;
    int droneIndex;
    char c = ' ';
    while(c != 'k'){
        gnu.drawScene();
        if(!(std::cin >> c)){
            throw std::exception();
        }
        switch (c) {
            case 'm':
                menuDisplay();
                break;
            case 'a':
                if(gnu.getIndex() == 0){
                    std::cout << "position of Drone 0: (" << gnu[0].getDeck().getPosition()[0]
                    << ", " << gnu[0].getDeck().getPosition()[1] <<") <- active\n";

                    std::cout << "position of Drone 1: (" << gnu[1].getDeck().getPosition()[0]
                    << ", " << gnu[1].getDeck().getPosition()[1] <<")\n";;
                }else if(gnu.getIndex() == 1){
                    std::cout << "position of Drone 0: (" << gnu[0].getDeck().getPosition()[0]
                              << ", " << gnu[0].getDeck().getPosition()[1] <<")\n";

                    std::cout << "position of Drone 1: (" << gnu[1].getDeck().getPosition()[0]
                              << ", " << gnu[1].getDeck().getPosition()[1] <<") <- active\n";;
                }else{
                    throw std::invalid_argument("Unknown drone is chosen");
                }
                    std::cout << "Give doron index (from 0 to 1)\n";
                    std::cin >> droneIndex;
                    if(droneIndex != 0 && droneIndex != 1){
                        throw std::invalid_argument("Unknown drone is chosen");
                    }
                    gnu.setIndex(droneIndex);
                    gnu.changeDronesColors();
                break;
            case 'p':
                std::cout << "give target angle in degree\n";
                std::cin >> angleOfFlight;
                std::cout << "give length of flight in degree\n";
                std::cin >> lengthOfFlight;

                gnu.animateDroneTranslation(angleOfFlight, lengthOfFlight);

                /*updating scene */
                gnu[gnu.getIndex()].calculatePosition();
                gnu.drawScene();

            case 'w':
                std::cout << vector3D::getTotal() << "<-- Total\n";
                std::cout << vector3D::getActual() << "<-- Actual\n";
                break;
            case 'c':
                gnu.makeCircleWithDrone(20);
                break;
//            case 'w':
//                chooseIndex(gnu);
//                std::cout << gnu.cub[gnu.chosenIndex];
//                break;
//            case 'r':
//                std::cout << gnu.rotMatrix;
                break;
            case 'k':
                break;
            default:
                std::cout << "unknown argument, pleas use correct arguments\n";
                break;
        }
        std::cout << "You chose: '"<< c << "' (m-menu)\n";
    }
}

void menuDisplay(){
  std::cout << "a - chose index of drone (0 or 1)\n";
  std::cout << "p - chose target position of chosen drone\n";
  std::cout << "c - make circle\n";
  std::cout << "w - print number of vector3D\n";
  std::cout << "m - display menu\n";
  std::cout << "k - close\n";

}
