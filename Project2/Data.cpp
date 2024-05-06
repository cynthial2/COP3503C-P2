// COP3503C: Project 2 (Image Processing)
// Data.cpp (requires: Data.h)
// Last edited: 10/31/22

#include <iostream>
#include <fstream>
#include <vector>
#include <string>
#include "Data.h"
using namespace std;

// Read input + Write output
void Data::ReadImageData(const string &name, Data &obj) {
    ifstream file(name, ios_base::binary);

    if (file.is_open()) {
        // Header info
        file.read(&obj.idLength, 1);
        file.read(&obj.colorMapType, 1);
        file.read(&obj.dataTypeCode, 1);
        file.read((char*)&obj.colorMapOrigin, 2);
        file.read((char*)&obj.colorMapLength, 2);
        file.read(&obj.colorMapDepth, 1);
        file.read((char*)&obj.xOrigin, 2);
        file.read((char*)&obj.yOrigin, 2);
        file.read((char*)&obj.width, 2);
        file.read((char*)&obj.height, 2);
        file.read(&obj.bitsPerPixel, 1);
        file.read(&obj.imageDescriptor, 1);

        // Pixels info (each pixel contains 3 bytes)
        int pixels = (int)obj.width * (int)obj.height;

        for (int i = 0; i < pixels; ++i) {
            vector<unsigned char> temp_pixel;
            // loop for each color in each pixel (blue, green, red)
            for (int j = 0; j < 3; ++j) {
                char temp_color;
                file.read(&temp_color, 1);
                temp_pixel.push_back((unsigned char)temp_color);
            }
            obj.pix.push_back(temp_pixel);
        }

    }
    else {
        cout << "file not opened" << endl;
    }
}
void Data::WriteImageData(const string &name, Data &obj) {
    ofstream file(name, ios_base::binary);
    // Header info
    file.write(&obj.idLength, 1);
    file.write(&obj.colorMapType, 1);
    file.write(&obj.dataTypeCode, 1);
    file.write((char*)&obj.colorMapOrigin, 2);
    file.write((char*)&obj.colorMapLength, 2);
    file.write(&obj.colorMapDepth, 1);
    file.write((char*)&obj.xOrigin, 2);
    file.write((char*)&obj.yOrigin, 2);
    file.write((char*)&obj.width, 2);
    file.write((char*)&obj.height, 2);
    file.write(&obj.bitsPerPixel, 1);
    file.write(&obj.imageDescriptor, 1);

    // Pixels info
    int pixels = (int)obj.width * (int)obj.height;
    for (int i = 0; i < pixels; ++i) {
        // loop for each color in each pixel (blue, green, red)
        for (int j = 0; j < 3; ++j) {
            unsigned char temp_color = obj.pix.at(i).at(j);
            file.write((char*)&temp_color, 1);
        }
    }
}

// Copy Data (to store new result); vector still empty!
void Data::CopyData(const Data &old_obj, Data &new_obj) {
    new_obj.idLength = old_obj.idLength;
    new_obj.colorMapType = old_obj.colorMapType;
    new_obj.dataTypeCode = old_obj.dataTypeCode;
    new_obj.colorMapOrigin = old_obj.colorMapOrigin;
    new_obj.colorMapLength = old_obj.colorMapLength;
    new_obj.colorMapDepth = old_obj.colorMapDepth;
    new_obj.xOrigin = old_obj.xOrigin;
    new_obj.yOrigin = old_obj.yOrigin;
    new_obj.width = old_obj.width;
    new_obj.height = old_obj.height;
    new_obj.bitsPerPixel = old_obj.bitsPerPixel;
    new_obj.imageDescriptor = old_obj.imageDescriptor;
}

// Multiply (new_obj = obj1 * obj2)
void Data::Multiply(const Data &obj1, const Data &obj2, Data &new_obj) {
    int pixels = (int)new_obj.width * (int)new_obj.height;
    for (int i = 0; i < pixels; ++i) {
        vector<unsigned char> temp_pixel;
        // loop for each color of each pixel (blue, green, red)
        for (int j = 0; j < 3; ++j) {
            float temp;
            // add 0.5f to get rounded up
            temp = ((float)obj1.pix.at(i).at(j) * (float)obj2.pix.at(i).at(j))/255 + 0.5f;
            temp_pixel.push_back((unsigned char)temp);
        }
        new_obj.pix.push_back(temp_pixel);
    }
}

// Multiply specific color by number (new_obj = obj(color) * n)
void Data::MultiplyToColor(const Data &obj, const int &n, const int &idx, Data &new_obj) {
    int pixels = (int)new_obj.width * (int)new_obj.height;
    for (int i = 0; i < pixels; ++i) {
        vector<unsigned char> temp_pixel;
        // change selected color (idx) of each pixel (blue, green, red)
        for (int j = 0; j < 3; ++j) {
            // if j is the selected idx, push_back changed value, else push_back same value as obj
            if (j == idx) {
                int temp;
                temp = (int)obj.pix.at(i).at(j) * n;
                if (temp > 255) {
                    temp = 255;
                }
                temp_pixel.push_back((unsigned char)temp);
            }
            else {
                unsigned char temp;
                temp = obj.pix.at(i).at(j);
                temp_pixel.push_back(temp);
            }
        }
        new_obj.pix.push_back(temp_pixel);
    }
}

