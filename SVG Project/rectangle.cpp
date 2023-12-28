#include "rectangle.h"
#include <fstream>
#include <iostream>

using namespace std;
// operator<< equivalent to write the object out
ostream &Rectangle::write(ostream &out) const {
  out << "      <rect ";
  out << "x=\"" << x << "\" ";
  out << "y=\"" << y << "\" ";
  out << "width=\"" << width << "\" ";
  out << "height=\"" << height << "\" ";
  out << "fill=\"" << color << "\" ";
  out << " />" << endl;

  return out;
}

// Operator>> equivalent to read the object contents
istream &Rectangle::read(istream &input) {
  input >> x >> y >> width >> height >> color;
  return input;
}