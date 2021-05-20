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
//            case 'p':
//                chooseIndex(gnu);
//                std::cin >> gnu.translation;
//                std::cout << "give amount of translation (it has to be positive integer) \n";
//                std::cin >> amountOfTranslation;
//                if(amountOfTranslation <= 0){
//                    throw std::invalid_argument("Incorrect amount of rotation");
//                }
//                for(int z = 0; z < amountOfTranslation; z++){
//                    gnu.animateTranslateRectangle();
//                }
//                break;
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
  std::cout << "m - display menu\n";
  std::cout << "k - close\n";

}

//void getRotationMatrix(scene &gnu){
//    char ch;
//    bool fail = false;
//    Cuboid oldCuboid = gnu.cub[gnu.chosenIndex];
//    gnu.rotMatrix = Matrix3x3();
//    double degree;
//    while(ch != '.'){
//        std::cout << "give axis ann angle in degree\n";
//        if(!(std::cin >> ch)){
//            throw std::exception();
//        }
//        if(ch == '.') break;
//        switch (ch) {
//            case'x':
//                fail = false;
//                break;
//            case'y':
//                fail = false;
//                break;
//            case'z':
//                fail = false;
//                break;
//            default:
//                std::cout <<"unknown axis, try again\n";
//                fail = true;
//                break;
//        }
//        if(!fail){
//            if(!(std::cin >> degree)){
//                throw std::exception();
//            }
//            // this method downstairs actualize cuboid and actualize rotMatrix
//            gnu.animateRotateCuboid(degree, ch);
//        }
//    }
//    gnu.cub[gnu.chosenIndex] = oldCuboid;
//}
//
//void chooseIndex(scene &gnu){
//    int in;
//    std::cout << "chose Index of cuboid you want to operate\n(indexing from 0 to 4, dont screw it up !!!)\n";
//    std::cin >> in;
//    if(in > 4 || in < 0){
//        throw std::invalid_argument("index out of range. You screwed up ...");
//    }
//    gnu.chosenIndex = in;
//}