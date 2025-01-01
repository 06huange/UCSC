// $Id: file_sys.cpp,v 1.7 2019-07-09 14:05:44-07 - - $

#include <iostream>
#include <stdexcept>
#include <unordered_map>
#include <iomanip>
using namespace std;

#include "debug.h"
#include "file_sys.h"

size_t inode::next_inode_nr {1};

struct file_type_hash {
   size_t operator() (file_type type) const {
      return static_cast<size_t> (type);
   }
};

ostream& operator<< (ostream& out, file_type type) {
   static unordered_map<file_type,string,file_type_hash> hash {
      {file_type::PLAIN_TYPE, "PLAIN_TYPE"},
      {file_type::DIRECTORY_TYPE, "DIRECTORY_TYPE"},
   };
   return out << hash[type];
}

inode_state::inode_state() {
   DEBUGF ('i', "root = " << root << ", cwd = " << cwd
          << ", prompt = \"" << prompt() << "\"");
   root = make_shared<inode>(file_type::DIRECTORY_TYPE);
   cwd = root;
   prev = root;
   root->contents->get_Dirents().insert(
      pair<string, inode_ptr>(".",root));
   root->contents->get_Dirents().insert(
      pair<string, inode_ptr>("..",root));
   inode_ptr dotdot = get_cdirectory()->
   get_Dirents().find("..")->second;
   dotdot->get_content()->s() = 2;
   inode_ptr dot = get_cdirectory()->get_Dirents().find(".")->second;
   dot->get_content()->s() = 2;
}

base_file_ptr inode_state::get_cdirectory() {
   return cwd->contents; 
}

string& inode_state::prompt() { return prompt_; }

string& inode_state::path() { return path_; }

ostream& operator<< (ostream& out, const inode_state& state) {
   out << "inode_state: root = " << state.root
       << ", cwd = " << state.cwd;
   return out;
}

inode::inode(file_type type): inode_nr (next_inode_nr++) {
   switch (type) {
      case file_type::PLAIN_TYPE:
           contents = make_shared<plain_file>();
           break;
      case file_type::DIRECTORY_TYPE:
           contents = make_shared<directory>();
           break;
   }
   DEBUGF ('i', "inode " << inode_nr << ", type = " << type);
}

base_file_ptr inode::get_content(){
   return contents;
}

int inode::get_inode_nr() const {
   DEBUGF ('i', "inode = " << inode_nr);
   return inode_nr;
}


file_error::file_error (const string& what):
            runtime_error (what) {
}

map<string,inode_ptr>& base_file::get_Dirents(){
   throw file_error ("is a " + error_file_type());
}

const wordvec& base_file::readfile() const {
   throw file_error ("is a " + error_file_type());
}

void base_file::writefile (const wordvec&) {
   throw file_error ("is a " + error_file_type());
}

void base_file::remove (const string&) {
   throw file_error ("is a " + error_file_type());
}

inode_ptr base_file::mkdir (const string&) {
   throw file_error ("is a " + error_file_type());
}

inode_ptr base_file::mkfile (const string&) {
   throw file_error ("is a " + error_file_type());
}

int& base_file::s () {
   throw file_error ("is a " + error_file_type());
}

int& base_file::index(){
   throw file_error ("is a " + error_file_type());
}


size_t plain_file::size() const {
   size_t size {0};
   DEBUGF ('i', "size = " << size);
   return size;
}

const wordvec& plain_file::readfile() const {
   DEBUGF ('i', data);
   return data;
}


void plain_file::writefile (const wordvec& words) {
   if(data.size() == 0){
      data = words;
   }
   else{
      for(auto i = words.begin(); i != words.end(); i++){
         data.push_back(*i);
      }
      data.pop_back();
      data.push_back("\n");      
   }
   for(size_t i=0; i< words.size(); i++){
      int temp = words[i].length();
      s() += temp;
   }
   DEBUGF ('i', words);
}

int& plain_file::s(){
   return s_;
}

int& plain_file::index(){
   return index_;
}

size_t directory::size() const {
   size_t size {0};
   DEBUGF ('i', "size = " << size);
   return size;
}

void directory::remove (const string& filename) {
   dirents.erase(filename);
   s()--;
   DEBUGF ('i', filename);
}

inode_ptr directory::mkdir (const string& dirname) {
   inode_ptr newDir = make_shared<inode>(file_type::DIRECTORY_TYPE);
   dirents.insert(pair<string,inode_ptr>(dirname,newDir));
   s() += 1;
   DEBUGF ('i', dirname);
   return newDir;
}

inode_ptr directory::mkfile (const string& filename) {
   inode_ptr newPointer = make_shared<inode>(file_type::PLAIN_TYPE);
   dirents.insert(pair<string,inode_ptr>(filename,newPointer));
   s() += 1;
   DEBUGF ('i', filename);
   return newPointer;
}

void directory::writefile (const wordvec& newdata) {
   if(newdata.size() > 0){
      cout<<"Error: invalid file type to intiate -- writefile\n";
   }
   return;
}

int& directory::s(){
   return s_;
}

int& directory::index(){
   return index_;
}

//helper -------------------------------------------

map<string,inode_ptr>& directory::get_Dirents(){
   return dirents;
}

inode_ptr& inode_state::get_cwd(){
   return cwd;
}

inode_ptr& inode_state::get_prev(){
   return prev;
}

inode_ptr& inode_state::get_root(){
   return root;
}

void inode_state::print_Dirents(string path){
   if(path == ""){
      cout<<"/:\n";
   }
   else{
      cout<<path<<":\n";
   }
   for(auto i = cwd->contents->get_Dirents().begin(); 
   i != cwd->contents->get_Dirents().end(); i++){
      cout<<"  "<<setw(3)<<left<<i->second->get_inode_nr();
      cout<<setw(3)<<right<<i->second->get_content()->s()<<"  ";
      if(i->second->contents->filetype() == "directory"){
         cout<< i->first<<"/\n";
      }
      else{
         cout<< i->first<<"\n";
      }
   }
}

string plain_file::filetype(){
   return "plain file";
}

string directory::filetype(){
   return "directory";
}

//void plain_file::get_Dirents(){ }
