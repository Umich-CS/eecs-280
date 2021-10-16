/* Polymorphism.cpp
 * 
 * Example of polymorphic types using shapes
 *
 * by Andrew DeOrio <awdeorio@umich.edu>
 * 2013-05-24
 */

#include <iostream> //cin, cout, endl
#include <string>   //string
#include <cstdlib>  //exit
#include <cmath>    //sqrt
using namespace std;


////////////////////////////////////////////////////////////////////////////////
class Shape {
public:
  //EFFECTS: returns the area of Shape
  virtual double area() const = 0;

  //EFFECTS: prints edge lengths
  virtual void print() const = 0;
};


////////////////////////////////////////////////////////////////////////////////
class Triangle : public Shape {
  //OVERVIEW: a geometric representation of a triangle

public:
  //EFFECTS: creates a zero-size Triangle
  Triangle() : a(0), b(0), c(0) {}

  //REQUIRES: a,b,c are non-negative and form a triangle
  //EFFECTS: creates a Triangle with given edge lengths
  Triangle(double a_in, double b_in, double c_in)
    : a(a_in), b(b_in), c(c_in) {}

  //EFFECTS: returns the area
  virtual double area() const {
    double s = (a + b + c) / 2;
    double area = sqrt(s*(s-a)*(s-b)*(s-c));
    return area;
  }

  //EFFECTS: prints edge lengths
  virtual void print() const
  { cout << "Triangle: a=" << a << " b=" << b << " c=" << c << endl; }

  //EFFECTS: returns edge length
  double get_a() const { return a; }
  double get_b() const { return b; }
  double get_c() const { return c; }

 private:
  //edges are non-negative and form a triangle
  double a,b,c;
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
  
  //EFFECTS: prints edge lengths
  virtual void print() const
  { cout << "Isosceles: base=" << get_a() << " leg=" << get_b() << endl; }
};


////////////////////////////////////////////////////////////////////////////////
class Equilateral : public Isosceles {
  //OVERVIEW: a geometric representation of an equilateral triangle

 public:
  //EFFECTS: creates a 0 size Equilateral triangle
  Equilateral() {} // Isosceles ctor called automatically

  //REQUIRES: edge is non-negative
  //EFFECTS: creates an Equilateral triangle with given edges
  Equilateral(double edge)
    : Isosceles(edge, edge) {}

  //EFFECTS: prints edge lengths
  virtual void print() const
  { cout << "Equilateral: edge=" << get_a() << endl; }
};


////////////////////////////////////////////////////////////////////////////////
class Rectangle : public Shape {
  double a,b;
public:

  //EFFECTS: creates a zero-size Rectangle
  Rectangle() : a(0), b(0) {}

  //REQUIRES: a, b are non-negative
  //EFFECTS: creates a Rectangle with given edge lengths
  Rectangle(double a_in, double b_in) : a(a_in), b(b_in) {}

  //EFFECTS: returns the area
  virtual double area() const
  { return a*b; }

  //EFFECTS: prints edge lengths
  virtual void print() const
  { cout << "Rectangle: a=" << a << " b=" << b << endl; }

};


////////////////////////////////////////////////////////////////////////////////
// Factory function
static Rectangle g_rectangle(2,4);
static Triangle g_triangle(3,4,5);
static Isosceles g_isosceles(1,12);
static Equilateral g_equilateral(5);

//EFFECTS: asks user to select a shape;
//         returns a pointer to object of correct type
Shape * ask_user() {
  cout << "Rectangle, Triangle, Isosceles or Equilateral?  ";
  string s;
  cin >> s;
  if (s == "Rectangle")   return &g_rectangle;
  if (s == "Triangle")    return &g_triangle;
  if (s == "Isosceles")   return &g_isosceles;
  if (s == "Equilateral") return &g_equilateral;

  // There's an error if we get here
  cout << "Unrecognized shape `" << s << "'\n";
  exit(1);//crash
}


////////////////////////////////////////////////////////////////////////////////
int main() {

  // ask_user() example
  // Shape * s = ask_user();
  // s->print();

  // array of pointers to polymorphic objects
  Rectangle r(2,4);
  Isosceles i(1,12);
  Equilateral e(5);

  const int SIZE=3;
  Shape * shapes[SIZE] = {&r, &i, &e};

  int area = 0;
  for (Shape **i=shapes; i<shapes+SIZE; ++i) {
    (**i).print();
    area += (**i).area();
  }
  cout << "total area = " << area << endl;
}

/* output
Rectangle: a=2 b=4
Isosceles: base=1 leg=12
Equilateral: edge=5
total area = 23
 */
