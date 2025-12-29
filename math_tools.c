#define EPS 1e-15 // The error used for approximation
#define PI 3.141592653589793238462643383279502884
#define TWO_PI 6.283185307179586

long double sin(long double arg) {
	arg -= TWO_PI * (long long)(arg / TWO_PI);
	// Move the arg value in [0, PI/2] for faster convergence
	int change = 1; // Change the final result sign if we move by PI
	if (arg < 0) {
		arg += 2*PI;
	}
	if (arg > 3 * PI / 2) {
		// quadran 4
		change = -change;
		arg = TWO_PI - arg;
	} else if (arg > PI) {
		// quadran 3
		change = -change;
		arg -= PI;
		if (arg > PI / 2) {
			arg = PI - arg;
		}
	} else if (arg > PI / 2) {
		// quadran 2
		arg = PI - arg;
	}
	// Use Taylor Series
	// sin(x) = Σ[(-1)^n * x^(2n + 1) / (2n + 1)!], with n from 0 to infinity
	long double term = arg;
	long double result = arg;
	for (int i = 1; term <= -EPS || term >= EPS; i += 2) {
		// each term is obtained from the previous one
		term *= -1.0 * (arg * arg) / ((i + 1) * (i + 2));
		result += term;
	}
	return result * change;
}

long double sqrt(long double n) {
	/* 
		Use Newton-Raphson method
		xk = xk-1 - f(xk-1) / f'(xk-1), with k from 0 to infinity
		The function: f(x) = x^2 - n
		from x = sqrt(n), simplified x^2 = n => x^2 - n = 0
	*/
	long double current_x = n / 2.0; // Start with the prediction set to n / 2.0
	while (1) {
		// Simplify the ecuation
		long double new_x = 0.5 * (current_x + n / current_x);
		if (new_x - current_x > -EPS && new_x - current_x < EPS) {
			/*
			The loop stops by returning the new x when the absolute value
			of the difference between new x and current x is less than epsilon
			*/
			return new_x;
		}
		current_x = new_x; // Continue the process for new value approximation
	}
}
