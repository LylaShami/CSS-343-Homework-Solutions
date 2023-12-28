#ifndef RECTANGLE_H
#define RECTANGLE_H
#include "svg.h"
#include <iostream>
#include <string>

using namespace std;

class Rectangle : public SVG {
public:
    ostream &write(ostream &out) const override;

  // Operator>> equivalent to read the object contents
  istream &read(istream &input) override;

private:
  int x{0}, y{0};
  int width{0}, height{0};
  string color{"black"};
};
#endif