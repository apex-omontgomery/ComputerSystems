	/*
 * CS:APP Data Lab
 *
 * bits.c - Source file with your solutions to the Lab.
 *          This is the file you will hand in to your instructor.
 *
 * WARNING: Do not include the <stdio.h> header; it confuses the dlc
 * compiler. You can still use printf for debugging without including
 * <stdio.h>, although you might get a compiler warning. In general,
 * it's not good practice to ignore compiler warnings, but in this
 * case it's OK.
 */

#include "btest.h"
#include <limits.h>
#include <stdio.h>

/*
 * Instructions to Students:
 *
 * STEP 1: Fill in the following struct with your identifying info.
 */
team_struct team =
{
   /* Team name: Replace with either:
      Your login ID if working as a one person team
      or, ID1+ID2 where ID1 is the login ID of the first team member
      and ID2 is the login ID of the second team member */
    "team",
   /* Student name 1: Replace with the full name of first team member */
   "William Montgomery",
   /* Login ID 1: Replace with the login ID of first team member */
   "42069",

   /* The following should only be changed if there are two team members */
   /* Student name 2: Full name of the second team member */
   "",
   /* Login ID 2: Login ID of the second team member */
   ""
};

#if 0
/*
 * STEP 2: Read the following instructions carefully.
 */

You will provide your solution to the Data Lab by
editing the collection of functions in this source file.

CODING RULES:

  Replace the "return" statement in each function with one
  or more lines of C code that implements the function. Your code
  must conform to the following style:

  int Funct(arg1, arg2, ...) {
      /* brief description of how your implementation works */
      int var1 = Expr1;
      ...
      int varM = ExprM;

      varJ = ExprJ;
      ...
      varN = ExprN;
      return ExprR;
  }

  Each "Expr" is an expression using ONLY the following:
  1. Integer constants 0 through 255 (0xFF), inclusive. You are
      not allowed to use big constants such as 0xffffffff.
  2. Function arguments and local variables (no global variables).
  3. Unary integer operations ! ~
  4. Binary integer operations & ^ | + << >>

  Some of the problems restrict the set of allowed operators even further.
  Each "Expr" may consist of multiple operators. You are not restricted to
  one operator per line.

  You are expressly forbidden to:
  1. Use any control constructs such as if, do, while, for, switch, etc.
  2. Define or use any macros.
  3. Define any additional functions in this file.
  4. Call any functions.
  5. Use any other operations, such as &&, ||, -, or ?:
  6. Use any form of casting.

  You may assume that your machine:
  1. Uses 2s complement, 32-bit representations of integers.
  2. Performs right shifts arithmetically.
  3. Has unpredictable behavior when shifting an integer by more
     than the word size.

EXAMPLES OF ACCEPTABLE CODING STYLE:
  /*
   * pow2plus1 - returns 2^x + 1, where 0 <= x <= 31
   */
  int pow2plus1(int x) {
     /* exploit ability of shifts to compute powers of 2 */
     return (1 << x) + 1;
  }

  /*
   * pow2plus4 - returns 2^x + 4, where 0 <= x <= 31
   */
  int pow2plus4(int x) {
     /* exploit ability of shifts to compute powers of 2 */
     int result = (1 << x);
     result += 4;
     return result;
  }


NOTES:
  1. Use the dlc (data lab checker) compiler (described in the handout) to
     check the legality of your solutions.
  2. Each function has a maximum number of operators (! ~ & ^ | + << >>)
     that you are allowed to use for your implementation of the function.
     The max operator count is checked by dlc. Note that '=' is not
     counted; you may use as many of these as you want without penalty.
  3. Use the btest test harness to check your functions for correctness.
  4. The maximum number of ops for each function is given in the
     header comment for each function. If there are any inconsistencies
     between the maximum ops in the writeup and in this file, consider
     this file the authoritative source.
#endif

/*
 * STEP 3: Modify the following functions according the coding rules.
 *
 *   IMPORTANT. TO AVOID GRADING SURPRISES:
 *   1. Use the dlc compiler to check that your solutions conform
 *      to the coding rules.
 *   2. Use the btest test harness to check that your solutions produce
 *      the correct answers. Watch out for corner cases around Tmin and Tmax.
 */
