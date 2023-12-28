#ifndef TRIANGLE_H
#define TRIANGLE_H

#include "svg.h"
#include <iostream>
#include <string>

using namespace std;

class Triangle : public SVG {
public:
  Triangle(); // default constructor

  Triangle(int verticePoint1, int verticePoint2, int verticePoint3,
           int verticePoint4, int verticePoint5, int verticePoint6,
           string color);

  ostream &write(ostream &out) const override;

  istream &read(istream &inputStream) override;

private:
  int verticePoint1{0}, verticePoint2{0};
  int verticePoint3{0}, verticePoint4{0};
  int verticePoint5{0}, verticePoint6{0};
  string color{"black"};
};

#endif
