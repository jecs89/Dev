#include <iostream>
#include <vector>
#include <string>
#include <fstream>
#include <math.h>
#include <random>
#include "iomanip"
#include <sstream>
//#include <algorithm>
//#include <thread>

// #include "opencv2/core/core.hpp"
// #include "opencv2/highgui/highgui.hpp"
// #include "opencv2/imgproc/imgproc.hpp"
// #include "opencv2/photo/photo.hpp"

using namespace std;

void reading_params( vector<double>& params){
    //Reading params
    ifstream file ( "params.p" );    // File to read image

    string line1, line2;
    double x;

    getline( file, line1 );
    //cout << line1 << endl;
    while( !file.eof() ){
        getline( file, line1 );
        if ( ! (istringstream(line1) >> x) ) x = 0;
        //cout << x << "\t";
        params.push_back(x);
    }
}

template<typename T>
void print( string title, vector< vector<T> >& Q_t ){
	cout << title << endl ;
	int spc = 15;
	for( int i = 0 ; i < Q_t.size(); ++i){
		for( int j = 0 ; j < Q_t[0].size(); ++j){
			cout << setw(spc) << Q_t[i][j] ;
		}
		cout << endl;
	}
}
template<typename T>
void print( string title, vector<T> & Q_t, int type = 0){
	cout << title << endl ;
	if(type == 0){
		int spc = 15;
		for( int i = 0 ; i < Q_t.size(); ++i){
			cout << setw(spc) << i << setw(spc) << Q_t[i] << endl;
		}
	}
	else if(type == 1){
		int spc = 8;
		for( int i = 0 ; i < Q_t.size(); ++i){
			cout << setw(spc) << Q_t[i] ;
		}
		cout << endl;
	}
	
}


int main(int argc, char const *argv[])
{

	vector<double> params;
	reading_params(params);
	print("params:\n",params,1);

	return 0;
}