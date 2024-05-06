// COP3503C: Project 2 (Image Processing)
// main.cpp (requires: Data.h)
// Last edited: 10/31/22

#include <iostream>
#include <fstream>
#include <vector>
#include <string>
#include "Data.h"
using namespace std;

// Prototypes that tests if identical image/pixels + variables
int TestPixelsIdentical(const Data &obj1, const Data &obj2);
void DisplayPixel(const Data &obj1, const Data &obj2, const int &a);
bool TestVariablesIdentical(const Data &obj1, const Data &obj2);
void PerformTest(const string &example_name, const string &test_name);

// Main Program (load files + perform tasks)
int main() {

    /* Load Input Files */
    cout << "----------------Loading Input Files----------------" << endl;

    Data car;
    car.ReadImageData("input/car.tga", car);
    cout << "car.tga loaded" << endl;

    Data circles;
    circles.ReadImageData("input/circles.tga", circles);
    cout << "circles.tga loaded" << endl;

    Data layer1;
    layer1.ReadImageData("input/layer1.tga", layer1);
    cout << "layer1.tga loaded" << endl;

    Data layer2;
    layer2.ReadImageData("input/layer2.tga", layer2);
    cout << "layer2.tga loaded" << endl;

    Data layer_blue;
    layer_blue.ReadImageData("input/layer_blue.tga", layer_blue);
    cout << "layer_blue.tga loaded" << endl;

    Data layer_green;
    layer_green.ReadImageData("input/layer_green.tga", layer_green);
    cout << "layer_green.tga loaded" << endl;

    Data layer_red;
    layer_red.ReadImageData("input/layer_red.tga", layer_red);
    cout << "layer_red.tga loaded" << endl;

    Data pattern1;
    pattern1.ReadImageData("input/pattern1.tga", pattern1);
    cout << "pattern1.tga loaded" << endl;

    Data pattern2;
    pattern2.ReadImageData("input/pattern2.tga", pattern2);
    cout << "pattern2.tga loaded" << endl;

    Data text;
    text.ReadImageData("input/text.tga", text);
    cout << "text.tga loaded" << endl;

    Data text2;
    text2.ReadImageData("input/text2.tga", text2);
    cout << "text2.tga loaded" << endl;


    /* Perform Tasks */
    cout << "---------------------Tasks------------------------" << endl;

    // Task 1 (MULTIPLY: layer1 * pattern1)
    Data part1;
    part1.CopyData(layer1, part1);
    layer1.Multiply(layer1, pattern1, part1);
    part1.WriteImageData("output/part1.tga", part1);
    cout << "Task 1 Complete!" << endl;

    // Task 2 (SUBTRACT: car - layer2)
    Data part2;
    part2.CopyData(car, part2);
    car.Subtract(car, layer2, part2);
    part2.WriteImageData("output/part2.tga", part2);
    cout << "Task 2 Complete!" << endl;

    // Task 3 (MULTIPLY: layer1 * pattern2, SCREEN: text and temp)
    Data temp3;
    temp3.CopyData(layer2, temp3);
    layer1.Multiply(layer1, pattern2, temp3);

    Data part3;
    part3.CopyData(text, part3);
    text.Screen(text, temp3, part3);
    part3.WriteImageData("output/part3.tga", part3);
    cout << "Task 3 Complete!" << endl;

    // Task 4 (MULTIPLY: layer2 * circles, SUBTRACT: temp - pattern2)
    Data temp4;
    temp4.CopyData(layer2, temp4);
    layer2.Multiply(layer2, circles, temp4);

    Data part4;
    part4.CopyData(pattern2, part4);
    pattern2.Subtract(temp4, pattern2, part4);
    part4.WriteImageData("output/part4.tga", part4);
    cout << "Task 4 Complete!" << endl;

    // Task 5 (OVERLAY: layer1 - top; pattern1 - bottom)
    Data part5;
    part5.CopyData(pattern1, part5);
    pattern1.Overlay(layer1, pattern1, part5);
    part5.WriteImageData("output/part5.tga", part5);
    cout << "Task 5 Complete!" << endl;


    // Task 6 (ADD: car(green) + 200)
    Data part6;
    part6.CopyData(car, part6);
    car.AddToColor(car, 200, 1, part6);
    part6.WriteImageData("output/part6.tga", part6);
    cout << "Task 6 Complete!" << endl;

    // Task 7: (MULTIPLY: car(red) * 4, car(blue) * 0)
    Data temp7;
    temp7.CopyData(car, temp7);
    car.MultiplyToColor(car, 4, 2, temp7);

    Data part7;
    part7.CopyData(temp7, part7);
    temp7.MultiplyToColor(temp7, 0, 0, part7);
    part7.WriteImageData("output/part7.tga", part7);
    cout << "Task 7 Complete!" << endl;

    // Task 8: (WRITE EACH COLOR CHANNEL AS SEP FILE: car) - 3 parts
    Data part8b;
    part8b.CopyData(car, part8b);
    Data part8g;
    part8g.CopyData(car, part8g);
    Data part8r;
    part8r.CopyData(car, part8r);

    car.Separate(car, 0, part8b);
    part8b.WriteImageData("output/part8_b.tga", part8b);
    car.Separate(car, 1, part8g);
    part8g.WriteImageData("output/part8_g.tga", part8g);
    car.Separate(car, 2, part8r);
    part8r.WriteImageData("output/part8_r.tga", part8r);
    cout << "Task 8 (b,g,r) Complete!" << endl;

    // Task 9: (COMBINE: layer_blue, layer_green, layer_red)
    Data part9;
    part9.CopyData(layer_blue, part9);
    layer_blue.Combine(layer_blue, layer_green, layer_red, part9);
    part9.WriteImageData("output/part9.tga", part9);
    cout << "Task 9 Complete!" << endl;

    // Task 10: (ROTATE 180 DEGREES - upside down: text2)
    Data part10;
    part10.CopyData(text2, part10);
    text2.Rotate(text2, part10);
    part10.WriteImageData("output/part10.tga", part10);
    cout << "Task 10 Complete!" << endl;

    // Extra Credit: (QUADRANT: car; circles; pattern1; text)
    Data ec;
    ec.CopyData(car, ec);
    ec.width = 512*2;
    ec.height = 512*2;
    ec.Quadrant(car, circles, text, pattern1, ec);
    ec.WriteImageData("output/extracredit.tga", ec);
    cout << "Extra Credit Complete!" << endl;


    /* Test if everything identical */
    PerformTest("examples/EXAMPLE_part1.tga", "output/part1.tga");
    PerformTest("examples/EXAMPLE_part2.tga", "output/part2.tga");
    PerformTest("examples/EXAMPLE_part3.tga", "output/part3.tga");
    PerformTest("examples/EXAMPLE_part4.tga", "output/part4.tga");
    PerformTest("examples/EXAMPLE_part5.tga", "output/part5.tga");
    PerformTest("examples/EXAMPLE_part6.tga", "output/part6.tga");
    PerformTest("examples/EXAMPLE_part7.tga", "output/part7.tga");
    PerformTest("examples/EXAMPLE_part8_b.tga", "output/part8_b.tga");
    PerformTest("examples/EXAMPLE_part8_g.tga", "output/part8_g.tga");
    PerformTest("examples/EXAMPLE_part8_r.tga", "output/part8_r.tga");
    PerformTest("examples/EXAMPLE_part9.tga", "output/part9.tga");
    PerformTest("examples/EXAMPLE_part10.tga", "output/part10.tga");
    PerformTest("examples/EXAMPLE_extracredit.tga", "output/extracredit.tga");

}

