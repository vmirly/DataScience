#include <stdio.h>
#include <opencv2/opencv.hpp>
#include <cstdlib>

using namespace cv;

int main(int argc, char** argv )
{
    if ( argc < 2 )
    {
        printf("usage: DisplayImage.out <Image_Path> <mode -1:unchanged 0: gray-scale 1:RGB>\n");
        return -1;
    }

    Mat image;
    image = imread( argv[1], atoi(argv[2]));

    if ( !image.data )
    {
        printf("No image data \n");
        return -1;
    }
    namedWindow("Display Image", WINDOW_AUTOSIZE );
    imshow("Display Image", image);

    waitKey(0);

    return 0;
}

