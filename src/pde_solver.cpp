#include "../headers/solve.h"

Solution FiniteDifferenceMethod::solve() const{
       // Initialize the solution matrix
       Solution sol = new Solution(N,K);
       // Set the initial condition
       for (int i=0;i<N;i++){
              (*sol)(i,0) = eqt->initial_condition(x_start + i*dx);
       }
       // Set the boundary conditions
       for (int k=0;k<K;k++){
              (*sol)(0,k) = eqt->left_boundary_condition(t_end - k*dt);
              (*sol)(N-1,k) = eqt->right_boundary_condition(t_end - k*dt);
       }
       // Set the interior points
       for (int k=0;k<K-1;k++){
              for (int i=1;i<N-1;i++){
                     (*sol)(i,k+1) = eqt->interior_point((*sol)(i-1,k), (*sol)(i,k), (*sol)(i+1,k), dx, dt);
              }
       }
       return *sol;
}