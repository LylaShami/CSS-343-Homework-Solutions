#include "triangle.h"
#include <fstream>
#include <iostream>

using namespace std;

Triangle::Triangle() {}
// paramatized point with each vertice of a triangle
Triangle::Triangle(int point1, int point2, int point3, int point4, int point5,
                   int point6, string color)
    : verticePoint1(point1), verticePoint2(point2), verticePoint3(point3),
      verticePoint4(point4), verticePoint5(point5), verticePoint6(point6),
      color(color) {}

ostream &Triangle::write(ostream &out) const {
  out << "      <polygon points=\"";
  out << verticePoint1 << "," << verticePoint2 << " ";
  out << verticePoint3 << "," << verticePoint4 << " ";
  out << verticePoint5 << "," << verticePoint6 << "\" ";
  out << "fill=\"" << color << "\" ";
  out << " />" << endl;

  return out;
}

istream &Triangle::read(istream &inputStream) {
  inputStream >> verticePoint1 >> verticePoint2 >> verticePoint3 >>
      verticePoint4 >> verticePoint5 >> verticePoint6 >> color;
  return inputStream;
}
