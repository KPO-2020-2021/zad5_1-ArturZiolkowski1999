#include "gtest/gtest.h"
#include "Matrix4x4.h"
#include <iostream>
#include <utility>
#include "Drone.h"
#include "Constants.h"
#include "HexagonalPrism.h"




TEST (Vector, EmptyConstructor) {

    // 3 dim
    vector3D Vec1 = vector3D();
    vector3D Vec2 = vector3D();
    Vec1.setX(0);
    Vec1.setY(0);
    Vec1.setZ(0);
    EXPECT_EQ(Vec1, Vec2);

    // 2 dim
    Vector<double, 2> Vec3 = Vector<double, 2>();
    Vector<double, 2> Vec4 = Vector<double, 2>();
    Vec1.setX(0);

    EXPECT_EQ(Vec3, Vec4);
}

TEST (Vector, Constructor) {

    // 3 dim
    Vector<double, 3> Vec1 = Vector<double, 3>(2.3,4.5, 1.1);
    Vector<double, 3> Vec2 = Vector<double, 3>();
    Vec2.setX(2.3);
    Vec2.setY(4.5);
    Vec2.setZ(1.1);
    EXPECT_EQ(Vec1, Vec2);

    // 2 dim
    Vector<double, 2> Vec3 = Vector<double, 2>(2.3,4.5);
    Vector<double, 2> Vec4 = Vector<double, 2>();
    Vec4.setX(2.3);
    Vec4.setY(4.5);
    EXPECT_EQ(Vec3, Vec4);
}

TEST (Vector, floatConstructor) {

    Vector<float, 3> Vec1 = Vector<float, 3>(2.3,4.5, 1.1);
    Vector<float, 3> Vec2 = Vector<float, 3>();
    Vec2.setX(2.3);
    Vec2.setY(4.5);
    Vec2.setZ(1.1);
    EXPECT_EQ(Vec1, Vec2);
}

TEST (Vector, intConstructor) {

    Vector<int, 3> Vec1 = Vector<int, 3>(2,4, 1);
    Vector<int, 3> Vec2 = Vector<int, 3>();
    Vec2.setX(2);
    Vec2.setY(4);
    Vec2.setZ(1);
    EXPECT_EQ(Vec1, Vec2);
}

TEST (Vector, Addition) {

    vector3D Vec1 = vector3D(2.3,4.5, 1.1);
    vector3D Vec2 = vector3D(1,1, 1);
    vector3D result = vector3D(3.3, 5.5, 2.1);
    EXPECT_EQ(Vec1 + Vec2, result);
}

TEST (Vector, Subtruction) {

    vector3D Vec1 = vector3D(2.3,4.5, 1.1);
    vector3D Vec2 = vector3D(1,1, 1);
    vector3D result = vector3D(1.3, 3.5, 0.1);

    EXPECT_EQ(Vec1 - Vec2, result);
}

TEST (Vector, Multiplication) {

    vector3D Vec1 = vector3D(2,4, 5);
    vector3D result = vector3D(4, 8, 10);
    EXPECT_EQ(Vec1 * 2, result);
}

TEST (Vector, Division) {

    vector3D Vec1 = vector3D(2,4, 8);
    vector3D result = vector3D(1, 2, 4);
    EXPECT_EQ(Vec1 / 2, result);
}

TEST (Vector, FailDivision) {

    vector3D Vec1 = vector3D(2,4, 8);

    EXPECT_THROW(Vec1 / 0, std::invalid_argument);
}

TEST (Vector, FailIndexing) {

    vector3D Vec1 = vector3D(2,4, 8);

    EXPECT_THROW(Vec1[6], std::invalid_argument);
}

TEST (Vector, Indexing) {

    vector3D Vec1 = vector3D(2,4,8);

    EXPECT_EQ(Vec1[1], 4);

    Vec1[0] = 3;
    Vec1[1] = 4;
    Vec1[2] = 6;
    vector3D result = vector3D(3, 4, 6);
    EXPECT_EQ(Vec1, result);

}

TEST (Vector, Ostream) {

    std::stringstream ost;
    vector3D vec = vector3D(3.1, 3.1, 7.5);
    ost << vec;
    /* in cout program print double in 10 decimal point fixed precision, but i didnt know how to automaticly test cout*/
    EXPECT_EQ("3.1 3.1 7.5\n", ost.str());
}

TEST (Vector, GetLength) {

    vector3D Vec1 = vector3D(0, 4, 3);
    double length;
    length = Vec1.getLength();
    EXPECT_EQ(length, 5.0);

    Vec1 = vector3D(6,0,0);
    length = Vec1.getLength();
    EXPECT_EQ(length, 6);
}

TEST (Matrix, EmptyConstructor) {
    Matrix<double, 3> A = Matrix<double, 3>();
    Matrix B = Matrix<double, 3>();

    B(0,0) = 1; B(0,1) = 0; B(0,2) = 0;
    B(1,0) = 0; B(1,1) = 1; B(1,2) = 0;
    B(2,0) = 0; B(2,1) = 0; B(2,2) = 1;

    EXPECT_EQ(A, B);
}

