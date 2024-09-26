#ifndef __SOLVE__H
#define __SOLVE__H

#include "pde.h"
#include <vector>
#include <tuple>
#include <functional>
#include <Eigen/Dense> 

typedef Eigen::MatrixXd Solution;

// Solver abstract scheme for AdvDiffReactEquation
class PDESolver{
protected:
       const AdvDiffReactEquation* eqt;
       Solution* sol;
       // Protected constructor
       PDESolver(const AdvDiffReactEquation* eqt) : eqt(eqt) { /*std::cout << "PDESolver constructor called\n";*/ }
public:
       template<typename Method>
       static std::unique_ptr<PDESolver> create(const AdvDiffReactEquation* eqt){
              return std::unique_ptr<PDESolver>(new Method(eqt));
       }

       virtual Solution solve() const = 0;
};

class FiniteDifferenceMethod : public PDESolver{
protected:
       FiniteDifferenceMethod(const AdvDiffReactEquation* eqt) : PDESolver(eqt) { /*std::cout << "FiniteDifferenceMethod constructor called\n";*/ }
       friend class PDESolver;

       float x_start, x_end; // Spatial domain
       float t_end; // Time domain

       unsigned long N; // Number of spatial points
       unsigned long K; // Number of time points

       float dx; // Space step
       float dt; // Time step

       void set_space_step(){ dx = (x_end-x_start)/static_cast<float>(N-1); }
       void set_time_step(){ dt = t_end/static_cast<float>(K-1); }
public:
       // Getters
       inline float get_x_start(){ return x_start; }
       inline float get_x_end(){ return x_end; }
       inline std::tuple<float, float> get_x_domain(){ return std::make_tuple(x_start, x_end); }
       inline float get_t_end(){ return t_end; }
       inline unsigned long get_N(){ return N; }
       inline unsigned long get_K(){ return K; }

       // Setters
       inline void set_x_start(float x){ x_start = x; }
       inline void set_x_end(float x){ x_end = x; }
       inline void set_x_domain(float x1, float x2){ x_start = x1; x_end = x2; }
       inline void set_t_end(float t){ t_end = t; }
       inline void set_N(unsigned long n){ N = n; }
       inline void set_K(unsigned long k){ K = k; }

       // Initial and boundary conditions
       void set_initial_condition(std::function<float> f); // function pointer ?????

       Solution solve() const = 0;
};

class ForwardEulerMethod : public FiniteDifferenceMethod{
private:
       ForwardEulerMethod(const AdvDiffReactEquation* eqt) : FiniteDifferenceMethod(eqt) {}
       friend class PDESolver;
public:
       Solution solve() const override;
};

class FiniteElementMethod : public PDESolver{
private:
       FiniteElementMethod(const AdvDiffReactEquation* eqt) : PDESolver(eqt) { /*std::cout << "FiniteElementMethod constructor called\n";*/ }
       friend class PDESolver;
public:
       Solution solve() const override { std::cout << "fde called\n"; }
};

#endif