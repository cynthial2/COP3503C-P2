// COP3503C: Project 2 (Image Processing)
// Data.h
// Last edited: 10/31/22

#include <iostream>
#include <fstream>
#include <vector>
#include <string>
#pragma once
using namespace std;


// Header data initialization

class Data {

public:
    // Initialize Variables
    char idLength;
    char colorMapType;
    char dataTypeCode;
    short colorMapOrigin;
    short colorMapLength;
    char colorMapDepth;
    short xOrigin;
    short yOrigin;
    short width;
    short height;
    char bitsPerPixel;
    char imageDescriptor;

    // Initialize empty vector
    vector<vector<unsigned char>> pix;

    // Read input + Write output
    void ReadImageData(const string &name, Data &obj);
    void WriteImageData(const string &name, Data &obj);

    // Copy Data (to store new result); vector still empty!
    void CopyData(const Data &old_obj, Data &new_obj);

    // Multiply (new_obj = obj1 * obj2)
    void Multiply(const Data &obj1, const Data &obj2, Data &new_obj);

    // Multiply specific color by number (new_obj = obj(color) * n)
    void MultiplyToColor(const Data &obj, const int &n, const int &idx, Data &new_obj);

    // Multiply pixel by number (new_obj = obj * n)
    void MultiplyByNum(const Data &obj, const int &n, Data &new_obj);

    // Subtract (new_obj = obj1 - obj2)
    void Subtract(const Data &obj1, const Data &obj2, Data &new_obj);

    // Subtract from number (new_obj = n - obj)
    void SubtractFromNum(const int &n, const Data &obj, Data &new_obj);

    // Add (new_obj = obj1 + obj2)
    void Add(const Data &obj1, const Data &obj2, Data &new_obj);

    // Add number to color (new_obj = obj(color) + n);
    void AddToColor(const Data &obj, const int &n, const int &idx, Data &new_obj);

    // Screen (new_obj = 1 - (1-obj1)*(1-obj2))
    void Screen(const Data &obj1, const Data &obj2, Data &new_obj);

    // Overlay (new_obj = 2*obj1*obj2 if <=50%gray ...OR... 1 - 2*(1-obj1)*(1-obj2) if >50%gray)
    void Overlay(const Data &obj1, const Data &obj2, Data &new_obj);

    // Overlay helper (does the calculations)
    char OverlayHelper(float x, float y);

    // Combine (new_obj = obj1 (blue) and obj2 (green) and obj3 (red))
    void Combine(const Data &obj1, const Data &obj2, const Data &obj3, Data &new_obj);

    // Separate (new_obj = obj(color))
    void Separate(const Data &obj, const int &idx, Data &new_obj);

    // Rotate (new_obj = obj(rotated 180 degrees))
    void Rotate(const Data &obj, Data &new_obj);

    // Quadrant (new_obj = car, circles, text, pattern1)
    void Quadrant(const Data &car, const Data &circles, const Data &text, const Data &pattern1, Data &new_obj);

};



