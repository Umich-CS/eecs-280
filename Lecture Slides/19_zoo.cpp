/* zoo.cpp
 *
 * Example using containers of pointers
 *
 * by Andrew DeOrio <awdeorio@umich.edu>
 * 2015-11-22
 */

#include "19_List.h"
#include <iostream>
#include <string>
using namespace std;


class Gorilla {
  string name;
public:
  Gorilla() : name("noname") { cout << "Gorilla default ctor\n"; }

  Gorilla(string name_in) : name(name_in) {
    cout << "Gorilla ctor: " << name << "\n";
  }

  Gorilla(const Gorilla &other) {
    name = other.name + " clone";
    cout << "Gorilla copy ctor: " << name << "\n";
  }

  ~Gorilla() {
    cout << "Gorilla dtor: " << name << "\n";
  }

  Gorilla & operator=(const Gorilla &rhs) {
    name = rhs.name + " clone";
    cout << "Gorilla operator=: " << name << "\n";
    return *this;
  }

  string get_name() const { return name; }
};


int main() {

{
  //NOTE: to see all the copies, disable optimization:
  //g++ -fno-elide-constructors
  cout << "\n*** Container of values ***\n";
  List <Gorilla> zoo;
  zoo.push_front(Gorilla("Colo"));
}

{
  cout << "\n*** Container of pointers ***\n";

  // once upon a time there was a zoo where Gorillas lived
  List<Gorilla*> zoo;

  // two gorillas lived in the zoo, Colo and Koko
  zoo.push_front(new Gorilla("Colo"));
  zoo.push_front(new Gorilla("Koko"));

  // Francine the zoo keeper fed the animals each day.  In the morning she
  // made a list of all the animals
  List<Gorilla*> todo = zoo;

  // She said hello to each animal, fed it, and removed it from her todo list
  while (!todo.empty()) {
    Gorilla *g = todo.front();
    cout << "Hi, " << g->get_name() << "\n";
    todo.pop_front();
  }

  // Don't forget to clean up, or you'll get orphan Gorilla objects!
  while (!zoo.empty()) {
    delete zoo.front();
    zoo.pop_front();
  }

}

  return 0;
}