/* Copyright (C) 1991-2014 Free Software Foundation, Inc.
   This file is part of the GNU C Library.

   The GNU C Library is free software; you can redistribute it and/or
   modify it under the terms of the GNU Lesser General Public
   License as published by the Free Software Foundation; either
   version 2.1 of the License, or (at your option) any later version.

   The GNU C Library is distributed in the hope that it will be useful,
   but WITHOUT ANY WARRANTY; without even the implied warranty of
   MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the GNU
   Lesser General Public License for more details.

   You should have received a copy of the GNU Lesser General Public
   License along with the GNU C Library; if not, see
   <http://www.gnu.org/licenses/>.  */
/* This header is separate from features.h so that the compiler can
   include it implicitly at the start of every compilation.  It must
   not itself include <features.h> or any other header that includes
   <features.h> because the implicit include comes before any feature
   test macros that may be defined in a source file before it first
   explicitly includes a system header.  GCC knows the name of this
   header in order to preinclude it.  */
/* glibc's intent is to support the IEC 559 math functionality, real
   and complex.  If the GCC (4.9 and later) predefined macros
   specifying compiler intent are available, use them to determine
   whether the overall intent is to support these features; otherwise,
   presume an older compiler has intent to support these features and
   define these macros by default.  */
/* wchar_t uses IS		O/IEC 10646 (2nd ed., published 2011-03-15) /
   Unicode 6.0.  */
/* We do not support C11 <threads.h>.  */
//
// 15 problems, 40 points
// 2 - rating 1
// 5 - rating 2
// 4 - rating 3
// 4 - rating 4




// rating 1
	/*
 * bitNor - ~(x|y) using only ~ and &
 *   Example: bitNor(0x6, 0x5) = 0xFFFFFFF8
 *   Legal ops: ~ &
 *   Max ops: 8
 *   Rating: 1
 */
int bitNor(int x, int y) {
// The logical equivalent to not (x or y) is (not x) and (not y)
return (~x&~y);
}




/*
 * TMax - return maximum two's complement integer
 *   Legal ops: ! ~ & ^ | + << >>
 *   Max ops: 4
 *   Rating: 1
 */
int tmax(void) {

// for a 32 bit word (2s complement) need to spit out 0111 1111 1111 1111 1111 1111 1111 1111
// As long as we start with a value that has a 1 in it, we can left shift that one all the way to the -2^31 position. 
// This will give us 1000 0000 0000 0000 0000 0000 0000 0000. This will give us the 2s complement highest negative value. 
// reverse all bits by using ~ operator. This will spit out the 2s complement maximum integer. 
  return ~(1 << 31);
}






// rating 2
/*
 * fitsBits - return 1 if x can be represented as an
 *  n-bit, two's complement integer.
 *   1 <= n <= 32
 *   Examples: fitsBits(5,3) = 0, fitsBits(-4,3) = 1
 *   Legal ops: ! ~ & ^ | + << >>
 *   Max ops: 15
 *   Rating: 2
 */
int fitsBits(int x, int n) {
// first make a mask using 33 plus the complement of the bits wanted. At first I tried 31 and 32, but found out 33 was correct.
// In this case ~n = (n+1)*-1.
	int sign = 33 + ~n;
// 33 + ~n gives us a positive value less than 33 if n is positive.
	int x1; int x2;
// these will be the test case holders
	x1 = x << sign;
// Now we shift the value by the number given in sign. This has the effect of removing any digits that wouldn't be included if you can't represent 
// x with n bits. After right shift back to return to original place.
	x2 = x1 >> sign;
// This is the logical step, We compare the masked x2 with the original x. 
// if we started with 0101, and wanted to represent it in 2 bits, x2 would now be 0001. (0101)^(0001) would return (0100)
// Now This gives us a value that not 1, by using logical not, we will get 0.
// if x can be represented by n, we will get a final value for x and x2 that are equal. (x^x2)= 0. 
// !0 = 1. 
	return !(x^x2);

}










/*
 * divpwr2 - Compute x/(2^n), for 0 <= n <= 30
 *  Round toward zero
 *   Examples: divpwr2(15,1) = 7, divpwr2(-33,4) = -2
 *   Legal ops: ! ~ & ^ | + << >>
 *   Max ops: 15
 *   Rating: 2
 */
