#include "gtest/gtest.h"
#include "Matrix3x3.h"
#include "Matrix4x4.h"
#include <iostream>
#include <utility>
#include "Cuboid.h"
#include "Constants.h"
#include "Vector.h"



TEST (Vector, EmptyConstructor) {

    // 3 dim
    Vector<double, 3> Vec1 = Vector<double, 3>();
    Vector<double, 3> Vec2 = Vector<double, 3>();
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

    Vector<double, 3> Vec1 = Vector<double, 3>(2.3,4.5, 1.1);
    Vector<double, 3> Vec2 = Vector<double, 3>(1,1, 1);
    Vector<double, 3> result = Vector<double, 3>(3.3, 5.5, 2.1);
    EXPECT_EQ(Vec1 + Vec2, result);
}

TEST (Vector, Subtruction) {

    Vector<double, 3> Vec1 = Vector<double, 3>(2.3,4.5, 1.1);
    Vector<double, 3> Vec2 = Vector<double, 3>(1,1, 1);
    Vector<double, 3> result = Vector<double, 3>(1.3, 3.5, 0.1);

    EXPECT_EQ(Vec1 - Vec2, result);
}

TEST (Vector, Multiplication) {

    Vector<double, 3> Vec1 = Vector<double, 3>(2,4, 5);
    Vector<double, 3> result = Vector<double, 3>(4, 8, 10);
    EXPECT_EQ(Vec1 * 2, result);
}

TEST (Vector, Division) {

    Vector<double, 3> Vec1 = Vector<double, 3>(2,4, 8);
    Vector<double, 3> result = Vector<double, 3>(1, 2, 4);
    EXPECT_EQ(Vec1 / 2, result);
}

TEST (Vector, FailDivision) {

    Vector<double, 3> Vec1 = Vector<double, 3>(2,4, 8);

    EXPECT_THROW(Vec1 / 0, std::invalid_argument);
}

TEST (Vector, FailIndexing) {

    Vector<double, 3> Vec1 = Vector<double, 3>(2,4, 8);

    EXPECT_THROW(Vec1[6], std::invalid_argument);
}

TEST (Vector, Indexing) {

    Vector<double, 3> Vec1 = Vector<double, 3>(2,4,8);

    EXPECT_EQ(Vec1[1], 4);

    Vec1[0] = 3;
    Vec1[1] = 4;
    Vec1[2] = 6;
    Vector<double, 3> result =Vector<double, 3>(3, 4, 6);
    EXPECT_EQ(Vec1, result);

}

TEST (Vector, Ostream) {

    std::stringstream ost;
    Vector<double, 3> vec = Vector<double, 3>(3.1, 3.1, 7.5);
    ost << vec;
    /* in cout program print double in 10 decimal point fixed precision, but i didnt know how to automaticly test cout*/
    EXPECT_EQ("3.1 3.1 7.5\n", ost.str());
}

