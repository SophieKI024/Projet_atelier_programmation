#pragma once

struct Vector{
        double x,y;
        };

Vector operator+(Vector a, Vector b); //Sum
Vector operator-(Vector a, Vector b); //Difference
double norm2(Vector a);               //Euclidian  norm
Vector operator*(Vector a, double lambda); //Mult. scalar
Vector operator*(double lambda, Vector a); //Mult. scalar