int divpwr2(int x, int n) {
// Found out that right shifting once only works if x is a positive integer. Since we cannot use logical statements need to create a conditional mask. 
// Two problems with right shifting negative: right shift nevgative numbers rounds away from 0. Right shift -1 (all 1) returns -1.
// Goal: Create mask that doesn't mask positive numbers, but provides a mask that returns 0 for -1 right shift. or 0 for any neg number that should be 0. 
// Goal (contd): Provide a mask that ensures rounding to 0.
        int maskFin = 0;
// create mask: 
	int mask1= 1 << n; // this sets the (n+1) bit to 1. 
        int maskX = x >> 31; // This will create one of two masks (0xFFFFFFFF = ~0 or 0x0= 0). The positive x case has a mask of 0. The negative x case has a mask of ~0.
	mask1 += ~0; // Adds mask and the 0xFFFFFFFF mask to create new mask where bit 0 to bit n are 1, and all other bits are 0. 
	
	// For the positive case we need to make sure there is no mask So combine mask and maskX by & them. This will return mask of 0.
        maskFin = maskX & mask1; // This either returns maskX for the positive case: 0x0. Or mask1 for the negative case: 000000011111 (or the like). 
        maskFin = maskFin+x; // This will return x if x is positive since x mask = 0; This will return 
	return (maskFin >> n);

// x = 11, n = 1;
// 1
// rsh | (-) mask |  2^n
//  0      0         1
//  1      1         2
//  2      3         4
//  3      7         8
//  4      15        16
// The pattern here is that this accounts for the rounding down. This was actually unintentional, as I was only working on the returning the case where negative is shifted to 0.
// Since the pattern is continually rounding the wrong way. The mask gets lost after the right shift by n. But this essentially adds 1 to the total value. Causing the rounding to work the right way.


return (x>>n);// 
}




/*
 * isNotEqual - return 0 if x == y, and 1 otherwise
 *   Examples: isNotEqual(5,5) = 0, isNotEqual(4,5) = 1
 *   Legal ops: ! ~ & ^ | + << >>
 *   Max ops: 6
 *   Rating: 2
 */
int isNotEqual(int x, int y) {
	
 // Like the fitsbits, we had to mask first, but in the end we had to check if they are equal. 
 // in fitsbits, if they are equal we wanted to spit out a 1, but now we want to spit out a 0. 
 // Use same comparison, but negate that value. The first ! masks any weird bits. 
   return !(!(x^y));
   
}



/*
 * bitXor - x^y using only ~ and &
 *   Example: bitXor(4, 5) = 1
 *   Legal ops: ~ &
 *   Max ops: 14
 *   Rating: 2
 00000.....100
 00000.....101
--------^------
 00000.....001
 
 11111.....011
 11111.....010
 -------&-----
 11111.....010
 */
int bitXor(int x, int y) {
  // nor/ and are opposites. See Page 8 notes for reasoning. 
	// Essentially I tried a bunch of simple laws, and I saw a pattern.
	// x   y    xor    nor    and  (nor) nor (and)
	// 1   1     0     0       1       0
	// 1   0     1     0       0       1
	// 0   1     1     0       0       1
	// 0   0     0     1       0       0
	// At this point I saw that if I were to nor the and and nor.
	// The right  result would occur. 
	int Op1 = ~x&~y;
	int Op2 = x&y;
	return (~Op1 & ~Op2);

}




/*
 * copyLSB - set all bits of result to least significant bit of x
 *   Example: copyLSB(5) = 0xFFFFFFFF, copyLSB(6) = 0x00000000
  0000....0101 // 5
  0000....0110 // 6
  // find lsb = 0 or 1
  // set all bits to 0 or 1
  // maybe left shift 31 times, then right sift 31 times. 
 
 
 *   Legal ops: ! ~ & ^ | + << >>
 *   Max ops: 5
 *   Rating: 2
 */
 
 
 
int copyLSB(int x) {
// twos complement arithmetic right shift preserves the value in the "-2^31" location. So move the least significant value there. Then shift all the way back.

	// either return 0xFFFFFFFF or 0x00000000
	x =x<<31; // this will give value of 1000 0000 0000 0000 000 0000 0000 0000 or 0000 0000 0000 0000 000 0000 0000 0000

	
  return (x>> 31); // this will return 1111 1111 1111 1111 1111 1111 1111 1111 or 0000 0000 0000 0000 000 0000 0000 0000
}