TEST (Matrix, Constructor) {

    Matrix<double, 3> A = Matrix3x3(90, 'z');
    Matrix<double, 3> B = Matrix<double, 3>();

    Matrix C = Matrix3x3(0, 'z');
    Matrix D = Matrix<double, 3>();

    B(0,0) = cos(M_PI/2); B(0,1) = -sin(M_PI/2); B(0,2) = 0;
    B(1,0) = sin(M_PI); B(1,1) = cos(M_PI/2); B(1,2) = 0;
    B(2,0) = 0; B(2,1) = 0; B(2,2) = 1;


    D(0,0) = cos(0); D(0,1) = -sin(0); D(0,2) = 0;
    D(1,0) = sin(0); D(1,1) = cos(0); D(1,2) = 0;
    D(2,0) = 0; D(2,1) = 0; D(2,2) = 1;
    EXPECT_EQ(A, B);
    EXPECT_EQ(C, D);

    Matrix<double, 3> E = Matrix3x3(90, 'x');
    B(0,0) = 1; B(0,1) = 0; B(0,2) = 0;
    B(1,0) = 0; B(1,1) = cos(M_PI/2); B(1,2) = -sin(M_PI/2);
    B(2,0) = 0; B(2,1) = sin(M_PI/2); B(2,2) = cos(M_PI/2);
    EXPECT_EQ(E, B);
}

TEST (Matrix, Matrix4x4Constructor) {

    Vector<double, 3> axis = Vector<double, 3>(1, 0, 0);
    Matrix4x4 A = Matrix4x4(0, 0, 0, axis);

    Matrix4x4 B = Matrix4x4();

    B(0,0) = 1; B(0,1) = 0; B(0,2) = 0; B(0,3) = 1;
    B(1,0) = 0; B(1,1) = 1; B(1,2) = 0; B(1,3) = 0;
    B(2,0) = 0; B(2,1) = 0; B(2,2) = 1; B(2,3) = 0;
    B(3,0) = 0; B(3,1) = 0; B(3,2) = 0; B(3,3) = 1;

    A.matrixDisplay();
    std::cout <<"\n";
    B.matrixDisplay();

    EXPECT_EQ(A, B);

}

TEST (Matrix, MultiplicationMatrixVector) {

    Matrix B = Matrix<double, 3>();
    Vector<double, 3> vec = Vector<double, 3>(1,2, 3);
    Vector<double, 3> result = Vector<double, 3>();

    B(0,0) = 1; B(0,1) = 1; B(0,2) = 0;
    B(1,0) = 0; B(1,1) = 2; B(1,2) = 0;
    B(2,0) = 0; B(2,1) = 0; B(2,2) = 3;
    result = B*vec;

    Vector<double, 3> result2 = Vector<double, 3>(3,4,9);
    EXPECT_EQ(result, result2);
}

TEST (Matrix, MultiplicationUnitByMatrixVector) {

    Matrix<double, 3> A = Matrix3x3(0, 'z');
    Vector<double, 3> vec = Vector<double, 3>(1,2, 3);
    Vector<double, 3> result = Vector<double, 3>();
    result = A*vec;
    Vector<double, 3> result2 = Vector<double, 3>(1,2,3);
    EXPECT_EQ(result, result2);
}

TEST (Matrix, MultiplicationMatrixByMatrix) {

    Matrix<double, 3> B = Matrix<double, 3>();
    B(0,0) = 1; B(0,1) = 1; B(0,2) = 0;
    B(1,0) = 0; B(1,1) = 2; B(1,2) = 0;
    B(2,0) = 1; B(2,1) = 0; B(2,2) = 3;

    Matrix<double, 3> A = Matrix<double, 3>();
    A(0,0) = 1; A(0,1) = 4; A(0,2) = 1;
    A(1,0) = 2; A(1,1) = 5; A(1,2) = 0;
    A(2,0) = 3; A(2,1) = 1; A(2,2) = 0;

    Matrix<double, 3> C = Matrix<double, 3>();
    C(0,0) = 2; C(0,1) = 9; C(0,2) = 3;
    C(1,0) = 2; C(1,1) = 12; C(1,2) = 0;
    C(2,0) = 3; C(2,1) = 5; C(2,2) = 0;

    EXPECT_EQ(A*B, C);
}


TEST (Matrix, FailIndexing) {

    Matrix<double, 3> A = Matrix<double, 3>();
    Vector<double, 3> vec = Vector<double, 3>(1,1,3);
    Vector<double, 3> result = Vector<double, 3>();

    EXPECT_THROW(A(2,4), std::invalid_argument);
}

