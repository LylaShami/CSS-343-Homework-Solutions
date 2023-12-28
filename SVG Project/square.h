#ifndef SQUARE_H
#define SQUARE_H

#include "svg.h"
#include <iostream>
#include <string>

using namespace std;

class Square : public SVG {
public:
  // paramaitized constructor
  explicit Square(int xCoordinate = 0, int yCoordinate = 0, int sideLength = 0,
                  string fillColor = "black");

  ostream &write(ostream &out) const override;

  istream &read(istream &inputStream) override;

private:
  int xCoordinate;

  int yCoordinate;

  int sideLength;

  string fillColor;
};

#endif