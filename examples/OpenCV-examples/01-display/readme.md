#

   imread (filename, mode)

 mode specifies
 
    CV_LOAD_IMAGE_UNCHANGED (<0) loads the image as is (including the alpha channel if present)
    CV_LOAD_IMAGE_GRAYSCALE ( 0) loads the image as an intensity one
    CV_LOAD_IMAGE_COLOR (>0) loads the image in the RGB format



---------------------

    Mat image;   create a Mat object that will store the data of the loaded image.

---------------------
 
   namedWindow( "Display window", WINDOW_AUTOSIZE );// Create a window for display.


   imshow( "Display window", image );      // Show our image inside it.


   waitKey(0);      // Wait for a keystroke in the window

--------------------


