#include <iostream>
#include <fstream>
#include <lacze_do_gnuplota.hh>
#include <utility>
#include "../inc/Matrix3x3.h"
#include "Cuboid.h"
#include "Vector.h"
#include "scene.h"
#define Vector Vector<double, 3>


void menuDisplay();
void getRotationMatrix(scene &gnu);
void chooseIndex(scene &gnu);

int main() {
    /* Initialize Cuboid and translation vector and axis*/
    Vector Ver0 = Vector(0,1,1); Vector Ver1 = Vector(5,1,1);
    Vector Ver2 = Vector(5,1,4); Vector Ver3 = Vector(0,1,4);

    Vector Ver4 = Vector(0,3,1); Vector Ver5 = Vector(5,3,1);
    Vector Ver6 = Vector(5,3,4); Vector Ver7 = Vector(0,3,4);

    Vector tr1 = Vector(-5,-5,-5); Vector tr2 = Vector(5,-5,-5);
    Vector tr3 = Vector(5,5,-5); Vector tr4 = Vector(5,5,5);

    Vector vertices[VERTICES_NUMBER] = {Ver0, Ver1, Ver2, Ver3, Ver4, Ver5, Ver6, Ver7};

    Vector vertices1[VERTICES_NUMBER] = {Ver0 + tr1, Ver1+ tr1, Ver2+ tr1, Ver3+ tr1,
                                        Ver4+ tr1, Ver5+ tr1, Ver6+ tr1, Ver7+ tr1};

    Vector vertices2[VERTICES_NUMBER] = {Ver0 + tr2, Ver1+ tr2, Ver2+ tr2, Ver3+ tr2,
                                        Ver4+ tr2, Ver5+ tr2, Ver6+ tr2, Ver7+ tr2};

    Vector vertices3[VERTICES_NUMBER] = {Ver0 + tr3, Ver1+ tr3, Ver2+ tr3, Ver3+ tr3,
                                        Ver4+ tr3, Ver5+ tr3, Ver6+ tr3, Ver7+ tr3};

    Vector vertices4[VERTICES_NUMBER] = {Ver0 + tr4, Ver1+ tr4, Ver2+ tr4, Ver3+ tr4,
                                        Ver4+ tr4, Ver5+ tr4, Ver6+ tr4, Ver7+ tr4};


    /* Initialize "Lacze do gnuplota" to work with in class scene*/
    double XRange[2] = {-15, 15};
    double YRange[2] = {-15, 15};
    double ZRange[2] = {-15, 15};
    scene gnu = scene(XRange, YRange, ZRange);
    gnu.cub[0] = Cuboid<double>(vertices);
    gnu.cub[1] = Cuboid<double>(vertices1);
    gnu.cub[2] = Cuboid<double>(vertices2);
    gnu.cub[3] = Cuboid<double>(vertices3);
    gnu.cub[4] = Cuboid<double>(vertices4);
    gnu.drone1 = Drone(Ver6);

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
    Cuboid<double> oldCuboid = gnu.cub[gnu.chosenIndex];
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