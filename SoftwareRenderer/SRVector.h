#ifndef __SRVECTOR_H__
#define __SRVECTOR_H__

#include <cmath>
#include <Windows.h>
#include "SRMatrix4x4.h"

class SRVector3{
public:
    float x;
    float y;
    float z;
    
    SRVector3(){
        toZero();
    }

    SRVector3(float a, float b, float c):x(a),y(b),z(c){}
    
    SRVector3(const SRVector3& vec3) :x(vec3.x), y(vec3.y), z(vec3.z){}

    // 为了使用连续赋值，重载的=号需要返回自己的引用
    SRVector3& operator=(const SRVector3& vec3){
        x = vec3.x;
        y = vec3.y;
        z = vec3.z;
        
        return *this;
    }

    SRVector3 operator-() const{
        return SRVector3(-x, -y, -z);
    }

    SRVector3 operator+(const SRVector3& rhs) const{
        return SRVector3(x + rhs.x, y + rhs.y, z + rhs.z);
    }

    SRVector3 operator-(const SRVector3& rhs) const{
        return SRVector3(x - rhs.x, y - rhs.y, z - rhs.z);
    }

    SRVector3 operator*(float rate) const{
        return SRVector3(x * rate, y * rate, z * rate);
    }

    float operator*(const SRVector3& rhs) const{
        return dot(rhs);
    }
    
    float dot(const SRVector3& vec3) const{
        return x*vec3.x + y*vec3.y + z*vec3.z;
    }

    SRVector3 cross(const SRVector3& vec3) const{
        return SRVector3(
            y*vec3.z - z*vec3.y,
            z*vec3.x - x*vec3.z,
            x*vec3.y - y*vec3.x
            );
    }

    void toNormalize(){
        float magSq = x*x + y*y + z*z;
        if (magSq > 0.0f){
            float oneOverMag = 1.0f / sqrtf(magSq);
            x *= oneOverMag;
            y *= oneOverMag;
            z *= oneOverMag;
        }
    }

    void toZero(){
        x = y = z = 0.0f;
    }

    static const SRVector3 zero(){
        return SRVector3(0.0f, 0.0f, 0.0f);
    }

    float mag() const{
        return sqrtf(x*x + y*y + z*z);
    }

    float distanceTo(SRVector3 vec3) const{
        return (*this - vec3).mag();
    }

    static float distanceBetween(const SRVector3& vec31, const SRVector3& vec32){
        return (vec31 - vec32).mag();
    }

    SRVector3 operator*(const SRMatrix4x4& mat){
        return SRVector3(
            mat[0] * x + mat[4] * y + mat[8] * z + mat[12],
            mat[1] * x + mat[5] * y + mat[9] * z + mat[13],
            mat[2] * x + mat[6] * y + mat[10] * z + mat[14]
            );
    }
};

#endif