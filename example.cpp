#include <iostream>
#include <math.h>
//#include <stdlib>
#include <fstream>
//#include<gsl/gsl_sf_erf. h>

using namespace std;

const int NT=10000; // number of time steps
const int NX=201; // nb of space intervals
const int L=200; // val max of x
const int K = 100; // strike
double sigmap=0.2, r=0.1;
double *u = new double [NX] ;
double phi_T(double s){ if(s>K) return s-K; else return 0;}

ofstream file("fd.csv");
       

void save(double vec[NX]){       
       for (int i=0;i<NX;i++){
              file << vec[i] << ",";
       }
       file << endl;
}

void PDEfiniteDiff(){
       double dx= (double) L/(double) (NX-1);
       double dt = 1./NT;
       double t = 0;
       
       // final condition
       for(int i=0;i<NX;i++){
              u[i] = phi_T(i*dx);
       }
       
       for(int j=0;j<NT;j++){
              t += dt;
              
              for(int i=1;i<NX-1;i++){
                     double x=i*dx;
                     u[i] += (0.5*sigmap*x*sigmap*x*(u[i+1]-2*u[i]+u[i-1])/dx/dx
                     +r*x*(u[i+1] -u[i] )/dx-r*u[i] ) * dt;
              }

              u[NX-1]=L-K*exp(-r*t) ;
              u[0]=0 ;

              save(u);
       }
}

int main(){
       PDEfiniteDiff();
       return 0;
}