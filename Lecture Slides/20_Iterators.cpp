/* Iterators.cpp
 * 
 * by Andrew DeOrio <awdeorio@umich.edu>
 * 2015-04-02
 */

#include "20_List_with_Iterator.h"
#include <iostream>
using namespace std;


bool no_duplicates(const List<int> &l) {
  for (List<int>::Iterator i=l.begin(); i != l.end(); ++i) {
    List<int>::Iterator j=i; ++j;
    for (; j != l.end(); ++j) {
      if (*i == *j) return false;
    }
  }
  return true;
}


int main() {

  List<int> l;
  l.push_front(3);
  l.push_front(2);
  l.push_front(1);


  cout << "l = ( ";
  for (List<int>::Iterator i=l.begin(); i != l.end(); ++i) {
    cout << *i << " ";
  }
  cout << ")" << endl;

  cout << "no_duplicates(l) = " << no_duplicates(l) << endl;

  ////////////////////////////////////////
  //C++11 version
  //
  //Compile C++11 code on OSX like normal
  //Compile on Windows (Visual Studio) like normal
  //Compile on Linux with g++ -std=c++11
  //  If it's CAEN Linux, run this command first: module load gcc
  //
  // cout << "l = ( ";
  // for (auto i:l) {   //access by value, type of i is int
  //   cout << i << " ";
  // }
  // cout << ")" << endl;
}
