#include "mattress.h"
#include <cstdio>

int main() {
  double av[] = {2., 3., -1., 5., 3., 2.},
         bv[] = {-3., 3., 1., -2., 0.5, -2., -3.5, 4.};
  Mattress a(av, 3, 2), b(bv, 2, 4);
  a.print(stdout, {});
  puts("");
  b.print(stdout, {});
  puts("");
  // Mattress sum = a + b;
  // sum.print(stdout, {});
  // puts("");
  // Mattress sub = a - b;
  // sub.print(stdout, {});
  // puts("");
  Mattress mul = a * b;
  mul.print(stdout, {});
  puts("");
  // Mattress krn = a ^ b;
  // krn.print(stdout, {});
  // puts("");
  Mattress neg = -a;
  neg.print(stdout, {});
  puts("");
  Mattress tns = ~a;
  tns.print(stdout, {});
  puts("");
  return 0;
}