// rating 3
/*
 * reverseBytes - reverse the bytes of x
 *   Example: reverseBytes(0x01020304) = 0x04030201
// Need to swap all bits, 


 *   Legal ops: ! ~ & ^ | + << >>
 *   Max ops: 25
 *   Rating: 3
 */
int reverseBytes(int x) {
	// there are 4 bytes in 32 bits. 
	// need 4 masks. 
	// 0xFF, 0xFF00, 0xFF0000, 0xFF000000. This last mask is the same as a right shifting until first byte is all the way on the left. 
	// use these masks to create the bytes in the right area. byte 1-> 4, byte 2->3, byte 3->2, byte 4->1.
	int part1, part2, part3, part4, mask1, mask2;
	part1 = (x >> 24) &  0xFF; // This shifts byte 4 all the way to bit 0 position. Then removes any values that arithmatically got shifted. 
	// cannot use 0xFF00, need to create
	// cannot use 0FF0000 need to create
	mask1 = 0xFF<<8;
	mask2 = mask1<<8;

	part2 = (x >> 8 ) & mask1; // Shifts byte 3 to where byte 2 was. The mask ensures only bits in this new position have 1s. 
	part3 = (x << 8)  & mask2; // Shifts byte 2 to where byte 3 was. Masks bits at byte 1, 2, 4. 
	part4 = (x << 24); // no need to mask, as the left shit places in zeros at byte 1, 2, 3. 
	// now we have 4 integers, with bytes in the correct location, I think I can use either "|" or the addition. Will need to try addition later. 
	return (part1+part2+part3+part4);
	

}





/*
 * logicalShift - shift x to the right by n, using a logical shift
 *   Can assume that 1 <= n <= 31
 *   Examples: logicalShift(0x87654321,4) = 0x08765432
 *   Legal ops: ~ & ^ | + << >>
 *   Max ops: 16
 *   Rating: 3
 */
int logicalShift(int x, int n) {
 // this will shift to right with the the highest n bits being 0. 
 // If we shift n times, we need n 0's starting from 2^31. So we need a mask where it's 0000(n=0)111....1111111. in this case int n=5. 
 int mask = ~0;// initialize all 1s. 
// shift to right until 1 in n position. 
 mask = ~(mask <<( 33+ ~n)); // 33 + ~n = 32 + (~n+1). Since n is a positive number (-n shift not defined). we take the 2s complement. and add it to number of bits. 
// Then we take the not, to get us the mask wanted. Finally we can take the arithmatic shift, and & mask and x. to preserve important bits and lose the 1s that need to be lsot.

x = x>> n; 
return( x&mask);
}





/*
 * isGreater - if x > y  then return 1, else return 0
 *   Example: isGreater(4,5) = 0, isGreater(5,4) = 1
 *   Legal ops: ! ~ & ^ | + << >>
 *   Max ops: 24
 *   Rating: 3
 */
int isGreater(int x, int y) {

//printf("%d\n",x);
//printf("%d\n",y);
//printf("%d\n\n",!((x+~y)>>31));
//return !((x+~y)>>31); // this works in most cases. only doesn't work in one case (x +, y negative)
int x_val, y_val, y_fix, issue;
issue = !((x+~y)>>31);
x_val = x >>31;
y_val = y >>31; 
 

// if x is positive and y negative return  1, otherwise return "issue"

y_fix = (!x_val)&y_val; // returns 1 if x pos, y neg. 
issue = issue&((!x_val)|y_val); //  // Uses & to combine the case that is mostly right, with the fix for the one odd case. 
return(y_fix|issue);


//return 2;




}





/*
 * bitMask - Generate a mask consisting of all 1's
 *   lowbit and highbit
 *   Examples: bitMask(5,3) = 0x38
 *   Assume 0 <= lowbit <= 31, and 0 <= highbit <= 31d
 *   If lowbit > highbit, then mask should be all 0's
 *   Legal ops: ! ~ & ^ | + << >>
 *   Max ops: 16
 *   Rating: 3
// bitmask (5,3) makes a mask that has 1 at 3rd position to 1 at 5th position
// 0011 1000

 */
