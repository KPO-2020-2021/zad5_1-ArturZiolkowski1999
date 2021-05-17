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

//TEST (Cuboid, EmptyConstructor) {
//
//    Cuboid Adam = Cuboid();
//    Cuboid Ewa = Cuboid();
//
//    vector3D Vec = vector3D();
//
//    for(int i = 0; i < VERTICES_NUMBER_OF_CUBOID; i++){
//        Adam[i] = Vec;
//    }
//
//    EXPECT_EQ(Adam, Ewa);
//}
//
//TEST (Cuboid, ConstructorWithVerticesInOrder) {
//
//    vector3D Ver0 = vector3D(0,0,1);
//    vector3D Ver1 = vector3D(5,0,1);
//    vector3D Ver2 = vector3D(5,0,4);
//    vector3D Ver3 = vector3D(0,0,4);
//
//    vector3D Ver4 = vector3D(0,7,1);
//    vector3D Ver5 = vector3D(5,7,1);
//    vector3D Ver6 = vector3D(5,7,4);
//    vector3D Ver7 = vector3D(0,7,4);
//
//    vector3D vertices[VERTICES_NUMBER_OF_CUBOID] = {Ver0, Ver1, Ver2, Ver3, Ver4, Ver5, Ver6, Ver7};
//    Cuboid Adam = Cuboid(vertices);
//    Cuboid Ewa = Cuboid();
//
//    for(int i = 0; i < VERTICES_NUMBER_OF_CUBOID; i++){
//        Ewa[i] = vertices[i];
//    }
//
//    EXPECT_EQ(Adam, Ewa);
//}
//
//
//TEST (Cuboid, TranslationByWector) {
//    vector3D Ver0 = vector3D(0,0,1);
//    vector3D Ver1 = vector3D(5,0,1);
//    vector3D Ver2 = vector3D(5,0,4);
//    vector3D Ver3 = vector3D(0,0,4);
//
//    vector3D Ver4 = vector3D(0,7,1);
//    vector3D Ver5 = vector3D(5,7,1);
//    vector3D Ver6 = vector3D(5,7,4);
//    vector3D Ver7 = vector3D(0,7,4);
//
//    vector3D vertices[VERTICES_NUMBER_OF_CUBOID] = {Ver0, Ver1, Ver2, Ver3, Ver4, Ver5, Ver6, Ver7};
//    Cuboid Adam = Cuboid(vertices);
//    vector3D translation = vector3D(1, 2, 3);
//
//    Adam.translationByVector(translation);
//    Cuboid Ewa = Cuboid();
//
//    for(int i = 0; i < VERTICES_NUMBER_OF_CUBOID; i++){
//        Ewa[i] = (vertices[i] + translation);
//    }
//    EXPECT_EQ(Adam, Ewa);
//}
//
//TEST (Cuboid, RotationByDegrees) {
//
//    vector3D Ver0 = vector3D(0,0,1);
//    vector3D Ver1 = vector3D(5,0,1);
//    vector3D Ver2 = vector3D(5,0,4);
//    vector3D Ver3 = vector3D(0,0,4);
//
//    vector3D Ver4 = vector3D(0,7,1);
//    vector3D Ver5 = vector3D(5,7,1);
//    vector3D Ver6 = vector3D(5,7,4);
//    vector3D Ver7 = vector3D(0,7,4);
//
//    vector3D vertices[VERTICES_NUMBER_OF_CUBOID] = {Ver0, Ver1, Ver2, Ver3, Ver4, Ver5, Ver6, Ver7};
//    Cuboid Adam = Cuboid(vertices);
//    Matrix3x3 rotation = Matrix3x3(360, 'z');
//    Adam.rotationByMatrix(rotation);
//
//    Cuboid Ewa = Cuboid();
//
//    for(int i = 0; i < VERTICES_NUMBER_OF_CUBOID; i++){
//        Ewa[i] = (rotation * vertices[i]);
//    }
//
//    EXPECT_EQ(Adam, Ewa);
//}
//
//TEST (Cuboid, Ostream) {
//
//    std::stringstream ost;
//    vector3D Ver0 = vector3D(0,0,1);
//    vector3D Ver1 = vector3D(5,0,1);
//    vector3D Ver2 = vector3D(5,0,4);
//    vector3D Ver3 = vector3D(0,0,4);
//
//    vector3D Ver4 = vector3D(0,7,1);
//    vector3D Ver5 = vector3D(5,7,1);
//    vector3D Ver6 = vector3D(5,7,4);
//    vector3D Ver7 = vector3D(0,7,4);
//
//    vector3D vertices[VERTICES_NUMBER_OF_CUBOID] = {Ver0, Ver1, Ver2, Ver3, Ver4, Ver5, Ver6, Ver7};
//    Cuboid Adam = Cuboid(vertices);
//    ost << Adam;
//    /* cuboid in cout give 10 decimal point fixed precision */
//    EXPECT_EQ("2.5000000000 0.0000000000 2.5000000000\n5.0000000000 0.0000000000 4.0000000000"
//              "\n5.0000000000 7.0000000000 4.0000000000\n2.5000000000 7.0000000000 2.5000000000\n#\n\n"
//              "2.5000000000 0.0000000000 2.5000000000\n5.0000000000 0.0000000000 1.0000000000\n"
//              "5.0000000000 7.0000000000 1.0000000000\n2.5000000000 7.0000000000 2.5000000000\n#\n""\n"
//              "2.5000000000 0.0000000000 2.5000000000\n0.0000000000 0.0000000000 1.0000000000\n"
//              "0.0000000000 7.0000000000 1.0000000000\n2.5000000000 7.0000000000 2.5000000000\n#\n\n"
//              "2.5000000000 0.0000000000 2.5000000000\n0.0000000000 0.0000000000 4.0000000000\n"
//              "0.0000000000 7.0000000000 4.0000000000\n2.5000000000 7.0000000000 2.5000000000\n#\n\n"
//              "2.5000000000 0.0000000000 2.5000000000\n5.0000000000 0.0000000000 4.0000000000\n"
//              "5.0000000000 7.0000000000 4.0000000000\n2.5000000000 7.0000000000 2.5000000000\n#\n\n"
//    , ost.str());
//}
//
//TEST (Cuboid, GetSidesLength) {
//
//    vector3D Ver0 = vector3D(0,0,1);
//    vector3D Ver1 = vector3D(5,0,1);
//    vector3D Ver2 = vector3D(5,0,4);
//    vector3D Ver3 = vector3D(0,0,4);
//
//    vector3D Ver4 = vector3D(0,7,1);
//    vector3D Ver5 = vector3D(5,7,1);
//    vector3D Ver6 = vector3D(5,7,4);
//    vector3D Ver7 = vector3D(0,7,4);
//
//    vector3D vertices[VERTICES_NUMBER_OF_CUBOID] = {Ver0, Ver1, Ver2, Ver3, Ver4, Ver5, Ver6, Ver7};
//    Cuboid Adam = Cuboid(vertices);
//    Adam.calculateSidesLength();
//
//
//    EXPECT_NEAR(Adam.getSideLength(0) , Adam.getSideLength(2), 0.00000001);
//    EXPECT_NEAR(Adam.getSideLength(0) , 5.0 , 0.00000001);
//
//    EXPECT_NEAR(Adam.getSideLength(4) , Adam.getSideLength(5), 0.00000001);
//    EXPECT_NEAR(Adam.getSideLength(5) , 3.0, 0.00000001);
//    EXPECT_NEAR(Adam.getSideLength(10) , Adam.getSideLength(11), 0.00000001);
//    EXPECT_NEAR(Adam.getSideLength(10) , 7.0, 0.00000001);
//}
//
//TEST (Cuboid, Indexing) {
//
//    vector3D Ver0 = vector3D(0,0,1);
//    vector3D Ver1 = vector3D(5,0,1);
//    vector3D Ver2 = vector3D(5,0,4);
//    vector3D Ver3 = vector3D(0,0,4);
//
//    vector3D Ver4 = vector3D(0,7,1);
//    vector3D Ver5 = vector3D(5,7,1);
//    vector3D Ver6 = vector3D(5,7,4);
//    vector3D Ver7 = vector3D(0,7,4);
//
//    vector3D vertices[VERTICES_NUMBER_OF_CUBOID] = {Ver0, Ver1, Ver2, Ver3, Ver4, Ver5, Ver6, Ver7};
//    Cuboid Adam = Cuboid(vertices);
//    vector3D result= vector3D(1.2, 1.3, 1.4);
//    Adam[0] = result;
//
//EXPECT_EQ(Adam[0], result);
//}
//
//TEST (Cuboid, calculateCenterOfMass) {
//    vector3D Ver0 = vector3D(-1,-1,0);
//    vector3D Ver1 = vector3D(1,-1,0);
//    vector3D Ver2 = vector3D(1,-1,2);
//    vector3D Ver3 = vector3D(-1,-1,2);
//
//    vector3D Ver4 = vector3D(-1,1,0);
//    vector3D Ver5 = vector3D(1,1,0);
//    vector3D Ver6 = vector3D(1,1,2);
//    vector3D Ver7 = vector3D(-1,1,2);
//
//    vector3D vertices[VERTICES_NUMBER_OF_CUBOID] = {Ver0, Ver1, Ver2, Ver3, Ver4, Ver5, Ver6, Ver7};
//    Cuboid Adam = Cuboid(vertices);
//
//    vector3D result = vector3D(0,0,1);
//
//    EXPECT_EQ(Adam.getCenterOfMass(), result);
//}
//
//TEST (Drone, constructorsAndIndexing) {
//
//    vector3D translation = vector3D(10,100,1000);
//    Drone drone1 = Drone();
//    Drone drone2 = Drone(translation);
//
//    double xMax = 3, xMin = -3, yMax = 3, yMin = -3, zMax = 1, zMin = -1;
//
//    vector3D Ver0 = vector3D(xMin,yMin,zMin);
//    vector3D Ver1 = vector3D(xMax,yMin,zMin);
//    vector3D Ver2 = vector3D(xMax,yMin,zMax);
//    vector3D Ver3 = vector3D(xMin,yMin,zMax);
//
//    vector3D Ver4 = vector3D(xMin,yMax,zMin);
//    vector3D Ver5 = vector3D(xMax,yMax,zMin);
//    vector3D Ver6 = vector3D(xMax,yMax,zMax);
//    vector3D Ver7 = vector3D(xMin,yMax,zMax);
//
//    vector3D vertices[VERTICES_NUMBER_OF_CUBOID] = {Ver0, Ver1, Ver2, Ver3, Ver4, Ver5, Ver6, Ver7};
//    Cuboid result = Cuboid(vertices);
//    EXPECT_EQ(drone1[4], result);
//    result.translationByVector(translation);
//    EXPECT_EQ(drone2[4], result);
//
//    for(int i = 0; i < NUMBER_OF_ROTORS; ++i){
//        switch (i) {
//            case 0:
//                xMax = -2; xMin = -4; yMax = 4; yMin = 2; zMax = 2; zMin = 1.2;
//                break;
//            case 1:
//                xMax = 4; xMin = 2; yMax = 4; yMin = 2; zMax = 2; zMin = 1.2;
//                break;
//            case 2:
//                xMax = 4; xMin = 2; yMax = -2; yMin = -4; zMax = 2; zMin = 1.2;
//                break;
//            case 3:
//                xMax = -2; xMin = -4; yMax = -2; yMin = -4; zMax = 2; zMin = 1.2;
//                break;
//        }
//        Ver0 = vector3D(xMin,yMin,zMin);
//        Ver1 = vector3D(xMax,yMin,zMin);
//        Ver2 = vector3D(xMax,yMin,zMax);
//        Ver3 = vector3D(xMin,yMin,zMax);
//        Ver4 = vector3D(xMin,yMax,zMin);
//        Ver5 = vector3D(xMax,yMax,zMin);
//        Ver6 = vector3D(xMax,yMax,zMax);
//        Ver7 = vector3D(xMin,yMax,zMax);
//
//        vertices[0] = Ver0; vertices[1] = Ver1; vertices[2] = Ver2; vertices[3] = Ver3,
//                vertices[4] = Ver4; vertices[5] = Ver5; vertices[6] = Ver6; vertices[7] = Ver7;
//                result = Cuboid(vertices);
//        EXPECT_EQ(drone1[i], result);
//        result.translationByVector(translation);
//        EXPECT_EQ(drone2[i], result);
//    }
//}

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