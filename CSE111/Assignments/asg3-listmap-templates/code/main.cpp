// $Id: main.cpp,v 1.11 2018-01-25 14:19:29-08 - - $

#include <cstdlib>
#include <exception>
#include <iostream>
#include <fstream>
#include <string>
#include <unistd.h>
#include <regex>
using namespace std;

#include "listmap.h"
#include "xpair.h"
#include "util.h"

using str_str_map = listmap<string,string>;
using str_str_pair = str_str_map::value_type;

void scan_options (int argc, char** argv) {
   opterr = 0;
   for (;;) {
      int option = getopt (argc, argv, "@:");
      if (option == EOF) break;
      switch (option) {
         case '@':
            debugflags::setflags (optarg);
            break;
         default:
            complain() << "-" << char (optopt) << ": invalid option"
                       << endl;
            break;
      }
   }
}

void trim(string &buff){
   while(buff[0] == ' '){
      buff.erase(0,1);
   }
   while(buff[buff.size()-1] == ' '){
      buff.erase(buff.size()-1,1);
   }
}
bool isComment(string buff){
   smatch matches;
   regex_search(buff,matches,regex("\\S"));
   if(matches.size() == 0 || matches[0] == '0') return true;
   return false;
}

void processInput(string buff,str_str_map &m){
   smatch matches;
   regex t1 ("=");
   smatch key;
   smatch value;
   smatch parse;
   regex_search(buff,parse,t1);
   //check if there is = in the input
   int eqCount = 0;
   for(unsigned i=0;i<buff.length();i++){
      if(buff[i] == '=') eqCount++;
   }

   if(eqCount > 0){
      bool hasKey = true;
      bool hasValue = true;

      regex_search(buff,key,regex("\\S+?(?=\\s*=)"));
      regex_search(buff,value,regex(".?=\\s*(.*)$"));
      if(key[0] == "" || key.size() == 0) hasKey = false;
      if(value.size() == 0 || value[0] == "=") hasValue = false;
      

      if(!hasKey && !hasValue){
         for(auto i = m.begin(); i != m.end(); ++i){
            cout<<i->first<<" = ";
            cout<<i->second<<endl;
         }
         return;
      }
      if(!hasKey){
         //print keys with value specified
         for(auto i = m.begin(); i != m.end(); ++i){
            if(!(i->second < value[1]) && 
            !(value[1] < i->second)){
               cout<<i->first<<" = "<<i->second<<endl;
            }
         }
         return;
      }
      if(!hasValue){
         //delete key specified
         auto f = m.find(key[0]);
         if(f != m.end()) m.erase(f);
         return;
      }
      else if(hasKey && hasValue){
         //search map for key specified
         //if found, replace value
         //if not found, add new pair
         str_str_pair pair(key[0],value[1]);
         auto f = m.find(key[0]);
         if(f == m.end()) m.insert(pair);
         else f->second = value[1];
         cout<<key[0]<<" = "<<value[1]<<endl;
         return;
      }
   }
   else{
      regex_search(buff,key,regex(".*"));
      auto f = m.find(key[0]);
      if(f != m.end()){
         cout<<f->first<<" = "<<f->second<<endl;
      }
      else cerr<<key[0]<<": key not found"<<endl;
   }
   
}

int main (int argc, char** argv) {
   sys_info::execname (argv[0]);
   scan_options (argc, argv);
   int count = 1;
   string buff;
   str_str_map m;
   int status = 0;
   if(argc >= 2){
      for(int filenum = 1; filenum < argc; ++filenum){
         count = 1;
         fstream in;
         in.open(argv[filenum]);
         if(!in.is_open()){
            cerr<<"keyvalue: "<<argv[filenum]<<
            ": No such file or directory\n";
            status = 1;
            continue;
         }
         while(!in.eof()){
            getline(in,buff);
            trim(buff);
            cout<<argv[filenum]<<": "<<count<<": "<<buff<<"\n";
            count++;
            if(isComment(buff)) continue;
            if(buff[0] == '#'){
               if(buff.length() > 7 && 
               buff.substr(0,6) == "# $Id:") break;
               continue;
            }
            processInput(buff,m);
         }
      }
   }
   else{
      while(!cin.eof()){
         getline(cin,buff);
         trim(buff);
         if(buff == "exit") break;
         cout<<"-: "<<count<<": "<<buff<<"\n";
         count++;
         if(isComment(buff)) continue;
         if(buff[0] == '#'){
            if(buff.length() > 7 && 
            buff.substr(0,6) == "# $Id:") break;
            continue;
         }
         processInput(buff,m);
      }
   }
   exit(status);
}
