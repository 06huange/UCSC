// $Id: hello.cpp,v 1.1 2020-10-01 15:41:24-07 - - $

#include <iostream>
#include <string>
using namespace std;

#include "hello.h"

hello::hello() {
}

hello::~hello() {
}

hello::hello (const string& message_): message(message_) {
}

void hello::say (ostream& out) {
   out << message << endl;
}

