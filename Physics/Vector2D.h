#pragma message(">> Including Vector2D.h from: " __FILE__)

#ifndef VECTOR2D_H
#define VECTOR2D_H

#include <string>
#include <iostream>

class Vector2D
{
    public:
        float X, Y;

    public:
        Vector2D(float x=0, float y=0) : X(x), Y(y) {}

    public:
        /*
            overriding the + operator for vector addition
        */
        inline Vector2D operator+(const Vector2D& v2) const {
            return Vector2D(X + v2.X, Y + v2.Y);
        }

        /*
            overriding the - operator for vector subtraction
        */
        inline Vector2D operator-(const Vector2D& v2) const {
            return Vector2D(X - v2.X, Y - v2.Y);
        }

        /*
            overriding the - operator for vector multiplication
        */
        inline Vector2D operator*(const float scalar) const {
            return Vector2D(X * scalar, Y * scalar);
        }

        void Log(std::string msg = ""){
            std::cout << msg << "(X Y) = (" << X << " " << Y << ")" << std::endl;
        }

};

#endif // VECTOR2D_H
