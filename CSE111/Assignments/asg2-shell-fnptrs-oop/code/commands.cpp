// $Id: commands.cpp,v 1.18 2019-10-08 13:55:31-07 - - $

#include "commands.h"
#include "debug.h"
#include <stack>
#include <sstream>
using namespace std;

command_hash cmd_hash {
   {"cat"   , fn_cat   },
   {"cd"    , fn_cd    },
   {"echo"  , fn_echo  },
   {"exit"  , fn_exit  },
   {"ls"    , fn_ls    },
   {"lsr"   , fn_lsr   },
   {"make"  , fn_make  },
   {"mkdir" , fn_mkdir },
   {"prompt", fn_prompt},
   {"pwd"   , fn_pwd   },
   {"rm"    , fn_rm    },
   {"rmr"    ,fn_rmr   },
};

command_fn find_command_fn (const string& cmd) {
   // Note: value_type is pair<const key_type, mapped_type>
   // So: iterator->first is key_type (string)
   // So: iterator->second is mapped_type (command_fn)
   DEBUGF ('c', "[" << cmd << "]");
   const auto result = cmd_hash.find (cmd);
   if (result == cmd_hash.end()) {
      throw command_error (cmd + ": no such function");
   }
   return result->second;
}

command_error::command_error (const string& what):
            runtime_error (what) {
}

int exit_status_message() {
   int status = exec::status();
   cout << exec::execname() << ": exit(" << status << ")" << endl;
   return status;
}

void fn_cat (inode_state& state, const wordvec& words){
   DEBUGF ('c', state);
   DEBUGF ('c', words);
   base_file_ptr dir = state.get_cdirectory();
   if(words.size()==1){
      cout << "cat: no file specified";
   }
   for(size_t j=1; j<words.size(); j++){
      auto key = dir->get_Dirents().find(words[j]);
      if (key != dir->get_Dirents().end()){
         vector<string> data = key->second->get_content()->readfile();
         for (auto i = data.begin(); i != data.end(); i++){
            cout<<*i<<" ";
         }
         cout<<"\n";
      }
      else {
         cout<<"cat: "<<words[1]<<": no file found\n";
      }
   }
   return;
}

void fn_cd (inode_state& state, const wordvec& words){
   /* The current directory is set the the pathname given. 
   If no pathname is specified, the root directory (/) is 
   used. It is an error if the pathname does not exist or 
   is a plain file, or if more than one operand is given.*/
   base_file_ptr dir = state.get_cdirectory();
   if(words.size()>2){
      cout<<"cd: "<<words[1]<<": More than one operand given\n";
      return;
   }
   if(words.size() == 1 || words[1] == "/"){
      state.get_cwd() = state.get_root();
      state.path() = "";
      return;
   }
   wordvec path = split(words[1],"/");

   inode_ptr curr = state.get_cwd();

   //search for directory
   for(auto i = path.begin(); i != path.end(); i++){
      auto key = dir->get_Dirents().find(*i);
      if (key == dir->get_Dirents().end()){
         cout<<"cd: "<<words[1]<<": Directory not found\n";
         state.get_cwd() = curr;
         return;
      }
      if (key->second->get_content()->filetype() == "plain file"){
         cout<<"cd: "<<words[1]<<
         ": invalid file type, plain file specified\n";
         state.get_cwd() = curr;
         return;
      }
      //files exists -- update file
      else{
         state.get_cwd() = key->second;
         state.path() += "/";
         state.path() += key->first;
         dir = state.get_cdirectory();
      }
   }

   //check if file already exists
   DEBUGF ('c', state);
   DEBUGF ('c', words);
}

void fn_echo (inode_state& state, const wordvec& words){
   DEBUGF ('c', state);
   DEBUGF ('c', words);
   cout << word_range (words.cbegin() + 1, words.cend()) << endl;
}


void fn_exit (inode_state& state, const wordvec& words){
   DEBUGF ('c', state);
   DEBUGF ('c', words);
   if(words.size()==2){
      if(isdigit(words[1][0]) != 0){
         stringstream temp(words[1]);
         int stat = 0;
         temp >> stat;
         exec::status(stat); 
      }
      else{
         exec::status(127);
      }
   }
   throw ysh_exit();
}

void fn_ls (inode_state& state, const wordvec& words){
   DEBUGF ('c', state);
   DEBUGF ('c', words);
   if(words.size() == 1 || words[1] == "/" || words[1] == "."){
      state.path() = "/";
      state.print_Dirents(state.path());
      return;
   }

   wordvec path = split(words[1],"/");
   inode_ptr curr = state.get_cwd();
   string originalPath = state.path();
   fn_cd(state,words);
   if (state.get_cwd() == curr){
      cout<<"ls: "<<words[1]<<": path not found\n";
   }
   else{
      state.print_Dirents(state.path());
      state.get_cwd() = curr;
   }
   state.path() = originalPath;
}

void fn_lsr (inode_state& state, const wordvec& words){
   /*As for ls, but a recursive depth-first preorder 
   traversal is done for subdi- rectories.*/
   if (words.size() == 1 || words[1] == "/"){
      lsr_recur(state);
      return;
   }
   wordvec path = split(words[1],"/");
   inode_ptr curr = state.get_cwd();
   fn_cd(state,words);
   if (state.get_cwd() == curr){
      cout<<"lsr: "<<words[1]<<": path not found\n";
   }
   else{
      lsr_recur(state);
   }
   
   DEBUGF ('c', state);
   DEBUGF ('c', words);
}