// Multiply pixel by number (new_obj = obj * n)
void Data::MultiplyByNum(const Data &obj, const int &n, Data &new_obj) {
    int pixels = (int)new_obj.width * (int)new_obj.height;
    for (int i = 0; i < pixels; ++i) {
        vector<unsigned char> temp_pixel;
        // change each pixel (blue, green, red)
        for (int j = 0; j < 3; ++j) {
                int temp;
                temp = (int)obj.pix.at(i).at(j) * n;
                if (temp > 255) {
                    temp = 255;
                }
                temp_pixel.push_back((unsigned char)temp);
        }
        new_obj.pix.push_back(temp_pixel);
    }
}

// Subtract (new_obj = obj1 - obj2)
void Data::Subtract(const Data &obj1, const Data &obj2, Data &new_obj) {
    int pixels = (int)new_obj.width * (int)new_obj.height;
    for (int i = 0; i < pixels; ++i) {
        vector<unsigned char> temp_pixel;
        // loop for each color of each pixel (blue, green, red)
        for (int j = 0; j < 3; ++j) {
            int temp;
            // change to int for calc, clamp at min (0) if under
            temp = (int)obj1.pix.at(i).at(j) - (int)obj2.pix.at(i).at(j);
            if (temp < 0) {
                temp = 0;
            }
            temp_pixel.push_back((unsigned char)temp);
        }
        new_obj.pix.push_back(temp_pixel);
    }
}

// Subtract from number (new_obj = n - obj)
void Data::SubtractFromNum(const int &n, const Data &obj, Data &new_obj) {
    int pixels = (int)new_obj.width * (int)new_obj.height;
    for (int i = 0; i < pixels; ++i) {
        vector<unsigned char> temp_pixel;
        // loop for each color of each pixel (blue, green, red)
        for (int j = 0; j < 3; ++j) {
            int temp;
            // change to int for calc, clamp at min (0) if under
            temp = n - (int)obj.pix.at(i).at(j);
            if (temp < 0) {
                temp = 0;
            }
            temp_pixel.push_back((unsigned char)temp);
        }
        new_obj.pix.push_back(temp_pixel);
    }
}

// Add (new_obj = obj1 + obj2)
void Data::Add(const Data &obj1, const Data &obj2, Data &new_obj) {
    int pixels = (int)new_obj.width * (int)new_obj.height;
    for (int i = 0; i < pixels; ++i) {
        vector<unsigned char> temp_pixel;
        // loop for each color of each pixel (blue, green, red)
        for (int j = 0; j < 3; ++j) {
            int temp;
            // change to int for calc, clamp at max (255) if over
            temp = (int)obj1.pix.at(i).at(j) + (int)obj2.pix.at(i).at(j);
            if (temp > 255) {
                temp = 255;
            }
            temp_pixel.push_back((unsigned char)temp);
        }
        new_obj.pix.push_back(temp_pixel);
    }
}

// Add number to specific color (new_obj = obj(color) + n)
void Data::AddToColor(const Data &obj, const int &n, const int &idx, Data &new_obj) {
    int pixels = (int)new_obj.width * (int)new_obj.height;
    for (int i = 0; i < pixels; ++i) {
        vector<unsigned char> temp_pixel;
        // loop through each pixel of each color (blue, green, red)
        for (int j = 0; j < 3; ++j) {
            // if j is the selected idx, push_back changed value, else push_back same value as obj
            if (j == idx) {
                // change to int for calc, clamp at max (255) if over
                int temp;
                temp = (int)obj.pix.at(i).at(j) + n;
                if (temp > 255) {
                    temp = 255;
                }
                temp_pixel.push_back((unsigned char)temp);
            }
            else {
                unsigned char temp;
                temp = obj.pix.at(i).at(j);
                temp_pixel.push_back(temp);
            }
        }
        new_obj.pix.push_back(temp_pixel);
    }
}

// Screen (new_obj = 1 - (1-obj1)*(1-obj2))
void Data::Screen(const Data &obj1, const Data &obj2, Data &new_obj) {
    // Make 3 temps: (1-obj1), (1-obj2), (1-obj1)*(1-obj2)
    Data temp1;
    CopyData(obj1, temp1);
    Data temp2;
    CopyData(obj1, temp2);
    Data temp3;
    CopyData(obj1, temp3);

    // Find (1-obj1) and (1-obj2)
    SubtractFromNum(255, obj1, temp1);
    SubtractFromNum(255, obj2, temp2);

    // Find (1-obj2)*(1-obj2)
    Multiply(temp1, temp2, temp3);

    // Find 1-(1-obj2)*(1-obj2)
    SubtractFromNum(255, temp3, new_obj);
}