int bitMask(int highbit, int lowbit) {
// cannot shift a negative value. not defined in c. 

// Create two masks, and find overlap?
/* This didn't work
int mask1 = 0x8000000>> (32-lowbit); // 31-4 = 27.  // I think it's because of the use of additions with the shift causing weird errors. 
int mask2 = 1 << (highbit); //highbit = 8
mask2 = mask2 + ~0;
return ~(mask1|mask2);
*/ // Try the opposite, create two masks that when "|" and then not create desired mask.
// the use of highbit or lowbit +/- is causing issues with the edge cases around 0 or 31. 

int Lmask = ~0 << highbit; // creates a mask where there are 1's in the place of hb and up. cannot use 0xFFFFFFFF
int Rmask = ~(~0 << lowbit); // creates a mask where there are 1's in the place of lb and below. 
// The issue is I want to left shift Lmask by one more but this leads to issues with hb=31. Need to mask the hb with a zero. 
// One way of doing this is to create another mask and and the two, since Lmask always has zeros below the hb, shift a 1 highbit 
// to get the 1 to desired location, and then not the whole word. 
int HBmask = ~(1 << highbit);
// combine HBmask and Lmask using and, to get a mask where there are 1s above hb and zeros every else.
int Lmask2= Lmask&HBmask;
// Finally we 'or' the bits from both masks, and take the not.

return ~(Lmask2|Rmask);


}







// rating 4
/*
 * abs - absolute value of x (except returns TMin for TMin)
 *   Example: abs(-1) = 1.
 *   Legal ops: ! ~ & ^ | + << >>
 *   Max ops: 10
 *   Rating: 4
 */
int abs(int x) {
 // return (~x+1);The obvious solution doesn't work becuase we don't know the 2^31 sign. Lets find that first. 
int sign = x >> 31; // This will give us either 0 or ~0
 // x sign |  sign value |   wanted result
 //  +       0000....0000      x
 //  -       1111....1111      -x

// how do I return -x with ~0 and x. 
// we want to give the ~x when it's negative and then add one. 
// So how do we reverse bits of x when sign = ~0, and keep the same when sign = 0. 
// XOR does that... 0011 0011 0101 0101 ^ 1111  1111 1111 1111= 1100 1100 1010 1010, so how do I use this? Check xor with 0.
// 0011 0011 0101 0101 ^ 0 = 0011 0011 0101 0101. 
// so x^(x>>31) returns x, while x is positive. and ~x = -1-x. so need to add one to ~x, but only if x is negative. 
//negative case
//x^(sign) + 1// how do I only add one if sign = ~0 What if I add 1 to sign, and then not it?
// 1+sign two possible options.
// 1+ ~0 = 0. ~0 =1. 
// 1+ 0 = 1. !1 = 0. 
return ((x^sign) + !(1+sign));


  	

}




/*
 * bitCount - returns count of number of 1's in word
 *   Examples: bitCount(5) = 2, bitCount(7) = 3
 *   Legal ops: ! ~ & ^ | + << >>
 *   Max ops: 40
 *   Rating: 4
 */
