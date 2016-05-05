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

#include <dirent.h> //reading folder
#include <stdio.h>
#include <stdlib.h>

#include <sys/stat.h> //mkdir
#include <sstream>


using namespace cv;
using namespace std;

void smooth_filter( Mat &image_src, Mat &img_padded, int type ){

    int T = 255;

    //Aplying filter
    // 2x2 1-3 , 3x3
    if( type == 1 ){
        for( int i = 0; i < (img_padded.rows - 1); i+=2 ){
            for( int j = 0; j < (img_padded.cols - 1); j+=2 ){
                // cout << (int)img_padded.at<uchar>(i,j) << " ";
                if( img_padded.at<uchar>(i,j) == T && 
                    img_padded.at<uchar>(i+1,j+1) == T ){
                    
                    img_padded.at<uchar>(i,j+1) = 0;
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
    }
    else if( type == 2 ) {
        for( int i = 0; i < (img_padded.rows - 1); i+=2 ){
            for( int j = 0; j < (img_padded.cols - 1); j+=2 ){
                // cout << (int)img_padded.at<uchar>(i,j) << " ";
                if( img_padded.at<uchar>(i,j) == T && 
                    img_padded.at<uchar>(i+1,j) == T 
                    && img_padded.at<uchar>(i+1,j+1) == T ){
                    
                    img_padded.at<uchar>(i,j+1) = 0;
                }
                else{
                    img_padded.at<uchar>(i,j) = 0 ;
                    img_padded.at<uchar>(i,j+1) = 0;
                    img_padded.at<uchar>(i+1,j+1) = 0;  
                    img_padded.at<uchar>(i+1,j) = 0;
                }

            } 
        }
    }

    else if( type == 3 ) {
        for( int i = 0; i < (img_padded.rows - 1); i+=2 ){
            for( int j = 0; j < (img_padded.cols - 1); j+=2 ){
                // cout << (int)img_padded.at<uchar>(i,j) << " ";
                if( img_padded.at<uchar>(i,j) == T && 
                    img_padded.at<uchar>(i+1,j) == T 
                    && img_padded.at<uchar>(i,j+1) == T
                    && img_padded.at<uchar>(i+1,j+1) == T ){
                }
                else{
                    img_padded.at<uchar>(i,j) = 0 ;
                    img_padded.at<uchar>(i,j+1) = 0;
                    img_padded.at<uchar>(i+1,j+1) = 0;  
                    img_padded.at<uchar>(i+1,j) = 0;
                }

            } 
        }
    }

    else if( type == 4 ) {
        for( int i = 0; i < (img_padded.rows - 2); i+=3 ){
            for( int j = 0; j < (img_padded.cols - 2); j+=3 ){
                // cout << (int)img_padded.at<uchar>(i,j) << " ";
                if( img_padded.at<uchar>(i,j) == T 
                    && img_padded.at<uchar>(i+1,j) == T 
                    && img_padded.at<uchar>(i+2,j) == T 
                    && img_padded.at<uchar>(i,j+1) == T
                    && img_padded.at<uchar>(i,j+2) == T ){

                    img_padded.at<uchar>(i+1,j+1) = 0;
                    img_padded.at<uchar>(i+1,j+2) = 0;
                    img_padded.at<uchar>(i+2,j+1) = 0;
                    img_padded.at<uchar>(i+2,j+2) = 0;
                }
                else{
                    img_padded.at<uchar>(i,j) = 0 ;
                    img_padded.at<uchar>(i,j+1) = 0;
                    img_padded.at<uchar>(i,j+2) = 0;
                    img_padded.at<uchar>(i+1,j) = 0;  
                    img_padded.at<uchar>(i+1,j+1) = 0;
                    img_padded.at<uchar>(i+1,j+2) = 0;
                    img_padded.at<uchar>(i+2,j) = 0;  
                    img_padded.at<uchar>(i+2,j+1) = 0;
                    img_padded.at<uchar>(i+2,j+2) = 0;
                }

            } 
        }
    }

    else if( type == 5 ) {
        for( int i = 0; i < (img_padded.rows - 2); i+=3 ){
            for( int j = 0; j < (img_padded.cols - 2); j+=3 ){
                // cout << (int)img_padded.at<uchar>(i,j) << " ";
                if( img_padded.at<uchar>(i,j) == T 
                    && img_padded.at<uchar>(i,j+1) == T
                    && img_padded.at<uchar>(i,j+2) == T 
                    && img_padded.at<uchar>(i+1,j) == T 
                    && img_padded.at<uchar>(i+2,j) == T 
                    && img_padded.at<uchar>(i+1,j+1) == T 
                    ){

                    img_padded.at<uchar>(i+1,j+2) = 0;
                    img_padded.at<uchar>(i+2,j+1) = 0;
                    img_padded.at<uchar>(i+2,j+2) = 0;
                }
                else{
                    img_padded.at<uchar>(i,j) = 0 ;
                    img_padded.at<uchar>(i,j+1) = 0;
                    img_padded.at<uchar>(i,j+2) = 0;
                    img_padded.at<uchar>(i+1,j) = 0;  
                    img_padded.at<uchar>(i+1,j+1) = 0;
                    img_padded.at<uchar>(i+1,j+2) = 0;
                    img_padded.at<uchar>(i+2,j) = 0;  
                    img_padded.at<uchar>(i+2,j+1) = 0;
                    img_padded.at<uchar>(i+2,j+2) = 0;
                }

            } 
        }
    }

    else if( type == 6 ) {
        for( int i = 0; i < (img_padded.rows - 2); i+=3 ){
            for( int j = 0; j < (img_padded.cols - 2); j+=3 ){
                // cout << (int)img_padded.at<uchar>(i,j) << " ";
                if( img_padded.at<uchar>(i,j) == T 
                    && img_padded.at<uchar>(i,j+2) == T
                    && img_padded.at<uchar>(i+1,j+1) == T 
                    && img_padded.at<uchar>(i+2,j) == T 
                    && img_padded.at<uchar>(i+2,j+2) == T 
                    ){

                    img_padded.at<uchar>(i,j+1) = 0;
                    img_padded.at<uchar>(i+1,j) = 0;
                    img_padded.at<uchar>(i+1,j+2) = 0;
                    img_padded.at<uchar>(i+2,j+1) = 0;
                }
                else{
                    img_padded.at<uchar>(i,j) = 0 ;
                    img_padded.at<uchar>(i,j+1) = 0;
                    img_padded.at<uchar>(i,j+2) = 0;
                    img_padded.at<uchar>(i+1,j) = 0;  
                    img_padded.at<uchar>(i+1,j+1) = 0;
                    img_padded.at<uchar>(i+1,j+2) = 0;
                    img_padded.at<uchar>(i+2,j) = 0;  
                    img_padded.at<uchar>(i+2,j+1) = 0;
                    img_padded.at<uchar>(i+2,j+2) = 0;
                }

            } 
        }
    }

    else if( type == 7 ) {

        Mat tmp1 = img_padded;
        Mat tmp2 = img_padded;

        for( int i = 0; i < (img_padded.rows - 2); i+=3 ){
            for( int j = 0; j < (img_padded.cols - 2); j+=3 ){
                // cout << (int)img_padded.at<uchar>(i,j) << " ";
                if( img_padded.at<uchar>(i,j) == T 
                    && img_padded.at<uchar>(i,j+1) == T
                    && img_padded.at<uchar>(i,j+2) == T
                    ){

                    tmp1.at<uchar>(i+1,j) = 0;
                    tmp1.at<uchar>(i+1,j+1) = 0;
                    tmp1.at<uchar>(i+1,j+2) = 0;

                    tmp1.at<uchar>(i+2,j) = 0;
                    tmp1.at<uchar>(i+2,j+1) = 0;
                    tmp1.at<uchar>(i+2,j+2) = 0;

                }
                else{
                    tmp1.at<uchar>(i,j) = 0 ;
                    tmp1.at<uchar>(i,j+1) = 0;
                    tmp1.at<uchar>(i,j+2) = 0;
                    tmp1.at<uchar>(i+1,j) = 0;  
                    tmp1.at<uchar>(i+1,j+1) = 0;
                    tmp1.at<uchar>(i+1,j+2) = 0;
                    tmp1.at<uchar>(i+2,j) = 0;  
                    tmp1.at<uchar>(i+2,j+1) = 0;
                    tmp1.at<uchar>(i+2,j+2) = 0;
                }

            } 
        }

        for( int i = 0; i < (img_padded.rows - 2); i+=3 ){
            for( int j = 0; j < (img_padded.cols - 2); j+=3 ){
                // cout << (int)img_padded.at<uchar>(i,j) << " ";
                if( img_padded.at<uchar>(i,j) == T 
                    && img_padded.at<uchar>(i+1,j) == T
                    && img_padded.at<uchar>(i+2,j) == T
                    ){
                    
                    tmp2.at<uchar>(i,j+1) = 0;
                    tmp2.at<uchar>(i,j+2) = 0;
                    
                    tmp2.at<uchar>(i+1,j+1) = 0;
                    tmp2.at<uchar>(i+1,j+2) = 0;

                    tmp2.at<uchar>(i+2,j+1) = 0;
                    tmp2.at<uchar>(i+2,j+2) = 0;

                }
                else{
                    tmp2.at<uchar>(i,j) = 0 ;
                    tmp2.at<uchar>(i,j+1) = 0;
                    tmp2.at<uchar>(i,j+2) = 0;
                    tmp2.at<uchar>(i+1,j) = 0;  
                    tmp2.at<uchar>(i+1,j+1) = 0;
                    tmp2.at<uchar>(i+1,j+2) = 0;
                    tmp2.at<uchar>(i+2,j) = 0;  
                    tmp2.at<uchar>(i+2,j+1) = 0;
                    tmp2.at<uchar>(i+2,j+2) = 0;
                }

            } 
        }

        for( int i = 0; i < (img_padded.rows ); i+=1 ){
            for( int j = 0; j < (img_padded.cols); j+=1 ){
                img_padded.at<uchar>(i,j) = (tmp1.at<uchar>(i,j) + tmp2.at<uchar>(i,j) >= 255)? 255:0;
            }
        }
    }



    for( int i = 0 ; i < image_src.rows ; ++i ){
        for( int j = 0 ; j < image_src.cols ; ++j ){
            if( img_padded.at<uchar>(i,j) != 255 ){
                image_src.at<Vec3b>(i,j) = Vec3b( 0,0,0 );
            }
        }
    }

}

bool isFind( string s, string pat){
    size_t found = 0;
    found = s.find(pat);

    //cout << found << endl;

    return ( found < 0 || found > s.size() ) ? 0 : 1;
}


void reading_folder( vector<string>& v_names){

    string postfix = ".jpg";

    DIR *dpdf;
    struct dirent *epdf;

    dpdf = opendir("./");

    // vector<Mat> v_image;
    vector<string> v_name;

    int cont = 0;
    
    if (dpdf != NULL){
       while (epdf = readdir(dpdf)){
          string name = epdf->d_name;
          if( isFind(name, postfix)){
            //printf("Filename: %s %s",epdf->d_name, "\n");
          
            // Mat reader = imread( name, 1);
            
            v_name.push_back( name );
            // v_image.push_back( reader );

            cont ++ ;
          }       
       }
    }
    v_names = v_name;
    cout << "Images read: " << cont << endl;
}

void processing( vector<string>& v_names, int type ){

    //Creating folders
    string s_type = static_cast<ostringstream*>( &(ostringstream() << type) )->str();
    string path = "./";
    string folder = path + s_type ;
    cout << folder << endl;
    mkdir(folder.c_str(), S_IRWXU | S_IRWXG | S_IROTH | S_IXOTH);

    //Processing images    
    vector<Mat> v_images( v_names.size() );

    Mat img_padded;
    Mat img_bw;

    for( int i = 0 ; i < v_names.size() ; ++i ){
        
        v_images[i] = imread( v_names[i] , 1 );
        img_padded = imread( v_names[i], 0 );

        int counter = 0;
        for( int x = 0 ; x < img_padded.rows ; ++x){
            for( int y = 0 ; y < img_padded.cols ; ++y){
                counter += img_padded.at<uchar>(x,y);
            }
        }

        img_bw = img_padded > ( counter / (img_padded.rows*img_padded.cols) );

        smooth_filter( v_images[i], img_bw, type );
        
        // imwrite( v_names[i] + "bw.jpg" , img_bw);

        imwrite( path + "/" + "1/"  + s_type + "_" + v_names[i] + "mod.jpg" , v_images[i]);
    }

}

template <typename T>
void print( vector<T>& v_T ){
    
    for( int i = 0 ; i < v_T.size() ; ++i ){
        cout << v_T[i] << "\t";
    } cout << endl;
}

int main(int argc, char** argv ){

    int type = atoi( argv[1] );

    vector<string> v_names;

    reading_folder( v_names );

    // print( v_names );

	processing( v_names, type );

	cvWaitKey(0);

	return 0;
}