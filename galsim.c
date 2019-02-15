/**   simulation program  **/

#include <stdio.h>
#include <stdlib.h>
#include <math.h>


int read_doubles_from_file(int n, double* p, const char* fileName);  // function prototype

int main(int argc, const char** argv) {

double x[2]={0};
double y[2]={0};

double vx[2]={0};
double vy[2]={0};

double r01[2] = {0}; 
double R01[2] = {0};
double Norm_ro1 = 0;

double r011[2]= {0};
double R011[2] = {0};

  if(argc != 6) {
    printf("Please give give arguments: input_file_name \n");
    return -1;
          } 
int N = atoi(argv[1]);
const char* in_file = argv[2];
int nsteps = atoi(argv[3]);
int delta_t = atoi(argv[4]);
int graphics = atoi(argv[5]);

printf("%d\n",N);
printf("input_file_name = %s\n", in_file);
printf("%d\n",nsteps);
printf("%d\n",delta_t);
printf("%d\n", graphics);

printf("\n");

/* Open input file and determine its size. */
  double buf1[6*N];
  if(read_doubles_from_file(6*N, buf1, in_file) != 0){
    printf("Error reading file '%s'\n", in_file);
    return -1;}

    for(int i = 0; i < N; i++){
      printf("x%d: %0.10f\n",i,buf1[i*6+0]);
      x[i] = buf1[i*6+0];
      printf("y%d: %0.10f\n",i,buf1[i*6+1]);
      y[i] = buf1[i*6+1];
      printf("mass%d: %0.10f\n",i,buf1[i*6+2]);
      printf("vx%d: %0.10f\n",i,buf1[i*6+3]);
      vx[i] = buf1[i*6+3];
      printf("vy%d; %0.10f\n",i,buf1[i*6+4]);
      vy[i] = buf1[i*6+4];
      printf("brightness%d: %0.10f\n",i,buf1[i*6+5]);
      printf("\n");

      r01[i] =  (x[i] - x[i+1])  +  (y[i] - y[i+11]) ;
      R01[i] = sqrt(  ( (x[i] - x[i+1])*(x[i] - x[i+1]) )  + ( (y[i] - y[i+1])*(y[i] - y[i+1]) ) ) ;

      printf("r011: %f\n", r01[i]);
      printf("R011: %f\n", R01[i]);

}

printf("%f\n", x[0]);
printf("%f\n", y[0]);


double E0 = 10^-3;
double G = (double)100/N;


r011[0] =  (x[0] - x[1])  +  (y[0] - y[1]) ;
R011[0] = sqrt(  ( (x[0] - x[1])*(x[0] - x[1]) )  + ( (y[0] - y[1])*(y[0] - y[1]) ) ) ;

//Norm_ro1 = r01/R01;

printf("r011: %f\n", r011[0]);
printf("R011: %f\n", R011[0]);

//printf("Norm_ro1: %f\n", Norm_ro1);



 //fclose(buf1);
  return 0;
}
  





/*  function diffination */

int read_doubles_from_file(int n, double* p, const char* fileName) {
  /* Open input file and determine its size. */
  FILE* input_file = fopen(fileName, "rb");
  if(!input_file) {
    printf("read_doubles_from_file error: failed to open input file '%s'.\n", fileName);
    return -1;
  
  }

  /* Get filesize using fseek() and ftell(). */
  fseek(input_file, 0L, SEEK_END);
  size_t fileSize = ftell(input_file);
  /* Now use fseek() again to set file position back to beginning of the file. */
  fseek(input_file, 0L, SEEK_SET);
  if(fileSize != n * sizeof(double)) {
    printf("read_doubles_from_file error: size of input file '%s' does not match the given n.\n", fileName);
    printf("For n = %d the file size is expected to be (n * sizeof(double)) = %lu but the actual file size is %lu.\n",
   n, n * sizeof(double), fileSize);
    return -1;
  }
  /* Read contents of input_file into buffer. */
  size_t noOfItemsRead = fread(p, sizeof(char), fileSize, input_file);
  if(noOfItemsRead != fileSize) {
    printf("read_doubles_from_file error: failed to read file contents into buffer.\n");
    return -1;
  }
  /* OK, now we have the file contents in the buffer.
     Since we are finished with the input file, we can close it now. */
  if(fclose(input_file) != 0) {
    printf("read_doubles_from_file error: error closing input file.\n");
    return -1;
  }
  /* Return 0 to indicate success. */

  return 0;
}