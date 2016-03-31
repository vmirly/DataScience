#include "opencv2/imgproc/imgproc.hpp"
#include "opencv2/highgui/highgui.hpp"
#include <stdlib.h>
#include <stdio.h>

using namespace cv;

/// Global Variables
Mat src, dst;
int top, bottom, left, right;
int borderType;
Scalar value;
char* window_name = "copyMakeBorder Demo";
RNG rng(12345);

/** @function main  */
int main( int argc, char** argv )
{

  int c;

  /// Load an image
  src = imread( argv[1] );

  if( !src.data )
  { return -1;
    printf(" No data entered, please enter the path to an image file \n");
  }

  /// Brief how-to for this program
  printf( "\n \t copyMakeBorder Demo: \n" );
  printf( "\t -------------------- \n" );
  printf( " ** Press 'c' to set the border to a random constant value \n");
  printf( " ** Press 'r' to set the border to be replicated \n");
  printf( " ** Press 'ESC' to exit the program \n");

  /// Create window
  namedWindow( window_name, CV_WINDOW_AUTOSIZE );

  float hthick = atof(argv[2]);
  float vthick = atof(argv[3]);

  /// Initialize arguments for the filter
  top = (int) (vthick*src.rows); bottom = (int) (vthick*src.rows);
  left = (int) (hthick*src.cols); right = (int) (hthick*src.cols);
  dst = src;

  imshow( window_name, dst );

  while( true )
    {
      c = waitKey(500);

      if( (char)c == 27 )
        { break; }
      else if( (char)c == 'c' )
        { borderType = BORDER_CONSTANT; }
      else if( (char)c == 'r' )
        { borderType = BORDER_REPLICATE; }

      value = Scalar( rng.uniform(0, 255), rng.uniform(0, 255), rng.uniform(0, 255) );
      copyMakeBorder( src, dst, top, bottom, left, right, borderType, value );

      imshow( window_name, dst );
    }

  return 0;
}
