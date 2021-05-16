#include <iostream>
#include <fstream>
#include <lacze_do_gnuplota.hh>
#include <utility>
#include "../inc/Matrix3x3.h"
#include "Cuboid.h"
#include "Vector3D.h"
#include "scene.h"
#define Vector vector3D


void menuDisplay();
void getRotationMatrix(scene &gnu);
void chooseIndex(scene &gnu);

int main() {
    /* Initialize Cuboid and translation vector and axis*/
    vector3D Ver0 = vector3D(0,1,1); vector3D Ver1 = vector3D(5,1,1);
    vector3D Ver2 = vector3D(5,1,4); vector3D Ver3 = vector3D(0,1,4);

    vector3D Ver4 = vector3D(0,3,1); vector3D Ver5 = vector3D(5,3,1);
    vector3D Ver6 = vector3D(5,3,4); vector3D Ver7 = vector3D(0,3,4);

    vector3D tr1 = vector3D(-5,-5,-5); vector3D tr2 = vector3D();
    vector3D vertices[VERTICES_NUMBER_OF_CUBOID] = {Ver0, Ver1, Ver2, Ver3, Ver4, Ver5, Ver6, Ver7};

    /* Initialize "Lacze do gnuplota" to work with in class scene*/
    double XRange[2] = {-20, 20};
    double YRange[2] = {-20, 20};
    double ZRange[2] = {-20, 20};
    scene gnu = scene(XRange, YRange, ZRange);
    for (int t = 0; t < 5; t++){
        for(int k = 0; k < VERTICES_NUMBER_OF_CUBOID; k++){
            tr2 = tr1 * t;
            vertices[k] = vertices[k] + tr2;
        }
        gnu.cub[t] = Cuboid();
    }

    Ver6 =  Ver6 * -2;
    gnu.drone1 = Drone();

    /* Drawing initial rectangle and display menu*/
    menuDisplay();

    int amountOfRotation, amountOfTranslation;
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
            case 'o':
                chooseIndex(gnu);
                gnu.rotMatrix = Matrix3x3();
                getRotationMatrix(gnu);
                std::cout << "give amount of rotation (it has to be positive integer) \n";
                std::cin >> amountOfRotation;
                if(amountOfRotation <= 0){
                    throw std::invalid_argument("Incorrect amount of rotation");
                }
                gnu.rotateByAmountOfRotation(amountOfRotation);
                break;
            case 'p':
                chooseIndex(gnu);
                std::cin >> gnu.translation;
                std::cout << "give amount of translation (it has to be positive integer) \n";
                std::cin >> amountOfTranslation;
                if(amountOfTranslation <= 0){
                    throw std::invalid_argument("Incorrect amount of rotation");
                }
                for(int z = 0; z < amountOfTranslation; z++){
                    gnu.animateTranslateRectangle();
                }
                break;
            case 'w':
                chooseIndex(gnu);
                std::cout << gnu.cub[gnu.chosenIndex];
                break;
            case 'r':
                std::cout << gnu.rotMatrix;
                break;
            case 'k':
                break;
            case 't':
                gnu.cub[gnu.chosenIndex].rotationByMatrix(gnu.rotMatrix);
                gnu.drawScene();
                break;
            case 'l':
                chooseIndex(gnu);
                gnu.cub[gnu.chosenIndex].calculateSidesLength();
                std::cout << "first sides: " << gnu.cub[gnu.chosenIndex].getSideLength(0) << std::endl;
                std::cout << "first sides: " << gnu.cub[gnu.chosenIndex].getSideLength(1) << std::endl;
                std::cout << "first sides: " << gnu.cub[gnu.chosenIndex].getSideLength(2) << std::endl;
                std::cout << "first sides: " << gnu.cub[gnu.chosenIndex].getSideLength(3) << std::endl;

                std::cout << "second sides: " << gnu.cub[gnu.chosenIndex].getSideLength(4) << std::endl;
                std::cout << "second sides: " << gnu.cub[gnu.chosenIndex].getSideLength(5) << std::endl;
                std::cout << "second sides: " << gnu.cub[gnu.chosenIndex].getSideLength(6) << std::endl;
                std::cout << "second sides: " << gnu.cub[gnu.chosenIndex].getSideLength(7) << std::endl;

                std::cout << "third sides: " << gnu.cub[gnu.chosenIndex].getSideLength(8) << std::endl;
                std::cout << "third sides: " << gnu.cub[gnu.chosenIndex].getSideLength(9) << std::endl;
                std::cout << "third sides: " << gnu.cub[gnu.chosenIndex].getSideLength(10) << std::endl;
                std::cout << "third sides: " << gnu.cub[gnu.chosenIndex].getSideLength(11) << std::endl;
                break;
            default:
                std::cout << "unknown argument, pleas use correct arguments\n";
                break;
        }
        std::cout << "You chose: '"<< c << "' (m-menu)\n";
    }
}

void menuDisplay(){
  std::cout << "o - rotate rectangle by angle in degree\n";
  std::cout << "p - translate rectangle by vector\n";
  std::cout << "w - display coordinates of rectangle vertices\n";
  std::cout << "m - display menu\n";
  std::cout << "k - close\n";
  std::cout << "l - display length of sides\n";
  std::cout << "r - display last rotational matrix\n";
  std::cout << "t - repeat the last rotation\n";
}

void getRotationMatrix(scene &gnu){
    char ch;
    bool fail = false;
    Cuboid oldCuboid = gnu.cub[gnu.chosenIndex];
    gnu.rotMatrix = Matrix3x3();
    double degree;
    while(ch != '.'){
        std::cout << "give axis ann angle in degree\n";
        if(!(std::cin >> ch)){
            throw std::exception();
        }
        if(ch == '.') break;
        switch (ch) {
            case'x':
                fail = false;
                break;
            case'y':
                fail = false;
                break;
            case'z':
                fail = false;
                break;
            default:
                std::cout <<"unknown axis, try again\n";
                fail = true;
                break;
        }
        if(!fail){
            if(!(std::cin >> degree)){
                throw std::exception();
            }
            // this method downstairs actualize cuboid and actualize rotMatrix
            gnu.animateRotateCuboid(degree, ch);
        }
    }
    gnu.cub[gnu.chosenIndex] = oldCuboid;
}

void chooseIndex(scene &gnu){
    int in;
    std::cout << "chose Index of cuboid you want to operate\n(indexing from 0 to 4, dont screw it up !!!)\n";
    std::cin >> in;
    if(in > 4 || in < 0){
        throw std::invalid_argument("index out of range. You screwed up ...");
    }
    gnu.chosenIndex = in;
}