void fn_make (inode_state& state, const wordvec& words){
   /* The file specified is created and the rest of the words 
   are put in that file. If the file already exists, a new 
   one is not created, but its contents are replaced. 
   It is an error to specify a directory. If there are no 
   words, the file is empty. */
   base_file_ptr dir = state.get_cdirectory();
   string fileName = words[1];
   vector<string> info = {words.begin() + 2, words.end()};

   auto key = dir->get_Dirents().find(words[1]);
   //check if file already exists
   if (key == dir->get_Dirents().end()){
      inode_ptr newInode = dir->mkfile(words[1]);
      newInode->get_content()->writefile(info);
   }
   //files exists -- update file
   else{
      key->second->get_content()->writefile(info);
   }
   

   DEBUGF ('c', state);
   DEBUGF ('c', words);
}

void fn_mkdir (inode_state& state, const wordvec& words){
   inode_ptr curr = state.get_cwd();
   if(words.size() < 2){
      cout<<"mkdir: invalid operands";
      return;
   }
   wordvec path = split(words[1],"/");
   for(size_t j = 0; j<path.size(); j++){
      string fileName = path[j];
      base_file_ptr dir = state.get_cdirectory();
      auto key = dir->get_Dirents().find(fileName);
      //check if file already exists
      if (key == dir->get_Dirents().end()){
         inode_ptr newInode = dir->mkdir(fileName);
         newInode->get_content()->get_Dirents().insert(
            pair<string, inode_ptr>(".",newInode));
         newInode->get_content()->get_Dirents().insert(
            pair<string, inode_ptr>("..",state.get_cwd()));
         inode_ptr dotdot = newInode->get_content()->
         get_Dirents().find("..")->second;
         inode_ptr dot = newInode->get_content()->
         get_Dirents().find(".")->second;
         dot->get_content()->s() = 2;
         dotdot->get_content()->s() = dir->s();
         dot->get_content()->filetype() = "directory";
         dotdot->get_content()->filetype() = "directory";
         state.get_cwd() = newInode;
      }
      //files exists -- update file
      else{
         if(j==path.size()-1){
         cout<<"mkdir: "<<words[1]<<
         ": File name already exists in directory\n";
         break;
         }
         else{
            state.get_cwd() = state.get_cdirectory()->
            get_Dirents().find(path[j])->second;
         }
      }
   }
   state.get_cwd() = curr;
   DEBUGF ('c', state);
   DEBUGF ('c', words);
}

void fn_prompt (inode_state& state, const wordvec& words){
   string newprompt;
   for(auto i = words.begin(); i != words.end(); i++){
      newprompt += *i + " ";
   }
   state.prompt() = newprompt;
   DEBUGF ('c', state);
   DEBUGF ('c', words);
}

void fn_pwd (inode_state& state, const wordvec& words){
   base_file_ptr dir = state.get_cdirectory();
   state.print_Dirents(state.path());
   DEBUGF ('c', state);
   DEBUGF ('c', words);
}

void fn_rm (inode_state& state, const wordvec& words){
   base_file_ptr dir = state.get_cdirectory();
   auto key = dir->get_Dirents().find(words[1]);
   if (key == dir->get_Dirents().end()){
      cout<<"rm: "<<words[1]<<": file not found";
   }
   //files exists -- update file
   else{
      dir->remove(words[1]);
   }

   DEBUGF ('c', state);
   DEBUGF ('c', words);
}

void fn_rmr (inode_state& state, const wordvec& words){
   inode_ptr curr = state.get_cwd();
   if (words.size() == 1){
      cout<<"rmr: "<<": path not specified\n";
      return;
   }
   if(words[1] == "/"){
      cout<<"rmr"<<words[1]<<": invalid operand of /";
   }
   else{
      fn_cd(state,words);
      if (state.get_cwd() == curr){
         cout<<"rmr"<<words[1]<<": path not found\n";
         return;
      }
   }
   rmr_recur(state);

   state.get_cwd() = curr;

   
   DEBUGF ('c', state);
   DEBUGF ('c', words);
   DEBUGF ('c', state);
   DEBUGF ('c', words);

}

void lsr_recur (inode_state& state){
   state.print_Dirents(state.path());
   string originalPath = state.path();
   const inode_ptr curr = state.get_cwd();
   base_file_ptr dir = state.get_cdirectory();
   for(auto i = dir->get_Dirents().begin(); 
   i != dir->get_Dirents().end(); i++){
      if(i->second->get_content()->filetype() == "directory"
      && i->first != "." && i->first != ".."){
         state.get_cwd() = i->second;
         state.path() += "/";
         state.path() += i->first;
         lsr_recur(state);
      }
   }
   state.get_cwd() = curr;
   state.path() = originalPath;
}

void rmr_recur (inode_state& state){
   base_file_ptr dir = state.get_cdirectory();
   inode_ptr curr = state.get_cwd();
   for (auto i = dir->get_Dirents().begin(); 
   i != dir->get_Dirents().end(); i++){
      if(i->second->get_content()->filetype() == "directory"
      && i->first != "." && i->first != ".."){
         if(i->second->get_content()->s() == 2){
            dir->remove(i->first);
         }
         else{
            state.get_cwd() = i->second;
            rmr_recur(state);
            state.get_cwd() = curr;
            dir->remove(i->first);
         }
      }
      else if(i->second->get_content()->filetype() == "plain file"){
         dir->remove(i->first);
      }
   }
}
