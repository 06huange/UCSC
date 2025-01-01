// $Id: listmap.tcc,v 1.15 2019-10-30 12:44:53-07 - - $

#include "listmap.h"
#include "debug.h"

//
/////////////////////////////////////////////////////////////////
// Operations on listmap.
/////////////////////////////////////////////////////////////////
//

//
// listmap::~listmap()
//
template <typename key_t, typename mapped_t, class less_t>
listmap<key_t,mapped_t,less_t>::~listmap() {
   DEBUGF ('l', reinterpret_cast<const void*> (this));
   for(auto i = begin(); i != end();){
      i = erase(i);
   }
}

//
// iterator listmap::insert (const value_type&)
//
template <typename key_t, typename mapped_t, class less_t>
typename listmap<key_t,mapped_t,less_t>::iterator
listmap<key_t,mapped_t,less_t>::insert (const value_type& pair) {
   DEBUGF ('l', &pair << "->" << pair);

   node* p;
   node* ne;
   node* curr = begin().where;
   if (curr == end().where) {
      p = ne = end().where;
   } else {
      p = curr;
      ne = end().where;
      bool les = true;
      while(true){
         if(curr != end().where){
            if(less(curr->value.first,pair.first)){
               p = curr;
               ne = curr->next;
               curr = curr->next;
            }
            else {
               les = false;
               break;
            }
         }
         else{
            curr = curr->prev;
            break;
         }
      }
      if(curr == begin().where && !les){
         p = anchor();
         ne = curr;
      }
   }
   node* n = new node(ne, p, pair);
   p->next = n;
   ne->prev = n;
   
   return iterator(n);
}

//
// listmap::find(const key_type&)
//
template <typename key_t, typename mapped_t, class less_t>
typename listmap<key_t,mapped_t,less_t>::iterator
listmap<key_t,mapped_t,less_t>::find (const key_type& that) {
   DEBUGF ('l', that);
   if(begin() == end()) return end();
   for(auto i = begin(); i != end(); ++i){
      if(!(i->first < that) && !(that < i->first)) return i;
   }
   return end();
}

//
// iterator listmap::erase (iterator position)
//
template <typename key_t, typename mapped_t, class less_t>
typename listmap<key_t,mapped_t,less_t>::iterator
listmap<key_t,mapped_t,less_t>::erase (iterator position) {
   DEBUGF ('l', &*position);
   
   node* temp = position.where;
   ++position;
   temp->prev->next = temp->next;
   temp->next->prev = temp->prev;
   temp->next = nullptr;
   temp->prev = nullptr;
   delete temp;
   
   return position;
}

// LISTMAP::iterator

