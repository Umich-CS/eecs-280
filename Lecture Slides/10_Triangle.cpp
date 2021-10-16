/* 10_Triangle.cpp
 * 
 * Example of an Abstract Data Type (ADT) representing a Triangle.
 * This file contains member function implementations.
 *
 * by Andrew DeOrio <awdeorio@umich.edu>
 * Created 2013-05-16
 * Modified 2015-02-17
 */

#include "10_Triangle.h" //needed for class declaration
#include <cmath>         //needed for sqrt
#include <iostream>      //needed for cout and endl
#include <cassert>       //needed for assert
using namespace std;


////////////////////////////////////////////////////////////////////////////////
// Triangle
Triangle::Triangle()
  : a(0), b(0), c(0) {}


Triangle::Triangle(double a_in, double b_in, double c_in)
  : a(a_in), b(b_in), c(c_in) {
  assert(check_invariant());
}


bool Triangle::check_invariant() {
  if (c >= a && c >= b) // c is the long edge
    return a + b > c;
  if (b >= a)           // b is the long edge
    return a + c > b;
  else                  // a is the long edge
    return b + c > a;
}


double Triangle::area() const {
  double s = (a + b + c) / 2;
  double area = sqrt(s*(s-a)*(s-b)*(s-c));
  return area;
}


void Triangle::print() const {
  cout << "a=" << a << " b=" << b << " c=" << c << endl;
}


void Triangle::set_a(double a_in) {
  a = a_in; 
  assert(check_invariant());
}


void Triangle::set_b(double b_in) {
  b = b_in; 
  assert(check_invariant());
}


void Triangle::set_c(double c_in) {
  c = c_in;
  assert(check_invariant());
}


void Triangle::set(double a_in, double b_in, double c_in) {
  a=a_in;
  b=b_in;
  c=c_in;
  assert(check_invariant());
}
