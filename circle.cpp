#include "opencv2/highgui/highgui.hpp"
#include "opencv2/imgproc/imgproc.hpp"
#include <iostream>
#include <stdio.h>

using namespace cv;

Mat src; Mat src_gray;
int thresh = 100;
int max_thresh = 255;
RNG rng(12345);

void thresh_callback(int, void* );

int main( int argc, char** argv )
{
  src = imread( argv[1], 1 );

  cvtColor( src, src_gray, CV_BGR2GRAY );
  blur( src_gray, src_gray, Size(3,3) );

  char* source_window = "Source";
  namedWindow( source_window, CV_WINDOW_AUTOSIZE );
  imshow( source_window, src );

  createTrackbar( " Canny thresh:", "Source", &thresh, max_thresh, thresh_callback );
  thresh_callback( 0, 0 );

  waitKey(0);
  return(0);
}
void thresh_callback(int, void* )
{
  Mat threshold_output;
  vector<vector<Point> > contours;
  vector<Vec4i> hierarchy;

  threshold( src_gray, threshold_output, thresh, 255, THRESH_BINARY );
  findContours( threshold_output, contours, hierarchy, CV_RETR_TREE, CV_CHAIN_APPROX_SIMPLE, Point(0, 0) );
  vector<vector<Point> > contours_poly( contours.size() );
  vector<Rect> boundRect( contours.size() );
  vector<RotatedRect> minRect( contours.size() );
    Mat drawing = Mat::zeros( threshold_output.size(), CV_8UC3 );
  for( int i = 0; i < contours.size(); i++ )
     { approxPolyDP( Mat(contours[i]), contours_poly[i], 3, true );
       boundRect[i] = boundingRect( Mat(contours_poly[i]) );
        minRect[i] = minAreaRect( Mat(contours[i]) );
        double l = boundRect[i].height;
        double b  = boundRect[i].width;
        if ( l/b <1.1 && l/b >0.9)
        {
           if (minRect[i].size.width/ minRect[i].size.height<1.1 && minRect[i].size.width/ minRect[i].size.height>0.9)
           {
            drawContours( drawing, contours_poly, i, Scalar(0,255,0), 1, 8, vector<Vec4i>(), 0, Point() );
           }
        }
      }
   
  namedWindow( "Contours", CV_WINDOW_AUTOSIZE );
  imshow( "Contours", drawing );
}