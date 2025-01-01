// $Id: hello.h,v 1.1 2020-10-01 15:41:24-07 - - $

#ifndef __HELLO_H__
#define __HELLO_H__

#include <iostream>
#include <string>

class hello {
   private:
      std::string message {"Hello, World!"};
   public:
      hello();                         // default constructor
      hello (const string&);           // alternate ctor
      ~hello();                        // destructor
      void say (ostream&);             // member function
};

#endif

