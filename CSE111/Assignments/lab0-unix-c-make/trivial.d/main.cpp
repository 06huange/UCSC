// $Id: main.cpp,v 1.2 2020-10-01 15:41:37-07 - - $

#include <cstdlib>
#include <iostream>
#include <string>
#include <vector>
using namespace std;

#include <libgen.h>

#include "hello.h"

int main (int argc, char** argv) {
   string execname {basename (argv[0])};
   vector<string> args (&argv[1], &argv[argc]);
   hello world;
   world.say (cout);
   hello goodbye {"Goodbye, world!"};
   goodbye.say (cout);
   for (const auto& arg: args) cout << "for: " << arg << endl;
   return EXIT_SUCCESS;
}