TEST (Cuboid, RotationByDegrees) {

    Matrix3x3 initMat = Matrix3x3();
    vector3D initVec = vector3D();
    Cuboid Adam = Cuboid("../data/cuboidModel.txt", "../data/deck.txt", initMat, initVec);
    initMat= Matrix3x3(90, 'z');
    Cuboid Ewa = Cuboid("../data/cuboidModel.txt", "../data/deck.txt", initMat, initVec);
    Adam.rotationByMatrix(initMat);
    Adam.calculateActualPosition();

    EXPECT_EQ(Adam[0], Ewa[0]);
}

TEST (Cuboid, Ostream) {

    std::stringstream ost;

    Matrix3x3 initMat = Matrix3x3();
    vector3D initVec = vector3D(1,2,3);

    Cuboid Adam = Cuboid("../data/cuboidModel.txt", "../data/deck.txt", initMat, initVec);
    Adam.calculateActualPosition();
    ost << Adam;
    /* cuboid in cout give 10 decimal point fixed precision */
    EXPECT_EQ("1.0000000000 2.0000000000 3.0000000000\n1.0000000000 2.0000000000 3.0000000000\n"
              "1.0000000000 2.0000000000 3.0000000000\n1.0000000000 2.0000000000 3.0000000000\n#\n\n"
              "1.0000000000 2.0000000000 3.0000000000\n1.0000000000 2.0000000000 3.0000000000\n"
              "1.0000000000 2.0000000000 3.0000000000\n1.0000000000 2.0000000000 3.0000000000\n#\n\n"
              "1.0000000000 2.0000000000 3.0000000000\n1.0000000000 2.0000000000 3.0000000000\n"
              "1.0000000000 2.0000000000 3.0000000000\n1.0000000000 2.0000000000 3.0000000000\n#\n\n"
              "1.0000000000 2.0000000000 3.0000000000\n1.0000000000 2.0000000000 3.0000000000\n"
              "1.0000000000 2.0000000000 3.0000000000\n1.0000000000 2.0000000000 3.0000000000\n#\n\n"
              "1.0000000000 2.0000000000 3.0000000000\n1.0000000000 2.0000000000 3.0000000000\n"
              "1.0000000000 2.0000000000 3.0000000000\n1.0000000000 2.0000000000 3.0000000000\n#\n\n"

    , ost.str());
}


TEST (Cuboid, translateCuboid) {
    Matrix3x3 initMat = Matrix3x3();
    vector3D initVec = vector3D(-1,1,2);
    Cuboid Adam = Cuboid("../data/cuboidModel.txt", "../data/deck.txt", initMat, initVec);
    vector3D result = Adam[0];
    Adam.translationByVector(initVec);
    Adam.calculateActualPosition();

    result = result + initVec;

    EXPECT_EQ(Adam.getPosition(), result);
}

TEST (Drone, constructorsAndIndexing) {

    vector3D translation = vector3D();
    Matrix3x3 orientation = Matrix3x3();
    Drone drone1 = Drone("../data/drone0_deck.txt", "../data/drone0_rotor0.txt",
                         "../data/drone0_rotor1.txt", "../data/drone0_rotor2.txt",
                         "../data/drone0_rotor3.txt", translation, orientation);

    translation = vector3D(10,100,1000);
    Drone drone2 = Drone("../data/drone0_deck.txt", "../data/drone0_rotor0.txt",
                         "../data/drone0_rotor1.txt", "../data/drone0_rotor2.txt",
                         "../data/drone0_rotor3.txt", translation, orientation);

    drone1.translateDrone(translation);
    drone1.calculatePosition();

    EXPECT_EQ(drone1[3].getPosition(), drone2[3].getPosition());
    EXPECT_EQ(drone1.getDeck().getPosition(), drone1.getDeck().getPosition());

}

TEST (Hex, constructorsAndIndexingAndReadModel) {

    vector3D result = vector3D(-2, -3.46410161514, -1);
    HexagonalPrism hex = HexagonalPrism("../../data/hexagonalPrismModel.txt");
    hex.readModelVerticesPosition();

    EXPECT_EQ(hex[0], result);
    result = vector3D(2, -3.46410161514, -1);
    EXPECT_EQ(hex[1], result);
    result = vector3D(4, 0, -1);
    EXPECT_EQ(hex[2], result);

    result = vector3D(-4, 0, 1);
    EXPECT_EQ(hex[11], result);
}

TEST (Hex, TestOperatorPlusEQualAndMultiplyEqual) {

    vector3D tr = vector3D(1, 2, 3);
    Matrix3x3 A = Matrix3x3(90, 'x');
    Matrix3x3 B = Matrix3x3(90, 'y');
    HexagonalPrism hex = HexagonalPrism("../../data/hexagonalPrismModel.txt");
    hex += tr;
    hex *= A;
    EXPECT_EQ(hex.getOrientation(), A);
    EXPECT_EQ(hex.getPosition(), tr);
    hex += tr;
    hex *= B;
    tr = tr + tr;
    A = B * A;
    EXPECT_EQ(hex.getOrientation(), A);
    EXPECT_EQ(hex.getPosition(), tr);
}