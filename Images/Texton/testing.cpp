#include <iostream>
#include "opencv2/core/core.hpp"
#include "opencv2/highgui/highgui.hpp"
#include "opencv2/imgproc/imgproc.hpp"
#include <fstream>
#include <iomanip>
#include <algorithm>
#include <math.h>
#include <vector>
#include <thread>

using namespace cv;
using namespace std;

void smooth_filter( Mat &image_src, Mat &img_padded ){

    // int image_width = image_src.cols;
    // int image_height = image_src.rows;

    //resizing image
    // resize( img_padded, img_padded, Size(), (double)(image_width + 2) /image_width , (double)(image_height + 2)/image_height , INTER_LINEAR );

    // int counter = 0;
    // for( int i = 0 ; i < img_padded.rows ; ++i ){
    // 	for (int j = 0; j < img_padded.cols ; ++j){
    // 		counter+= (int)img_padded.at<uchar>(i,j);
    // 	}
    // }

    // double T = counter/(img_padded.rows*img_padded.cols);
    int T = 0;

    //Aplying filter
    for( int i = 0; i < (img_padded.rows - 1); i+=2 ){
        for( int j = 0; j < (img_padded.cols - 1); j+=2 ){
  
            if( img_padded.at<uchar>(i,j) > T && 
                img_padded.at<uchar>(i+1,j) > T 
                && img_padded.at<uchar>(i+1,j+1) > T ){
            	
            	img_padded.at<uchar>(i,j) = 255;
            	img_padded.at<uchar>(i,j+1) = 255;
            	img_padded.at<uchar>(i+1,j+1) = 255;

            	img_padded.at<uchar>(i+1,j) = 0;
            }
            else{
            	img_padded.at<uchar>(i,j) = 0 ;
            	img_padded.at<uchar>(i,j+1) = 0;
            	img_padded.at<uchar>(i+1,j+1) = 0;	
            	img_padded.at<uchar>(i+1,j) = 0;
            }

        } 
    }


    for( int i = 0 ; i < image_src.rows ; ++i ){
        for( int j = 0 ; j < image_src.rows ; ++j ){
            if( img_padded.at<uchar>(i,j) == 0 ){
                image_src.at<Vec3b>(i,j) = Vec3b( 0,0,0 );
            }
        }
    }



}

int main(int argc, char** argv ){

	Mat image_src = imread( argv[1] , 1 ); // 0, grayscale  >0, color
	Mat img_padded = imread( argv[1] , 0 ); // 0, grayscale  >0, color

    Mat img_bw = img_padded > 128;

	string name (argv[1]);

	smooth_filter( image_src, img_bw );

	imwrite( name + "bw.jpg" , img_bw);

	// imshow("HOLA", img_bw);

    imwrite( name + "mod.jpg" , image_src);

	cvWaitKey(0);

	return 0;
}