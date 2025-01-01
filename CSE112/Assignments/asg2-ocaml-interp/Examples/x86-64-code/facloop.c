// $Id: facloop.c,v 1.1 2021-04-01 00:52:49-07 - - $
long factorial (long n) {
   long m = 1;
   while (n > 1) m *= n--;
   return m;
}
