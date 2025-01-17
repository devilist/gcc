/* { dg-do compile } */
/* { dg-options "-mno-speculate-indirect-jumps" } */

/* Test for deliberate misprediction of computed goto.  */

int bar (int);
int baz (int);
int spaz (int);

int foo (int x)
{
  static void *labptr[] = { &&lab0, &&lab1, &&lab2 };

  if (x < 0 || x > 2)
    return -1;

  goto *labptr[x];

 lab0:
  return bar (x);

 lab1:
  return baz (x) + 1;

 lab2:
  return spaz (x) / 2;
}

/* The following assumes CR7 as the first chosen volatile.  */

/* { dg-final { scan-assembler "crset 30" } } */
/* { dg-final { scan-assembler "beqctr- 7" } } */
/* { dg-final { scan-assembler "b ." } } */
