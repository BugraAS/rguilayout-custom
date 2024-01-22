#pragma once

#include "raylib.h"
#include "raymath.h"

static inline Vector3 operator*(const Vector3& l, const Vector3& r){
    return Vector3Multiply(l, r);
}
static inline Vector3 operator+(const Vector3& l, const Vector3& r){
    return Vector3Add(l, r);
}
static inline Vector3 operator-(const Vector3& l, const Vector3& r){
    return Vector3Subtract(l, r);
}
static inline Vector3 operator*(const Vector3& l, const float r){
    return Vector3Scale(l, r);
}
static inline Vector3 operator*(const float l, const Vector3& r){
    return Vector3Scale(r, l);
}


static inline Vector2 operator*(const Vector2& l, const Vector2& r){
    return Vector2Multiply(l, r);
}
static inline Vector2 operator+(const Vector2& l, const Vector2& r){
    return Vector2Add(l, r);
}
static inline Vector2 operator-(const Vector2& l, const Vector2& r){
    return Vector2Subtract(l, r);
}
static inline Vector2 operator*(const Vector2& l, const float r){
    return Vector2Scale(l, r);
}
static inline Vector2 operator*(const float l, const Vector2& r){
    return Vector2Scale(r, l);
}


static inline Matrix operator*(const Matrix& l, const Matrix& r){
    return MatrixMultiply(r, l); //TODO: COMPLAIN TO WHOEVER THAT MADE THIS FUNCTION SWAPPED
}
static inline Vector3 operator*(const Matrix& l, const Vector3& r){
    return Vector3Transform(r, l);
}
static inline Vector2 operator*(const Matrix& l, const Vector2& r){
    return Vector2Transform(r, l);
}
static inline Matrix operator+(const Matrix& l, const Matrix& r){
    return MatrixAdd(l, r);
}
static inline Matrix operator-(const Matrix& l, const Matrix& r){
    return MatrixSubtract(l, r);
}
static inline Matrix Invert(const Matrix& l){
    return MatrixInvert(l);
}
static inline Matrix Transpose(const Matrix& l){
    return MatrixTranspose(l);
}