int bitCount(int x) { 
// grouping is done by masking and shifting
// If we add the bits by doing incremental shifts, we can group the word as such.
// _ _, _ _ (first grouping) this has a max value of 2 = 0010 (mask the even bits)
// _ _  _ _,  (second grouping) this has a max value of 4 = 0100 (bits 2 and 3, in every 3 bit grouping (starting at 0))
// _ _  _ _  _ _  _ _ , (third grouping) this has a max value of 8 = 01000 (mask the 4-7 bit in a 7 bit grouping (starting at 0))
// _ _  _ _  _ _  _ _  _ _  _ _  _ _  _ _, (fourth grouping) has a max value of 16 - 010000 
// all value = 1. (fifth grouping), max value of 32 =0100000

// Each grouping needs to mask the location where the sum shouldn't be. 
// First sum is every even bit (2^(0,2,4,6,8..))

int count = 0; 
//naming scheme mask2 = max value of 2 after addition

//int mask2  = 0x55555555;  // 0101 0101 0101 0101 0101 0101 0101 0101, not sure if I need to mask the 2^0 position. 
//int mask4  = 0x33333333;  // 0011 0011 0011 0011 0011 0011 0011 0011
//int mask8  = 0x0F0F0F0F;  // 0000 1111 0000 1111 0000 1111 0000 1111 
//int mask16 = 0x00FF00FF;  // 0000 0000 1111 1111 0000 0000 1111 1111

int mask2, mask4,mask8,mask16,mask32;
// so I cannot use these and I have to make them. 

    //mask2  = 0x55555555;  // 0101 0101 0101 0101 0101 0101 0101 0101, not sure if I need to mask the 2^0 position. 
  
    mask2  = 0x55+(0x55<<8);
    mask2  = mask2+ (mask2 << 16);
  //int mask2  = 0x55555555;  // 0101 0101 0101 0101 0101 0101 0101 0101, not sure if I need to mask the 2^0 position. 

    mask4  = 0x33+(0x33<<8); // 0011 0011 0011 0011 0011 0011 0011 0011
    mask4  = mask4 + (mask4 << 16);
//int mask4  = 0x33333333;  // 0011 0011 0011 0011 0011 0011 0011 0011

    mask8  = 0x0F+(0x0F<<8); // 0000 1111 0000 1111 0000 1111 0000 1111 
    mask8 = mask8 +(mask8 << 16);
//int mask8  = 0x0F0F0F0F;  // 0000 1111 0000 1111 0000 1111 0000 1111 

    mask16 = 0xFF+(0xFF<<16);  // 0000 0000 1111 1111 0000 0000 1111 1111
//int mask16 = 0x00FF00FF;  // 0000 0000 1111 1111 0000 0000 1111 1111

 mask32 = ~(~0<<16); // 0000 0000 0000 0000 1111 1111 1111 1111
     // mask32 = 0x0000FFFF;  // 0000 0000 0000 0000 1111 1111 1111 1111





// now we need to add the bits while shifting and using a mask.

// mask2, shift once. mask4 = shift 2. mask8 = shift 4. mask16 = shift 8. mask32= shift16.
count = (x&mask2)+ ((x>>1)&mask2); 
count = (count&mask4)+ ((count>>2)&mask4); 
count = (count&mask8)+ ((count>>4)&mask8); 
count = (count&mask16)+ ((count>>8)&mask16);
count = (count&mask32)+ ((count>>16)&mask32);
return(count);
  
  
  
  
  return 2;
}







/*
 * isNonZero - Check whether x is nonzero using
 *              the legal operators except !
 *   Examples: isNonZero(3) = 1, isNonZero(0) = 0
 *   Legal ops: ~ & ^ | + << >>
 *   Max ops: 10
 *   Rating: 4
 */
int isNonZero(int x) {
// see Solution for bang, I started on that one first, and saw that I solved this one if I stopped at the final XOR. 
int Negx= 1+~x; 
x = x>> 31; 
Negx = Negx >> 31;
Negx = Negx&1; 
x = x&1;  
return(x|Negx);
}




/*
 * bang - Compute !x without using !
 *   Examples: bang(3) = 0, bang(0) = 1
 // return 1 if input = 0, all others return 0. 


*   Legal ops: ~ & ^ | + << >>
 *   Max ops: 12
 *   Rating: 4
 */
int bang(int x) {
 

//returns 0 if anything but 0. Returns 1 if 0. 

// lets look at x and (-1)*x.
// this is 1+ ~x. 
int Negx= 1+~x; 
// by taking this we will get 0 for both x and Negx if x =0. Any other value of x will spit out a number that has a 1 at the last bit if you look at both x
// and Negx
x = x>> 31; 
Negx = Negx >> 31; // Doing this will get a 1 at the 2^0 place for at least one of these. (unless x=0).
// We want it to return a 1 for 0, and a 0 for everything else. mask 2^1->2^31?
Negx = Negx&1; 
x = x&1;  // This will create a number for both that is either 0x0, or 0x1. Maybe combine both somehow so we can spit out a 0 or 1? while retaining the 1.
// this one is the original bit that shows from taking the 1+~x, that lets us know that x=0.
// Negx | x // if NegX = x = 0. Want to spit out 1. but want 0 for all other cases. I can't think of a non ! that spits out 1. Lets mask 3 cases into 2 cases.
//   0    0 
//   1    0
//   0    1
// There shouldn't be a case where NegX and x are 1. This would only happen if x is negative, and so is the Neg_x. 	 
// NegX | x ? This keeps NegX=x=0, and puts a 1 for all other cases. // This is the exact opposite of what I want. So how do I get the correct result?
x = x|Negx;
// x_fin |  x_original
//   0         0
//   1         (anything but x)
// we want x_fin=0 to return as 1. 
// Try comparing it to another value.  x&0, works for all but x=0. | doesn't work, not doesn't work. try XOR.
return (x^1);
// Thank god it works.
}
