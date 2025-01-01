// $Id: ubigint.cpp,v 1.10 2020-10-11 12:25:22-07 - - $

#include <cctype>
#include <cstdlib>
#include <exception>
#include <stack>
#include <stdexcept>
using namespace std;

#include "debug.h"
#include "relops.h"
#include "ubigint.h"

ubigint::ubigint (unsigned long that) {
   while (that > 0){
      ubig_value.push_back((that%10) + '0');
      that/=10;
   }
   //DEBUGF ('~', this << " -> " << ubig_value);
}

ubigint::ubigint (const string& that) {
   DEBUGF ('~', "that = \"" << that << "\"");
   for (auto it = that.rbegin(); it != that.rend(); it++){
      ubig_value.push_back(*it);
      DEBUGF ('~', *it);
   }
}

ubigint ubigint::operator+ (const ubigint& that) const {
   DEBUGF ('u', *this << "+" << that);
   ubigint result;
   int carry = 0;
   int temp = 0;
   int i = 0;

   while(i < ubig_value.size() or i < that.ubig_value.size()){
      temp = carry;

      if(i < ubig_value.size()){
         temp += ubig_value[i] - '0';
      }
      if(i < that.ubig_value.size()){
         temp += that.ubig_value[i] - '0';
      }
      result.ubig_value.push_back((temp%10) + '0');
      i++;
      carry = temp/10;
   }
   if(carry != 0){
      result.ubig_value.push_back((carry) + '0');
   }

   //DEBUGF ('u', result);
   while (result.ubig_value.size() > 0 and
      result.ubig_value.back() == 0+'0') {
      result.ubig_value.pop_back();
   }
   return result;
}

ubigint ubigint::operator- (const ubigint& that) const {
   ubigint result;

   if (*this < that) throw domain_error ("ubigint::operator-(a<b)");

   int i = 0;
   int borrow = 0;
   int temp = 0;
   while(i < ubig_value.size()){
      temp = ubig_value[i] - '0' - borrow;
      if(i < that.ubig_value.size()){
         temp -= that.ubig_value[i] - '0';
      }
      if(temp < 0){
         temp += 10;
         borrow = 1;
      }
      else{
         borrow = 0;
      }
      result.ubig_value.push_back(temp + '0');
      i++;
   }
   while (result.ubig_value.size() > 0 and
      result.ubig_value.back() == 0+'0') {
      result.ubig_value.pop_back();
   }
   return result;
}

ubigint ubigint::operator* (const ubigint& that) const {
   ubigint result;
   for(size_t i=0; i < ubig_value.size() + that.ubig_value.size(); i++) result.ubig_value.push_back('0' + 0);
   for (size_t i=0; i < ubig_value.size(); i++){
      int c = 0;
      for (size_t j=0; j < that.ubig_value.size(); j++){
         int d = result.ubig_value[i+j] - '0';
         d += (ubig_value[i] - '0') * (that.ubig_value[j] - '0');
         d += c;
         result.ubig_value[i+j] = (d % 10) + '0';
         c = d/10;
      }
      result.ubig_value[i+that.ubig_value.size()] = c + '0';
   }
   while (result.ubig_value.size() > 0 and
      result.ubig_value.back() == 0+'0') {
      result.ubig_value.pop_back();
   }
   return result;
}

void ubigint::multiply_by_2() {
   int carry = 0;
   int curr;
   for(size_t i=0; i<ubig_value.size(); i++){
      curr = ubig_value[i] - '0';
      curr *= 2;
      curr += carry;
      if(curr >= 10){
         carry = 1;
         curr -= 10;
      }
      else{
         carry = 0;
      }
      ubig_value[i] = curr + '0';
   }

   if(carry != 0){
      ubig_value.push_back(carry + '0');
   }
}

void ubigint::divide_by_2() {
   int curr;
   size_t i;
   for(i=0; i<ubig_value.size(); i++){
      curr = ubig_value[i] - '0';
      curr /= 2;
      if((i+1)<ubig_value.size()){
         if((ubig_value[i+1] - '0') % 2 != 0) curr += 5;
      }
      ubig_value[i] = curr + '0';
   }
   while (ubig_value.size() > 0 and
      ubig_value.back() == 0+'0') {
      ubig_value.pop_back();
   }
}


struct quo_rem { ubigint quotient; ubigint remainder; };
quo_rem udivide (const ubigint& dividend, const ubigint& divisor_) {
   // NOTE: udivide is a non-member function.
   ubigint divisor {divisor_};
   ubigint zero {0};
   if (divisor == zero) throw domain_error ("udivide by zero");
   ubigint power_of_2 {1};
   ubigint quotient {0};
   ubigint remainder {dividend}; // left operand, dividend
   while (divisor < remainder) {
      divisor.multiply_by_2();
      power_of_2.multiply_by_2();
   }
   while (power_of_2 > zero) {
      if (divisor <= remainder) {
         remainder = remainder - divisor;
         quotient = quotient + power_of_2;
      }
      divisor.divide_by_2();
      power_of_2.divide_by_2();
   }
   return {.quotient = quotient, .remainder = remainder};
}

ubigint ubigint::operator/ (const ubigint& that) const {
   return udivide (*this, that).quotient;
}

ubigint ubigint::operator% (const ubigint& that) const {
   return udivide (*this, that).remainder;
}

bool ubigint::operator== (const ubigint& that) const {
   // check of the lengths of the vectors are the same
   if (ubig_value.size() != that.ubig_value.size()) return false;
   //iterate through both vectors and check
   for (int i = ubig_value.size() - 1; i >= 0; i--) {
      if (ubig_value[i] != that.ubig_value[i]) return false;
   }
   return true;
}

bool ubigint::operator< (const ubigint& that) const {
   //return ubig_value < that.ubig_value;
   if (ubig_value.size() != that.ubig_value.size()) {
      return ubig_value.size() < that.ubig_value.size();
   }
   if ((*this) == that) return false;
   // Compare higher order number
   for (int i = ubig_value.size() - 1; i >= 0; i--) {
      if(ubig_value[i] < that.ubig_value[i]){
         return true;
      }
      else if (that.ubig_value[i] < ubig_value[i]) {
         return false;
      }
   }

   return false;
}

ostream& operator<< (ostream& out, const ubigint& that) {
   if (that.ubig_value.size() == 0) out << "0";
   int charCount = 0;
   
   for (int i=that.ubig_value.size() - 1; i>=0; i--){
      out << (that.ubig_value[i] - '0');
      if (charCount == 68) {
         out << "\\" << endl;
         charCount = 0;
      }
      else{
         charCount++;
      }
   }
   return out;
}

