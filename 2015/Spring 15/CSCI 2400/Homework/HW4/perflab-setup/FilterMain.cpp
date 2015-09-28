#include <stdio.h>
#include "cs1300bmp.h"
#include <iostream>
#include <fstream>
#include "Filter.h"

using namespace std;

#include "rtdsc.h"

//
// Forward declare the functions
//
Filter * readFilter(string filename);
double applyFilter(Filter *filter, cs1300bmp *input, cs1300bmp *output);

int
main(int argc, char **argv)
{

  if ( argc < 2) {
    fprintf(stderr,"Usage: %s filter inputfile1 inputfile2 .... \n", argv[0]);
  }

  //
  // Convert to C++ strings to simplify manipulation
  //
  string filtername = argv[1];

  //
  // remove any ".filter" in the filtername
  //
  string filterOutputName = filtername;
  string::size_type loc = filterOutputName.find(".filter");
  if (loc != string::npos) {
    //
    // Remove the ".filter" name, which should occur on all the provided filters
    //
    filterOutputName = filtername.substr(0, loc);
  }

  Filter *filter = readFilter(filtername);

  double sum = 0.0;
  int samples = 0;

  for (int inNum = 2; inNum < argc; inNum++) {
    string inputFilename = argv[inNum];
    string outputFilename = "filtered-" + filterOutputName + "-" + inputFilename;
    struct cs1300bmp *input = new struct cs1300bmp;
    struct cs1300bmp *output = new struct cs1300bmp;
    int ok = cs1300bmp_readfile( (char *) inputFilename.c_str(), input);

    if ( ok ) {
      double sample = applyFilter(filter, input, output);
      sum += sample;
      samples++;
      cs1300bmp_writefile((char *) outputFilename.c_str(), output);
    }
    delete input;
    delete output;
  }
  fprintf(stdout, "Average cycles per sample is %f\n", sum / samples);

}

struct Filter *
readFilter(string filename)
{
  ifstream input(filename.c_str());

  if ( ! input.bad() ) {
    int size = 0;
    input >> size;
    Filter *filter = new Filter(size);
    int div;
    input >> div;
    filter -> setDivisor(div);
    for (int i=0; i < size; i++) {
      for (int j=0; j < size; j++) {
	int value;
	input >> value;
	filter -> set(i,j,value);
      }
    }
    return filter;
  }
}