TEST (Vector, GetLength) {

    Vector<double, 3> Vec1 = Vector<double, 3>(0, 4, 3);
    double length;
    length = Vec1.getLength();
    EXPECT_EQ(length, 5.0);

    Vec1 = Vector<double, 3>(6,0,0);
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

TEST (Cuboid, EmptyConstructor) {

    Cuboid<double> Adam = Cuboid<double>();
    Cuboid<double> Ewa = Cuboid<double>();

    Vector<double, 3> Vec = Vector<double, 3>();

    for(int i = 0; i < VERTICES_NUMBER; i++){
        Adam[i] = Vec;
    }

    EXPECT_EQ(Adam, Ewa);
}

TEST (Cuboid, ConstructorWithVerticesInOrder) {

    Vector<double, 3> Ver0 = Vector<double, 3>(0,0,1);
    Vector<double, 3> Ver1 = Vector<double, 3>(5,0,1);
    Vector<double, 3> Ver2 = Vector<double, 3>(5,0,4);
    Vector<double, 3> Ver3 = Vector<double, 3>(0,0,4);

    Vector<double, 3> Ver4 = Vector<double, 3>(0,7,1);
    Vector<double, 3> Ver5 = Vector<double, 3>(5,7,1);
    Vector<double, 3> Ver6 = Vector<double, 3>(5,7,4);
    Vector<double, 3> Ver7 = Vector<double, 3>(0,7,4);

    Vector<double, 3> vertices[VERTICES_NUMBER] = {Ver0, Ver1, Ver2, Ver3, Ver4, Ver5, Ver6, Ver7};
    Cuboid<double> Adam = Cuboid<double>(vertices);
    Cuboid<double> Ewa = Cuboid<double>();

    for(int i = 0; i < VERTICES_NUMBER; i++){
        Ewa[i] = vertices[i];
    }

    EXPECT_EQ(Adam, Ewa);
}


TEST (Cuboid, TranslationByWector) {
    Vector<double, 3> Ver0 = Vector<double, 3>(0,0,1);
    Vector<double, 3> Ver1 = Vector<double, 3>(5,0,1);
    Vector<double, 3> Ver2 = Vector<double, 3>(5,0,4);
    Vector<double, 3> Ver3 = Vector<double, 3>(0,0,4);

    Vector<double, 3> Ver4 = Vector<double, 3>(0,7,1);
    Vector<double, 3> Ver5 = Vector<double, 3>(5,7,1);
    Vector<double, 3> Ver6 = Vector<double, 3>(5,7,4);
    Vector<double, 3> Ver7 = Vector<double, 3>(0,7,4);

    Vector<double, 3> vertices[VERTICES_NUMBER] = {Ver0, Ver1, Ver2, Ver3, Ver4, Ver5, Ver6, Ver7};
    Cuboid<double> Adam = Cuboid<double>(vertices);
    Vector<double, 3> translation = Vector<double, 3>(1, 2, 3);

    Adam.translationByVector(translation);
    Cuboid<double> Ewa = Cuboid<double>();

    for(int i = 0; i < VERTICES_NUMBER; i++){
        Ewa[i] = (vertices[i] + translation);
    }
    EXPECT_EQ(Adam, Ewa);
}

TEST (Cuboid, RotationByDegrees) {

    Vector<double, 3> Ver0 = Vector<double, 3>(0,0,1);
    Vector<double, 3> Ver1 = Vector<double, 3>(5,0,1);
    Vector<double, 3> Ver2 = Vector<double, 3>(5,0,4);
    Vector<double, 3> Ver3 = Vector<double, 3>(0,0,4);

    Vector<double, 3> Ver4 = Vector<double, 3>(0,7,1);
    Vector<double, 3> Ver5 = Vector<double, 3>(5,7,1);
    Vector<double, 3> Ver6 = Vector<double, 3>(5,7,4);
    Vector<double, 3> Ver7 = Vector<double, 3>(0,7,4);

    Vector<double, 3> vertices[VERTICES_NUMBER] = {Ver0, Ver1, Ver2, Ver3, Ver4, Ver5, Ver6, Ver7};
    Cuboid<double> Adam = Cuboid<double>(vertices);
    Matrix3x3 rotation = Matrix3x3(360, 'z');
    Adam.rotationByMatrix(rotation);

    Cuboid<double> Ewa = Cuboid<double>();

    for(int i = 0; i < VERTICES_NUMBER; i++){
        Ewa[i] = (rotation * vertices[i]);
    }

    EXPECT_EQ(Adam, Ewa);
}

TEST (Cuboid, Ostream) {

    std::stringstream ost;
    Vector<double, 3> Ver0 = Vector<double, 3>(0,0,1);
    Vector<double, 3> Ver1 = Vector<double, 3>(5,0,1);
    Vector<double, 3> Ver2 = Vector<double, 3>(5,0,4);
    Vector<double, 3> Ver3 = Vector<double, 3>(0,0,4);

    Vector<double, 3> Ver4 = Vector<double, 3>(0,7,1);
    Vector<double, 3> Ver5 = Vector<double, 3>(5,7,1);
    Vector<double, 3> Ver6 = Vector<double, 3>(5,7,4);
    Vector<double, 3> Ver7 = Vector<double, 3>(0,7,4);

    Vector<double, 3> vertices[VERTICES_NUMBER] = {Ver0, Ver1, Ver2, Ver3, Ver4, Ver5, Ver6, Ver7};
    Cuboid<double> Adam = Cuboid<double>(vertices);
    ost << Adam;
    /* cuboid in cout give 10 decimal point fixed precision */
    EXPECT_EQ("0.0000000000 0.0000000000 1.0000000000\n"
              "5.0000000000 0.0000000000 1.0000000000\n"
              "5.0000000000 0.0000000000 4.0000000000\n"
              "0.0000000000 0.0000000000 4.0000000000\n"
              "0.0000000000 0.0000000000 4.0000000000\n"
              "0.0000000000 0.0000000000 1.0000000000\n"
              "0.0000000000 7.0000000000 1.0000000000\n"
              "5.0000000000 7.0000000000 1.0000000000\n"
              "5.0000000000 0.0000000000 1.0000000000\n"
              "5.0000000000 7.0000000000 1.0000000000\n"
              "5.0000000000 7.0000000000 1.0000000000\n"
              "5.0000000000 7.0000000000 4.0000000000\n"
              "5.0000000000 0.0000000000 4.0000000000\n"
              "5.0000000000 7.0000000000 4.0000000000\n"
              "0.0000000000 7.0000000000 4.0000000000\n"
              "0.0000000000 0.0000000000 4.0000000000\n"
              "0.0000000000 7.0000000000 4.0000000000\n"
              "0.0000000000 7.0000000000 1.0000000000\n"
              "0.0000000000 0.0000000000 1.0000000000\n"
    , ost.str());
}

TEST (Cuboid, GetSidesLength) {

    Vector<double, 3> Ver0 = Vector<double, 3>(0,0,1);
    Vector<double, 3> Ver1 = Vector<double, 3>(5,0,1);
    Vector<double, 3> Ver2 = Vector<double, 3>(5,0,4);
    Vector<double, 3> Ver3 = Vector<double, 3>(0,0,4);

    Vector<double, 3> Ver4 = Vector<double, 3>(0,7,1);
    Vector<double, 3> Ver5 = Vector<double, 3>(5,7,1);
    Vector<double, 3> Ver6 = Vector<double, 3>(5,7,4);
    Vector<double, 3> Ver7 = Vector<double, 3>(0,7,4);

    Vector<double, 3> vertices[VERTICES_NUMBER] = {Ver0, Ver1, Ver2, Ver3, Ver4, Ver5, Ver6, Ver7};
    Cuboid<double> Adam = Cuboid<double>(vertices);
    Adam.calculateSidesLength();


    EXPECT_NEAR(Adam.getSideLength(0) , Adam.getSideLength(2), 0.00000001);
    EXPECT_NEAR(Adam.getSideLength(0) , 5.0 , 0.00000001);

    EXPECT_NEAR(Adam.getSideLength(4) , Adam.getSideLength(5), 0.00000001);
    EXPECT_NEAR(Adam.getSideLength(5) , 3.0, 0.00000001);
    EXPECT_NEAR(Adam.getSideLength(10) , Adam.getSideLength(11), 0.00000001);
    EXPECT_NEAR(Adam.getSideLength(10) , 7.0, 0.00000001);
}

TEST (Cuboid, Indexing) {

    Vector<double, 3> Ver0 = Vector<double, 3>(0,0,1);
    Vector<double, 3> Ver1 = Vector<double, 3>(5,0,1);
    Vector<double, 3> Ver2 = Vector<double, 3>(5,0,4);
    Vector<double, 3> Ver3 = Vector<double, 3>(0,0,4);

    Vector<double, 3> Ver4 = Vector<double, 3>(0,7,1);
    Vector<double, 3> Ver5 = Vector<double, 3>(5,7,1);
    Vector<double, 3> Ver6 = Vector<double, 3>(5,7,4);
    Vector<double, 3> Ver7 = Vector<double, 3>(0,7,4);

    Vector<double, 3> vertices[VERTICES_NUMBER] = {Ver0, Ver1, Ver2, Ver3, Ver4, Ver5, Ver6, Ver7};
    Cuboid<double> Adam = Cuboid<double>(vertices);
    Vector<double, 3> result= Vector<double, 3>(1.2, 1.3, 1.4);
    Adam[0] = result;

EXPECT_EQ(Adam[0], result);
}