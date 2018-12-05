#ifndef __SRVECTOR_H__
#define __SRVECTOR_H_

#include<cmath>

class Vector3{
public:
    float x;
    float y;
    float z;
    
    Vector3(){
        Vector3(zero());
    }

    Vector3(float a, float b, float c):x(a),y(b),z(c){}
    
    Vector3(const Vector3& vec3) :x(vec3.x), y(vec3.y), z(vec3.z){}

    // 为了使用连续赋值，重载的=号需要返回自己的引用
    Vector3& operator=(const Vector3& vec3){
        x = vec3.x;
        y = vec3.y;
        z = vec3.z;
        
        return *this;
    }

    Vector3 operator-() const{
        return Vector3(-x, -y, -z);
    }

    Vector3 operator+(const Vector3& rhs) const{
        return Vector3(x + rhs.x, y + rhs.y, z + rhs.z);
    }

    Vector3 operator-(const Vector3& rhs) const{
        return Vector3(x - rhs.x, y - rhs.y, z - rhs.z);
    }

    Vector3 operator*(float rate) const{
        return Vector3(x * rate, y * rate, z * rate);
    }

    static Vector3 operator*(float rate, Vector3 vec3){
        return vec3 * rate;
    }

    float operator*(const Vector3& rhs) const{
        return dot(rhs);
    }
    
    float dot(const Vector3& vec3) const{
        return x*vec3.x + y*vec3.y + z*vec3.z;
    }

    Vector3 cross(const Vector3& vec3) const{
        return Vector3(
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

    static const Vector3 zero(){
        return Vector3(0.0f, 0.0f, 0.0f);
    }

    float mag() const{
        return sqrtf(x*x + y*y + z*z);
    }

    float distanceTo(Vector3 vec3) const{
        return (*this - vec3).mag();
    }

    static float distanceBetween(const Vector3& vec31, const Vector3& vec32){
        return (vec31 - vec32).mag();
    }
};

extern const Vector3 gZeroVector3;
#endif