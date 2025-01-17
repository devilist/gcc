/* { dg-do compile } */
/* { dg-options "-mno-speculate-indirect-jumps" } */

/* Test for deliberate misprediction of jump tables.  */

void bar (void);

int foo (int x)
{
  int a;
  
  switch (x)
    {
    default:
      a = -1;
      break;
    case 0:
      a = x * x;
      break;
    case 1:
      a = x + 1;
      break;
    case 2:
      a = x + x;
      break;
    case 3:
      a = x << 3;
      break;
    case 4:
      a = x >> 1;
      break;
    case 5:
      a = x;
      break;
    case 6:
      a = 0;
      break;
    case 7:
      a = x * x + x;
      break;
    }

  bar();

  return a;
}

/* The following assumes CR7 as the first chosen volatile.  */

/* { dg-final { scan-assembler "crset 30" } } */
/* { dg-final { scan-assembler "beqctr- 7" } } */
/* { dg-final { scan-assembler "b ." } } */