// Overlay (new_obj = 2*obj1*obj2 if obj2<=50%gray ...OR... 1 - 2*(1-obj1)*(1-obj2) if obj2>50%gray)
void Data::Overlay(const Data &obj1, const Data &obj2, Data &new_obj) {
    int pixels = (int)new_obj.width * (int)new_obj.height;
    for (int i = 0; i < pixels; ++i) {
        vector<unsigned char> temp_pixel;
        unsigned char c;
        for (int j = 0; j < 3; ++j) {
            float temp1 = obj1.pix.at(i).at(j)/255.0f;
            float temp2 = obj2.pix.at(i).at(j)/255.0f;
            c = OverlayHelper(temp1, temp2);
            temp_pixel.push_back(c);
        }
        new_obj.pix.push_back(temp_pixel);
    }
}

// Overlay helper (does the calculations)
char Data::OverlayHelper(float x, float y) {
    if (y > 0.5) {
        return ((1 - 2 * (1 - x) * (1 - y)) * 255.0f) + 0.5f;
    }
    else {
        return ((2 * x * y) * 255.0f ) + 0.5f;
    }
}

// Combine (new_obj = obj1 (blue) and obj2 (green) and obj3 (red))
void Data::Combine(const Data &obj1, const Data &obj2, const Data &obj3, Data &new_obj) {
    int pixels = (int)new_obj.width * (int)new_obj.height;
    for (int i = 0; i < pixels; ++i) {
        vector<unsigned char> temp_pixel;
        // pushback onto temp_pixel: blue value, green value, red value
        temp_pixel.push_back(obj1.pix.at(i).at(0));
        temp_pixel.push_back(obj2.pix.at(i).at(1));
        temp_pixel.push_back(obj3.pix.at(i).at(2));
        new_obj.pix.push_back(temp_pixel);
    }
}

// Separate (new_obj = obj(color))
void Data::Separate(const Data &obj, const int &idx, Data &new_obj) {
    int pixels = (int)new_obj.width * (int)new_obj.height;
    for (int i = 0; i < pixels; ++i) {
        vector<unsigned char> temp_pixel;
        // pushback onto temp_pixel: blue value, green value, red value
        temp_pixel.push_back(obj.pix.at(i).at(idx));
        temp_pixel.push_back(obj.pix.at(i).at(idx));
        temp_pixel.push_back(obj.pix.at(i).at(idx));
        new_obj.pix.push_back(temp_pixel);
    }
}

// Rotate (new_obj = obj(rotated 180 degrees))
void Data::Rotate(const Data &obj, Data &new_obj) {
    int pixels = (int)new_obj.width * (int)new_obj.height;
    for (int i = 0; i < pixels; ++i) {
        vector<unsigned char> temp_pixel;
        // loop for each color of each pixel (blue, green, red)
        for (int j = 0; j < 3; ++j) {
            int n = obj.pix.size() - 1;   // index of last element
            temp_pixel.push_back(obj.pix.at(n-i).at(j));
        }
        new_obj.pix.push_back(temp_pixel);
    }
}

// Quadrant (new_obj = car, circles, text, pattern1)
void Data::Quadrant(const Data &car, const Data &circles, const Data &text, const Data &pattern1, Data &new_obj) {
    // for every row of text and pattern1
    for (int i = 0; i < 512; ++i) {
        // for every pixel of text in row i
        for (int j = 0; j < 512; ++j) {
            vector<unsigned char> temp_pixel3;
            // for every color of pixel
            for (int k = 0; k < 3; ++k) {
                temp_pixel3.push_back(text.pix.at(j + i*512).at(k));
            }
            new_obj.pix.push_back(temp_pixel3);
        }
        // for every pixel of pattern1 in row i
        for (int j = 0; j < 512; ++j) {
            vector<unsigned char> temp_pixel4;
            // for every color of pixel
            for (int k = 0; k < 3; ++k) {
                temp_pixel4.push_back(pattern1.pix.at(j + i*512).at(k));
            }
            new_obj.pix.push_back(temp_pixel4);
        }
    }
    // for every row of car and circles
    for (int i = 0; i < 512; ++i) {
        // for every pixel of car in row i
        for (int j = 0; j < 512; ++j) {
            vector<unsigned char> temp_pixel1;
            // for every color of pixel
            for (int k = 0; k < 3; ++k) {
                temp_pixel1.push_back(car.pix.at(j + i*512).at(k));
            }
            new_obj.pix.push_back(temp_pixel1);
        }
        // for every pixel of circles in row i
        for (int j = 0; j < 512; ++j) {
            vector<unsigned char> temp_pixel2;
            // for every color of pixel
            for (int k = 0; k < 3; ++k) {
                temp_pixel2.push_back(circles.pix.at(j + i*512).at(k));
            }
            new_obj.pix.push_back(temp_pixel2);
        }
    }
}
