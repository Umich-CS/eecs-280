#ifndef TRIANGLE_H
#define TRIANGLE_H
/* 10_Triangle.h
 * 
 * Example of an Abstract Data Type (ADT) representing a Triangle.
 * This file contains the class declaration, which is the abstraction.
 *
 * by Andrew DeOrio <awdeorio@umich.edu>
 * Created 2013-05-16
 * Modified 2013-05-16
 */

//NOTE: there are no "#include"s because we don't need any libraries here!
//NOTE: there is no "using namespace std" because header files should contain
//      as few things as possible.


////////////////////////////////////////////////////////////////////////////////
class Triangle {
  //OVERVIEW: a geometric representation of a triangle

public:
  //EFFECTS: creates a zero size Triangle
  Triangle();

  //REQUIRES: a,b,c are non-negative and form a triangle
  //EFFECTS: creates a Triangle with given edge lengths
  Triangle(double a_in, double b_in, double c_in);

  //EFFECTS: returns the area
  double area() const;

  //EFFECTS: prints edge lengths
  void print() const;

  //EFFECTS: returns edge a, b, c
  double get_a() const { return a; }
  double get_b() const { return b; }
  double get_c() const { return c; }

  //REQUIRES: a,b,c are non-negative and form a triangle
  //MODIFIES: a, b, c
  //EFFECTS: sets length of edge a, b, c
  void set(double a_in, double b_in, double c_in);
  void set_a(double a_in);
  void set_b(double b_in);
  void set_c(double c_in);

 private:
  //edges are non-negative and form a triangle
  double a, b, c;

  //EFFECTS: returns true if member variables a,b,c form a triangle
  bool check_invariant();
};

#endif
