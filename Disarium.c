#include <stdlib.h>
#include <stdio.h>

#ifndef DMAX
  #define DMAX (20)  // Max # of digits
#endif

#ifndef UNIT
  #define UNIT size_t
#endif

int
main( int argc, char *argv[] ) {
  int start = 0;  // Start # of digits
  int final = 0;  // Final # of digits

  if( argc > 2 ) {
    start = atoi( argv[2] );
  }
  if( start < 1 || DMAX < start ) {
    start = 1;
  }

  if( argc > 1 ) {
    final = atoi( argv[1] );
  }
  if( final < 1 || DMAX < final ) {
    final = DMAX;
  }

  // Pre-calculated exponential & power serials
  UNIT EXP[1 + DMAX][11] = {{0,0,0,0,0,0,0,0,0,0,1},{0,1,2,3,4,5,6,7,8,9,10}};
  UNIT POW[1 + DMAX][11] = {{0,0,0,0,0,0,0,0,0,0,0},{0,1,2,3,4,5,6,7,8,9, 9}};
  for( int i = 1; i < DMAX; i++ ) {
    for( int j = 0; j < 10; j++ ) {
      EXP[i + 1][j] = EXP[i][j] * 10;
      POW[i + 1][j] = POW[i][j] *  j;
    }
    EXP[i + 1][10] = EXP[i][10] * 10;
    POW[i + 1][10] = POW[i][10] + POW[i + 1][9];
  }

  // Digits of candidate and values of known low bits
  int DIGITS[1 + DMAX] = {0};  // Digits form
  UNIT   Exp[1 + DMAX] = {0};  // Number form
  UNIT   Pow[1 + DMAX] = {0};  // Powers form

  UNIT exp, pow;
  UNIT min, max;
  for( int digit = start; digit <= final; digit++ ) {
    printf( "# of digits: %d\n", digit );

    int level = 1;
    DIGITS[0] = 0;
    while( 1 ) {
      // Check limits derived from already known low bit values
      // to find the most possible candidates
      while( 0 < level && level < digit ) {
        // Reset path to try next if checking in level is done
        if( DIGITS[level] > 9 ) {
          DIGITS[level] = 0;
          level--;
          DIGITS[level]++;
          continue;
        }

        // Update known low bit values
        Exp[level] = Exp[level - 1] + EXP[level][DIGITS[level]];
        Pow[level] = Pow[level - 1] + POW[digit + 1 - level][DIGITS[level]];

        // Max possible value
        pow = Pow[level] + POW[digit - level][10];

        if( pow < EXP[digit][1] ) {  // Try next since upper limit is invalidly low
          DIGITS[level]++;
          continue;
        }

        max  = pow % EXP[level][10];
        pow -= max;
        if( max < Exp[level] ) {
          pow -= EXP[level][10];
        }
        max  = pow + Exp[level];

        if( max < EXP[digit][1] ) {  // Try next since upper limit is invalidly low
          DIGITS[level]++;
          continue;
        }

        // Min possible value
        exp = Exp[level] + EXP[digit][1];
        pow = Pow[level] + 1;

        if( exp > max || max < pow ) { // Try next since upper limit is invalidly low
          DIGITS[level]++;
          continue;
        }

        if( pow > exp ) {
          min  = pow % EXP[level][10];
          pow -= min;
          if( min > Exp[level] ) {
            pow += EXP[level][10];
          }
          min  = pow + Exp[level];
        } else {
          min  = exp;
        }

        // Check limits existence
        if( max < min ) {
          DIGITS[level]++;  // Try next number since current limits invalid
        } else {
          level++;  // Go for further level checking since limits available
        }
      }
      
      // All checking is done, escape from the main check loop
      if( level < 1 ) {
        break;
      }

      // Final check last bit of the most possible candidates
      // Update known low bit values
      Exp[level] = Exp[level - 1] + EXP[level][DIGITS[level]];
      Pow[level] = Pow[level - 1] + POW[digit + 1 - level][DIGITS[level]];

      // Loop to check all last bit of candidates
      while( DIGITS[level] < 10 ) {
        /* Comment out to show all single digit disariums
        if( Exp[level] > Pow[level] ) { break; } */

        // Print out new disarium number
        if( Exp[level] == Pow[level]) {
          for( int i = DMAX; i > 0; i-- ) {
            printf( "%d", DIGITS[i] );
          }
          printf( "\n" );
        }

        // Go to followed last bit candidate
        DIGITS[level]++;
        Exp[level] += EXP[level][1];
        Pow[level]++;
      }

      // Reset to try next path
      DIGITS[level] = 0;
      level--;
      DIGITS[level]++;
    }
  }

  printf( "All disarium numbers have found\n" );
}
