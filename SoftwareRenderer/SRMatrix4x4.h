#ifndef __SRMATRIX4X4_H__
#define __SRMATRIX4X4_H__
#include<cmath>
//默认是列主序，对标OpenGL
class Matrix4x4
{
public:
    Matrix4x4(){
        toIdentity();
    }

    Matrix4x4(  float m01, float m02, float m03, float m04,
                float m05, float m06, float m07, float m08,
                float m09, float m10, float m11, float m12,
                float m13, float m14, float m15, float m16){
        mat[0] = m01;
        mat[1] = m02;
        mat[2] = m03;
        mat[3] = m04;
        mat[4] = m05;
        mat[5] = m06;
        mat[6] = m07;
        mat[7] = m08;
        mat[8] = m09;
        mat[9] = m10;
        mat[10] = m11;
        mat[11] = m12;
        mat[12] = m13;
        mat[13] = m14;
        mat[14] = m15;
        mat[15] = m16;
    }

    Matrix4x4(const Matrix4x4& matrix){
        for(int i = 0; i < 16; ++i){
            mat[i] = matrix[i];
        }
    }

    Matrix4x4 operator*(const Matrix4x4& matrix) const{
        return Matrix4x4(
            mat[0] * matrix[0]  + mat[4] * matrix[1]  + mat[8] * matrix[2]  + mat[12] * matrix[3],
            mat[0] * matrix[4]  + mat[4] * matrix[5]  + mat[8] * matrix[6]  + mat[12] * matrix[7],
            mat[0] * matrix[8]  + mat[4] * matrix[9]  + mat[8] * matrix[10] + mat[12] * matrix[11],
            mat[0] * matrix[12] + mat[4] * matrix[13] + mat[8] * matrix[14] + mat[12] * matrix[15],

            mat[1] * matrix[0]  + mat[5] * matrix[1]  + mat[9] * matrix[2]  + mat[13] * matrix[3],
            mat[1] * matrix[4]  + mat[5] * matrix[5]  + mat[9] * matrix[6]  + mat[13] * matrix[7],
            mat[1] * matrix[8]  + mat[5] * matrix[9]  + mat[9] * matrix[10] + mat[13] * matrix[11],
            mat[1] * matrix[12] + mat[5] * matrix[13] + mat[9] * matrix[14] + mat[13] * matrix[15],

            mat[2] * matrix[0]  + mat[6] * matrix[1]  + mat[10] * matrix[2]  + mat[14] * matrix[3],
            mat[2] * matrix[4]  + mat[6] * matrix[5]  + mat[10] * matrix[6]  + mat[14] * matrix[7],
            mat[2] * matrix[8]  + mat[6] * matrix[9]  + mat[10] * matrix[10] + mat[14] * matrix[11],
            mat[2] * matrix[12] + mat[6] * matrix[13] + mat[10] * matrix[14] + mat[14] * matrix[15],

            mat[3] * matrix[0]  + mat[7] * matrix[1]  + mat[11] * matrix[2]  + mat[15] * matrix[3],
            mat[3] * matrix[4]  + mat[7] * matrix[5]  + mat[11] * matrix[6]  + mat[15] * matrix[7],
            mat[3] * matrix[8]  + mat[7] * matrix[9]  + mat[11] * matrix[10] + mat[15] * matrix[11],
            mat[3] * matrix[12] + mat[7] * matrix[13] + mat[11] * matrix[14] + mat[15] * matrix[15]
            );
    }

    Matrix4x4 operator+(const Matrix4x4& matrix) const{
        return Matrix4x4(
            mat[0]  + matrix[0],
            mat[1]  + matrix[1],
            mat[2]  + matrix[2],
            mat[3]  + matrix[3],
            mat[4]  + matrix[4],
            mat[5]  + matrix[5],
            mat[6]  + matrix[6],
            mat[7]  + matrix[7],
            mat[8]  + matrix[8],
            mat[9]  + matrix[9],
            mat[10] + matrix[10],
            mat[11] + matrix[11],
            mat[12] + matrix[12],
            mat[13] + matrix[13],
            mat[14] + matrix[14],
            mat[15] + matrix[15]
            );
    }

    Matrix4x4 operator-() const{
        return Matrix4x4(
            -mat[0],
            -mat[1],
            -mat[2],
            -mat[3],
            -mat[4],
            -mat[5],
            -mat[6],
            -mat[7],
            -mat[8],
            -mat[9],
            -mat[10],
            -mat[11],
            -mat[12],
            -mat[13],
            -mat[14],
            -mat[15]
            );
    }

    Matrix4x4 operator-(const Matrix4x4& matrix) const{
        return Matrix4x4(*this + (-matrix));
    }

    float operator[](int index) const{
        return mat[index];
    }

    void toZero();
    void toIdentity();

private:
    float mat[16];
};

void Matrix4x4::toZero(){
    mat[0] = 0.0f;
    mat[1] = 0.0f;
    mat[2] = 0.0f;
    mat[3] = 0.0f;
    mat[4] = 0.0f;
    mat[5] = 0.0f;
    mat[6] = 0.0f;
    mat[7] = 0.0f;
    mat[8] = 0.0f;
    mat[9] = 0.0f;
    mat[10] = 0.0f;
    mat[11] = 0.0f;
    mat[12] = 0.0f;
    mat[13] = 0.0f;
    mat[14] = 0.0f;
    mat[15] = 0.0f;
}

void Matrix4x4::toIdentity(){
    toZero();
    mat[0] = 1.0f;
    mat[5] = 1.0f;
    mat[10] = 1.0f;
    mat[15] = 1.0f;
}

#endif