// $Id: cxi.cpp,v 1.1 2020-11-22 16:51:43-08 - - $

#include <iostream>
#include <memory>
#include <string>
#include <unordered_map>
#include <fstream>
#include <regex>
#include <vector>
using namespace std;

#include <libgen.h>
#include <sys/types.h>
#include <unistd.h>

#include "protocol.h"
#include "logstream.h"
#include "sockets.h"

logstream outlog (cout);
struct cxi_exit: public exception {};

unordered_map<string,cxi_command> command_map {
   {"exit", cxi_command::EXIT},
   {"help", cxi_command::HELP},
   {"ls"  , cxi_command::LS  },
   {"get" , cxi_command::GET },
   {"put" , cxi_command::PUT },
   {"rm"  , cxi_command::RM  },
};

static const char help[] = R"||(
exit         - Exit the program.  Equivalent to EOF.
get filename - Copy remote file to local host.
help         - Print help summary.
ls           - List names of files on remote server.
put filename - Copy local file to remote host.
rm filename  - Remove file from remote server.
)||";

void cxi_help() {
   cout << help;
}

void cxi_ls (client_socket& server) {
   cxi_header header;
   header.command = cxi_command::LS;
   outlog << "sending header " << header << endl;
   send_packet (server, &header, sizeof header);
   recv_packet (server, &header, sizeof header);
   outlog << "received header " << header << endl;
   if (header.command != cxi_command::LSOUT) {
      outlog << "sent LS, server did not return LSOUT" << endl;
      outlog << "server returned " << header << endl;
   }else {
      size_t host_nbytes = ntohl (header.nbytes);
      auto buffer = make_unique<char[]> (host_nbytes + 1);
      recv_packet (server, buffer.get(), host_nbytes);
      outlog << "received " << host_nbytes << " bytes" << endl;
      buffer[host_nbytes] = '\0';
      cout << buffer.get();
   }
}

void cxi_get (client_socket& server, string file){
   cxi_header header;
   header.command = cxi_command::GET;
   char *cstr = &file[0];
   strcpy(header.filename,cstr);
   
   cout<<header.filename<<endl;
   send_packet (server, &header, sizeof header);
   recv_packet (server, &header, sizeof header);
   outlog << "received header " << header << endl;
   if (header.command != cxi_command::FILEOUT){
      outlog << "sent GET, server did not return FILEOUT" << endl;
      outlog << "server returned " << header << endl;
   }
   else{
      char* buffer = new char[header.nbytes + 1];
      recv_packet (server, buffer, header.nbytes); //payload
      outlog << "received " << header.nbytes << " bytes" << endl;
      buffer[header.nbytes] = '\0';
      ofstream targetFile(header.filename, std::ofstream::binary);
      targetFile.write(buffer, header.nbytes);
      delete[] buffer;
   }
}

void cxi_put(client_socket& server, string file) {

   cxi_header header; 
   char *cstr = &file[0];
   strcpy(header.filename,cstr);
   std::ifstream targetFile (header.filename, std::ifstream::binary);

   if (targetFile) {
      targetFile.seekg(0, targetFile.end);
      int length = targetFile.tellg();
      targetFile.seekg(0, targetFile.beg);
      char* buffer = new char[length];

      targetFile.read(buffer, length); 

      header.command = cxi_command::PUT;
      header.nbytes = length;
      send_packet (server, &header, sizeof header); //header
      send_packet (server, buffer, length); //payload
      recv_packet (server, &header, sizeof header); //receive
   }
   else 
      cerr << "Error: file not found: " << file << endl;

   if (header.command == cxi_command::ACK)
      cout << "ACK received: succesfully put file on the server" 
      << endl;
   else if (header.command == cxi_command::NAK)
      cerr << "NAK received: failed to put file on server" << endl;

   targetFile.close();
}

void cxi_rm(client_socket& server, string file) {
cxi_header header;
header.command = cxi_command::RM;
char *cstr = &file[0];
strcpy(header.filename,cstr);

header.nbytes = 0;
send_packet (server, &header, sizeof header);
recv_packet (server, &header, sizeof header);

if (header.command == cxi_command::ACK)
   cout << "ACK received: succesfully deleted file: " << 
   file << endl;
else if (header.command == cxi_command::NAK)
   cerr << "NAK received: failed to delete file: " << file << endl;
}

void usage() {
   cerr << "Usage: " << outlog.execname() << " [host] [port]" << endl;
   throw cxi_exit();
}

int main (int argc, char** argv) {
   outlog.execname (basename (argv[0]));
   outlog << "starting" << endl;
   vector<string> args (&argv[1], &argv[argc]);
   if (args.size() > 2) usage();
   string host = get_cxi_server_host (args, 0);
   in_port_t port = get_cxi_server_port (args, 1);
   outlog << to_string (hostinfo()) << endl;
   try {
      outlog << "connecting to " << host << " port " << port << endl;
      client_socket server (host, port);
      outlog << "connected to " << to_string (server) << endl;
      for (;;) {
         string line;
         getline (cin, line);
         if (cin.eof()) throw cxi_exit();
         //tokenize input with whitespace
         vector<string> tokens;
         stringstream temp(line);
         string intermediate;
         while(getline(temp, intermediate, ' ')) { 
            tokens.push_back(intermediate); 
         }
         outlog << "command " << tokens[0] << endl;
         const auto& itor = command_map.find (tokens[0]);
         cxi_command cmd = itor == command_map.end()
                         ? cxi_command::ERROR : itor->second;
         switch (cmd) {
            case cxi_command::EXIT:
               throw cxi_exit();
               break;
            case cxi_command::GET:
               cxi_get(server, tokens[1]);
               break;
            case cxi_command::PUT:
               cxi_put(server, tokens[1]);
               break;
            case cxi_command::RM:
               cxi_rm(server, tokens[1]);
               break;
            case cxi_command::HELP:
               cxi_help();
               break;
            case cxi_command::LS:
               cxi_ls (server);
               break;
            default:
               outlog << line << ": invalid command" << endl;
               break;
         }
      }
   }catch (socket_error& error) {
      outlog << error.what() << endl;
   }catch (cxi_exit& error) {
      outlog << "caught cxi_exit" << endl;
   }
   outlog << "finishing" << endl;
   return 0;
}