double
applyFilter(struct Filter *filter, cs1300bmp *input, cs1300bmp *output)
{

  long long cycStart, cycStop;

  cycStart = rdtscll();
  output -> width = input -> width;
  output -> height = input -> height;

  int div = filter -> getDivisor();
  int w = (input -> width) - 1;
  int h = (input -> width) - 1;
  int get_Size = filter -> getSize();

  int t1 = 0;
  int t2 = 0;
  int t3 = 0;
  int t4 = 0;
  int t5 = 0;
  int t6 = 0;

  int filt[get_Size][get_Size];

  for(int a = 0; a < get_Size; ++a){

    for(int b = 0; b < get_Size; ++b){

      filt[b][a] = filter -> get(a, b);
    }
  }

  if (filt[0][0] == 1 && filt[0][1] == 1 && filt[0][2] == 1 && filt[1][0] == 1 && filt[1][1] == 1 && filt[1][2] == 1 && filt[2][0] == 1 && filt[2][1] == 1 && filt[2][2] == 1) {
    
    for(int plane = 0; plane < 3; plane++) {
    
      for(int row = h - 1; row > 0 ; row -= 2) {
    
        for(int col = w - 1; col > 0; col -= 3) {
          
          t1 = 0;
          t2 = 0;
          t3 = 0;
          t4 = 0;
          t5 = 0;
          t6 = 0;

      
          for (int j = 0; j < get_Size; j++) {

            int col1 = col + j - 1;
            int col2 = col + j;
            int col3 = (col + 1) + j;

              for (int i = 0; i < get_Size; i++) {

                int row1 = row + i - 1;
                int row2 = row + i;

                t1 += (input -> color[plane][row1][col1]);
                t2 += (input -> color[plane][row1][col2]);
                t3 += (input -> color[plane][row2][col1]);
                t4 += (input -> color[plane][row2][col2]);
                t5 += (input -> color[plane][row1][col3]);
                t6 += (input -> color[plane][row2][col3]);
              }
          }

        if(div != 1){

          t1 = t1 / div;
          t2 = t2 / div;
          t3 = t3 / div;
          t4 = t4 / div;
          t5 = t5 / div;
          t6 = t6 / div;
          
        }

        if (t1 < 0){
          t1 = 0;
        }

        if (t1 > 255){
          t1 = 255;
        }

        if (t2 < 0){
          t2 = 0;
        }

        if (t2 > 255){ 
          t2 = 255;
        }

        if (t3 < 0){
          t3 = 0;
        }

        if (t3 > 255){ 
          t3 = 255;
        }

        if (t4 < 0){
          t4 = 0;
        }

        if (t4 > 255){ 
          t4 = 255;
        }

        if (t5 < 0){
          t5 = 0;
        }

        if (t5 > 255){ 
          t5 = 255;
        }

        if (t6 < 0){
          t6 = 0;
        }

        if (t6 > 255){ 
          t6 = 255;
        }

      output -> color[plane][row][col] = t1;
      output -> color[plane][row][col + 1] = t2;
      output -> color[plane][row + 1][col] = t3;
      output -> color[plane][row + 1][col + 1] = t4;
      output -> color[plane][row][col + 2] = t5;
      output -> color[plane][row + 1][col + 2] = t6;

        }
      }
    }
  }

  else{
  
  for(int plane = 0; plane < 3; plane++) {

    for(int row = h - 1; row > 0 ; row -= 2) {
  
      for(int col = w - 1; col > 0; col -= 3) {
        
        t1 = 0;
        t2 = 0;
        t3 = 0;
        t4 = 0;
        t5 = 0;
        t6 = 0;

        for (int j = 0; j < get_Size; j++) {
          
          int col1 = col + j - 1;
          int col2 = col + j;
          int col3 = (col + 1) + j;
          
          for (int i = 0; i < get_Size; i++) {
            
            int getFilter = filt[i][j];
            
            if(getFilter == 0){}
              else{
      
              int row1 = row + i - 1;
              int row2 = row +i ;
      
              t1 += (input -> color[plane][row1][col1] * getFilter );
              t2 += (input -> color[plane][row1][col2] * getFilter );      
              t3 += (input -> color[plane][row2][col1] * getFilter );
              t4 += (input -> color[plane][row2][col2] * getFilter );
              t5 += (input -> color[plane][row1][col3] * getFilter );
              t6 += (input -> color[plane][row2][col3] * getFilter );

            }
          }
        }
    
        if(div != 1){

          t1 = t1 / div;
          t2 = t2 / div;
          t3 = t3 / div;
          t4 = t4 / div;
          t5 = t5 / div;
          t6 = t6 / div;  

        }

        if (t1 < 0){
          t1 = 0;
        }

        if (t1 > 255){ 
          t1 = 255;
        }

        if (t2 < 0){
          t2 = 0;
        }

        if (t2 > 255){ 
          t2 = 255;
        }

        if (t3 < 0){
          t3 = 0;
        }

        if (t3 > 255){ 
          t3 = 255;
        }

        if (t4 < 0){
          t4 = 0;
        }

        if (t4 > 255){ 
          t4 = 255;
        }

        if (t5 < 0){
          t5 = 0;
        }

        if (t5 > 255){ 
          t5 = 255;
        }

        if (t6 < 0){
          t6 = 0;
        }

        if (t6 > 255){ 
          t6 = 255;
        }

      output -> color[plane][row][col] = t1;
      output -> color[plane][row][col + 1] = t2;
      
      output -> color[plane][row + 1][col] = t3;
      output -> color[plane][row + 1][col + 1] = t4;

      output -> color[plane][row][col + 2] = t5;
      output -> color[plane][row + 1][col + 2] = t6;
      
        }
      }   
    }
  }
 
  cycStop = rdtscll();
  double diff = cycStop - cycStart;
  double diffPerPixel = diff / (output -> width * output -> height);
  fprintf(stderr, "Took %f cycles to process, or %f cycles per pixel\n",
	  diff, diff / (output -> width * output -> height));
  return diffPerPixel;
}