// Implementation of functions that tests if image data identical
bool TestVariablesIdentical(const Data &obj1, const Data &obj2) {
    if (obj1.idLength != obj2.idLength) {
        cout << "idLength different!" << endl;
        return false;
    }
    if (obj1.colorMapType != obj2.colorMapType) {
        cout << "colorMapType different!" << endl;
        return false;
    }
    if (obj1.dataTypeCode != obj2.dataTypeCode) {
        cout << "dataTypeCode different!" << endl;
        return false;
    }
    if (obj1.colorMapOrigin != obj2.colorMapOrigin) {
        cout << "colorMapOrigin different!" << endl;
        return false;
    }
    if (obj1.colorMapDepth != obj2.colorMapDepth) {
        cout << "colorMapDepth different!" << endl;
        return false;
    }
    if (obj1.xOrigin != obj2.xOrigin) {
        cout << "xOrigin different!" << endl;
        return false;
    }
    if (obj1.yOrigin != obj2.yOrigin) {
        cout << "yOrigin different!" << endl;
        return false;
    }
    if (obj1.width != obj2.width) {
        cout << "width different!" << endl;
        return false;
    }
    if (obj1.height != obj2.height) {
        cout << "height different!" << endl;
        return false;
    }
    if (obj1.bitsPerPixel != obj2.bitsPerPixel) {
        cout << "bitsPerPixel different!" << endl;
        return false;
    }
    if (obj1.imageDescriptor != obj2.imageDescriptor) {
        cout << "imageDescriptor different!" << endl;
        return false;
    }
    return true;
}
int TestPixelsIdentical(const Data &obj1, const Data &obj2) {
    int pixels1 = obj1.width * obj1.height;
    int pixels2 = obj2.width * obj2.height;
    if (pixels1 != pixels2) {
        cout << "number of pixels different!" << endl;
        return -1;
    }
    for (int i = 0; i < pixels1; ++i) {
        for (int j = 0; j < 3; ++j) {
            if (obj1.pix.at(i).at(j) != obj2.pix.at(i).at(j)) {
                //cout << "pixel value (" << i << ", " << j << ") different!" << endl;
                return i;
            }
        }
    }
    return 1;
}
void DisplayPixel(const Data &obj1, const Data &obj2, const int &a) {
    cout << "test (program output): (" << (int)obj1.pix.at(a).at(0) << ", " << (int)obj1.pix.at(a).at(1) << ", "
         << (int)obj1.pix.at(a).at(2) << ")" << endl;
    cout << "example (answer key): (" << (int)obj2.pix.at(a).at(0) << ", " << (int)obj2.pix.at(a).at(1) << ", "
         << (int)obj2.pix.at(a).at(2) << ")" << endl;
}
void PerformTest(const string &example_name, const string &test_name) {
    Data example;
    example.Data::ReadImageData(example_name, example);

    Data test;
    test.Data::ReadImageData(test_name, test);

    cout << "--------------Testing if (" << example_name << ") and (" << test_name << ") same--------------" << endl;
    int result = TestPixelsIdentical(test, example);
    if (result == 1) {
        cout << "Pixels test successful!" << endl;
    }
    else if (result == -1) {
        cout << "Pixels test unsuccessful! Number of pixels differ!" << endl;
    }
    else {
        cout << "Pixels test unsuccessful! Pixel value at " << result << " differ!" << endl;
        DisplayPixel(test, example, result);
    }


    int result2 = TestVariablesIdentical(test, example);
    if (result2 == 1) {
        cout << "Variables test successful!" << endl;
    }
    else {
        cout << "Variables test unsuccessful!" << endl;
    }
}