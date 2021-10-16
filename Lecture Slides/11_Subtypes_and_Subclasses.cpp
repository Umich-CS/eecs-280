/* 11_Subtypes_and_Subclasses.cpp
 * 
 * Example of derived types using Triangles
 *
 * by Andrew DeOrio <awdeorio@umich.edu>
 * Created 2013-05-24
 * Modified 2015-02-17
 */

#include <iostream> //cout, endl
#include <cassert>  //assert
#include <cstdlib>  //exit
#include <cmath>    //sqrt, acos
using namespace std;


////////////////////////////////////////////////////////////////////////////////
class Triangle {
  //OVERVIEW: a geometric representation of a triangle

public:
  //EFFECTS: creates a zero-size Triangle
  Triangle() : a(0), b(0), c(0) {}

  //REQUIRES: a,b,c are non-negative and form a triangle
  //EFFECTS: creates a Triangle with given edge lengths
  Triangle(double a_in, double b_in, double c_in)
    : a(a_in), b(b_in), c(c_in) {
    assert(check_invariant());
  }

  //EFFECTS: returns the area
  double area() const {
    double s = (a + b + c) / 2;
    double area = sqrt(s*(s-a)*(s-b)*(s-c));
    return area;
  }

  //EFFECTS: prints edge lengths
  void print() const
  { cout << "Triangle: a=" << a << " b=" << b << " c=" << c << endl; }

  //EFFECTS: sets edge length
  void set_a(double a_in) {
    a = a_in;
    assert(check_invariant());
  }

  //EFFECTS: sets edge length
  void set_b(double b_in) {
    b = b_in;
    assert(check_invariant());
  }

  //EFFECTS: sets edge length
  void set_c(double c_in) {
    c = c_in;
    assert(check_invariant());
  }

  //EFFECTS: sets edge lengths
  void set(double a_in, double b_in, double c_in) {
    a = a_in;
    b = b_in;
    c = c_in;
    assert(check_invariant());
  }

  //EFFECTS: returns edge length
  double get_a() const { return a; }
  double get_b() const { return b; }
  double get_c() const { return c; }

 private:
  //edges are non-negative and form a triangle
  double a,b,c;

  //EFFECTS: returns true if member variables a,b,c form a triangle
  bool check_invariant() {
  if (c >= a && c >= b) // c is the long edge
    return a + b > c;
  if (b >= a)           // b is the long edge
    return a + c > b;
  else                  // a is the long edge
    return b + c > a;
  }
};


////////////////////////////////////////////////////////////////////////////////
class Isosceles : public Triangle {
  //OVERVIEW: a geometric representation of an isosceles triangle;
  //           edge a is the base; b and c are legs of equal length

 public:
  //EFFECTS: creates an 0 size Isosceles triangle
  Isosceles() {} //Triangle default ctor runs automatically

  //REQUIRES: base and leg are non-negative and form an isosceles triangle
  //EFFECTS: creates an Isosceles triangle with given edge lengths
  Isosceles(double base, double leg)
    : Triangle(base, leg, leg) {}

  //EFFECTS: sets a, b, c, ensuring that we still have an Isosceles triangle
  void set(double a_in, double b_in, double c_in) {
    b_in = c_in;
    Triangle::set(a_in, b_in, c_in);
  }

  //EFFECTS: sets both legs
  void set_b(double b_in) {
    Triangle::set(get_a(), b_in, b_in);
  }

  //EFFECTS: sets both legs
  void set_c(double c_in) {
    Triangle::set(get_a(), c_in, c_in);
  }

};


////////////////////////////////////////////////////////////////////////////////
int main() {
  // array of Triangles representing a triangle mesh in computer graphics
  const int SIZE = 3;
  Isosceles mesh[SIZE];
  mesh[0] = Isosceles(3,4);
  mesh[1] = Isosceles(1,11);
  mesh[2] = Isosceles(5,5);

  // compute the area of the mesh
  double area = 0;
  for (int i=0; i<SIZE; ++i) {
    area += mesh[i].area();
  }
  cout << "total area = " << area << "\n";  //total area = 21.8818

  return 0;
}
