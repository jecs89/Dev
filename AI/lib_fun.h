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

template<typename T> void print( string title, vector<T> & Q_t);


void assign_values(string line1, vector<double>& values){
	//cout << line1.substr(0,line1.find(" ")) << endl;

	int val = -1;

	if ( ! (istringstream(line1.substr(0,line1.find(" "))) >> val) ) val = -1;
	values.push_back(val);

	//cout << "0 " << values[0] << endl;
	int i = 1;

	line1 = line1.substr(line1.find(" ")+1,line1.length()-1) ;

	//cout << line1 << endl;

	//cout << "///\n";
	while( line1.length() > 0 ){

		//cout << "L1 "<<line1 << endl;

	    string tmp = line1.substr(0,line1.find(" "));
	    //cout << "tmp " <<  tmp << endl;

	    if ( ! (istringstream(tmp) >> val) ) {val = -1;}
	    values.push_back(val);

	    //cout << "v " << values[i] << endl;

	    line1 = line1.substr(line1.find(" ")+1,line1.length()-1) ;

	    //cout<< "L " << line1.length() << endl;

	    //cout << "L2 "<< line1 << endl;

	    i++;


	}
}

void reading_params( string name, vector<double>& params, vector<vector<double>>& patterns ){
    //Reading params
    ifstream file ( name.c_str() );    // File to read image

    string line1, line2;
    double x;

    getline( file, line1 );
    cout << "nxd\n";
    assign_values(line1,params);

    
  	
  	cout << "pat\n";

  	int i = 0;
    while( !file.eof() ){
    	vector<double> vector_values;

        getline( file, line1 );
        //cout << "reading\n" << line1 << endl;
        //if ( ! (istringstream(line1) >> x) ) x = 0;
        
        //cout << "ass\n";
        assign_values(line1, vector_values);

        //print("v\n",vector_values);
        
        patterns.push_back(vector_values);
        i++;
    }


    cout << "RP\n";
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
void print( string title, vector<T> & Q_t){
	cout << title << endl ;
	//if(type == 0){
		int spc = 15;
		for( int i = 0 ; i < Q_t.size(); ++i){
			cout << setw(spc) << i << setw(spc) << Q_t[i] << endl;
		}
	//}
	/*else if(type == 1){
		int spc = 8;
		for( int i = 0 ; i < Q_t.size(); ++i){
			cout << setw(spc) << Q_t[i] ;
		}
		cout << endl;
	}*/
	
}

template<typename T>
void print( string title, vector<T> & Q_t, int spc, ofstream & os ){
    os << title << endl ;
    // int spc = 10;
    for( int i = 0 ; i < Q_t.size(); ++i){
        // cout << setw(spc) << i << setw(spc) << Q_t[i] << endl;
        os << setw(spc) << Q_t[i] ;
    }    
    os << endl;
    
}

template<typename T>
void create_matrix( vector<vector<T>>& xij, int rows, int cols ){
	vector< vector<double> > Xij ( rows, vector<double>(cols) );
	xij = Xij;
}

template<typename T>
void init( vector<T> & xij, T value ){
    for( int i = 0 ; i < xij.size(); ++i){
    	xij[i] = value;
    }    
}

template<typename T>
void init( vector<vector<T>>& xij, T value ){
	cout << xij.size() << "\t" << xij[0].size() << endl;
    for( int i = 0 ; i < xij.size(); ++i){
    	for( int j = 0 ; j < xij[0].size() ; ++j){
    		xij[i][j] = value;
    	}
    }    
}

// void testing_functions(){

// 	vector<double> params;
// 	reading_params(params);

// 	//testing print vector
// 	print("params:\n",params,1);

// 	//testing print file
// 	ofstream out_lib_fun("out_lib_fun.txt",ofstream::app);
// 	print("params:\n",params,8,out_lib_fun);

// 	//testing creation of matrix
// 	vector<vector<double>> Xij;
// 	create_matrix(Xij,2,3);

// 	//testing matrix print 
// 	print( "params:\n", Xij );

// 	//testing initialization
// 	init(Xij,3.0);

// 	//testing matrix print 
// 	print( "params:\n", Xij );

// }