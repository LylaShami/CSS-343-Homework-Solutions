#include "square.h"
#include <iostream>

using namespace std;

// paramitized constructor
Square::Square(int xCoordinate, int yCoordinate, int sideLength,
               string fillColor)
    : xCoordinate(xCoordinate), yCoordinate(yCoordinate),
      sideLength(sideLength), fillColor(fillColor) {}

ostream &Square::write(ostream &out) const {
  out << "      <rect ";
  out << "x=\"" << xCoordinate << "\" ";
  out << "y=\"" << yCoordinate << "\" ";
  out << "width=\"" << sideLength << "\" ";
  out << "height=\"" << sideLength << "\" ";
  out << "fill=\"" << fillColor << "\" ";
  out << " />" << endl;

  return out;
}

istream &Square::read(istream &inputStream) {
  inputStream >> xCoordinate >> yCoordinate >> sideLength >> fillColor;
  return inputStream;
}