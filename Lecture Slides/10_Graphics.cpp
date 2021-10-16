/* 10_Graphics.cpp
 * 
 * Example using an Abstract Data Type (ADT) representing a Triangle, using
 * a simple graphics-like application that contains a triangle mesh
 *
 * To compile, first make sure you have all three files in the same directory:
 * 10_Triangle.cpp 10_Triangle.h 10_Graphics.cpp
 * $ g++ -Wall -Werror -pedantic 10_Graphics.cpp 10_Triangle.cpp
 *
 * by Andrew DeOrio <awdeorio@umich.edu>
 * Created 2013-05-16
 * Modified 2015-02-17
 */

#include "10_Triangle.h" //needed for Triangle ADT
#include <iostream>      //needed for cout and endl
using namespace std;


int main() {

  // array of Triangles representing a triangle mesh in computer graphics
  const int SIZE = 3;
  Triangle mesh[SIZE];
  mesh[0] = Triangle(3,4,5);
  mesh[1] = Triangle(1,11,11);
  mesh[2] = Triangle(5,5,5);

  // compute the area of the mesh
  double area = 0;
  for (int i=0; i<SIZE; ++i) {
    area += mesh[i].area();
  }
  cout << "total area = " << area << "\n";  //total area = 22.3196

  return 0;
}
