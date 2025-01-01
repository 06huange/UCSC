// $Id: facrec.c,v 1.1 2021-04-01 00:52:49-07 - - $
static long factorial_private (long n, long m) {
   if (n < 1L) return m;
   return factorial_private (n - 1L, m * n);
}
extern long factorial (long);
long factorial (long n) {
   return factorial_private (n, 1L);
}
