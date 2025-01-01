// $Id: bigint.cpp,v 1.3 2020-10-11 12:47:51-07 - - $

#include <cstdlib>
#include <exception>
#include <stack>
#include <stdexcept>
using namespace std;

#include "bigint.h"
#include "ubigint.h"

bigint::bigint (long that): uvalue (that), is_negative (that < 0) {
   DEBUGF ('~', this << " -> " << uvalue)
}

bigint::bigint (const ubigint& uvalue_, bool is_negative_):
                uvalue(uvalue_), is_negative(is_negative_) {
}

bigint::bigint (const string& that) {
   is_negative = that.size() > 0 and that[0] == '_';
   uvalue = ubigint (that.substr (is_negative ? 1 : 0));
}

bigint bigint::operator+ () const {
   return *this;
}

bigint bigint::operator- () const {
   return {uvalue, not is_negative};
}

bigint bigint::operator+ (const bigint& that) const {
   ubigint result = ubigint();
   //case 1 = same sign
   //return addition of both ints and keep sign
   if(is_negative == that.is_negative){
      result = uvalue.operator+(that.uvalue);
      return(bigint(result ,is_negative));
   }
   //case 2 = different sign
   else{
      if(uvalue.operator<(that.uvalue)){
         result = that.uvalue.operator-(uvalue);
         return(bigint(result, that.is_negative));
      }
      else{
         result = uvalue.operator-(that.uvalue);
         return(bigint(result, is_negative));
      }
   }
}

bigint bigint::operator- (const bigint& that) const {

   ubigint result;

   //case 1 = different sign
   //subtract
   if(is_negative != that.is_negative){
      result = uvalue + that.uvalue;
      return(bigint(result,is_negative));
   }
   //case 2 = same sign
   else{
      if(uvalue < that.uvalue){
         result = that.uvalue - uvalue;
         return (bigint(result, !that.is_negative));
      }
      else{
         result = uvalue - that.uvalue;
         return (bigint(result, is_negative));
      }
   }
}


bigint bigint::operator* (const bigint& that) const {
   ubigint result;

   result = uvalue * that.uvalue;
   if(is_negative == that.is_negative){
      return(bigint(result,false));     
   }
   else{
      return(bigint(result,true));
   }
}

bigint bigint::operator/ (const bigint& that) const {
   ubigint result;

   result = uvalue / that.uvalue;
   if(is_negative == that.is_negative){
      return(bigint(result,false));     
   }
   else{
      return(bigint(result,true));
   }
}

bigint bigint::operator% (const bigint& that) const {
   bigint result = uvalue % that.uvalue;
   return result;
}

bool bigint::operator== (const bigint& that) const {
   return is_negative == that.is_negative and uvalue == that.uvalue;
}

bool bigint::operator< (const bigint& that) const {
   if (is_negative != that.is_negative) return is_negative;
   return is_negative ? uvalue > that.uvalue
                      : uvalue < that.uvalue;
}

ostream& operator<< (ostream& out, const bigint& that) {

   return out << (that.is_negative ? "-" : "")
    << that.uvalue;

}

