#include <stdio.h>
#include <ctime>
#include <cilk/cilk.h>
#include <cilk/reducer_opadd.h>
#include <chrono>
#include <time.h>

using namespace std::chrono;

/**
  * @brief Function for calculate value mathematik function
  * @param x -point where calculating function value
  */
double func(double x) {
	return 8 / (1 + x*x);
}

int main()
{
	srand((unsigned)time(0));
	// Limits of integration
	double a = 0.0;
	double b = 1.0;

	// Initializing variable for integral sum
	// double I = 0.0;
	cilk::reducer_opadd <double> I(0.0);

	// Initializing variable for number of intervals
	int N = 1e+9;

	// Calculating step size
	double step = abs(a - b) / N;

	// Initializing start time
	high_resolution_clock::time_point t1 = high_resolution_clock::now();
	
	// Calculation of the integral method of rectangles
	cilk_for (int i = 0; i < N; i++) {
		I += func(i * step) * step;
	}
	
	high_resolution_clock::time_point t2 = high_resolution_clock::now();
	duration<double> duration = (t2 - t1);

	printf("Number of intervals: %d\n", N);
	printf("Calculation time: %f\n", duration);

	// print result
	double PI = 3.14159265358979;
	printf("Computed value of integral : %.8f\n", I.get_value());
	printf("Real value of the integral : %.8f\n", PI * 2);

	return 0;
}