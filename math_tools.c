#define EPS 1e-15 // The error used for approximation
#define PI 3.141592653589793238462643383279502884
#define TWO_PI 6.283185307179586

long double sin(long double arg) {
	arg -= TWO_PI * (long long)(arg / TWO_PI);
	// Move the arg value in [0, PI/2] for faster convergence
	int change = 1; // Change the final result sign if we move by PI
	if (arg < 0) {
		arg += TWO_PI;
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

long double cos(long double arg) {
	arg -= TWO_PI * (long long)(arg / TWO_PI);
	// Move the arg value in [0, PI/2] for faster convergence
	if (arg < 0) {
		arg += TWO_PI;
	}
	int change = 1;
	if (arg > 3 * PI / 2) {
		// quadran 4
		arg = TWO_PI - arg;
	} else if (arg > PI) {
		// quadran 3
		change = -change;
		arg -= PI;
		if (arg > PI / 2) {
			arg = PI - arg;
		}
	} else if (arg > PI / 2) {
		change = -change;
		arg = PI - arg;
	}
	// Use Taylor Series
	// cos(x) = Σ[(-1)^n * x^(2n) / (2n)!], with n from 0 to infinity
	long double term = 1;
	long double result = 1;
	for (int i = 1; term <= -EPS || term >= EPS; i += 2) {
		term *= -1.0 * (arg * arg) / (i * (i + 1));
		result += term;
	}
	return result * change;
}

long double tan(long double arg) {
	return sin(arg) / cos(arg);
}

long double cot(long double arg) {
	return cos(arg) / sin(arg);
}

long double arcsin(long double arg) {
	/* 
		Use Newton-Raphson method
		xk = xk-1 - f(xk-1) / f'(xk-1), with k from 0 to infinity
		The function: f(x) = sin(x) - arg
		The derivative: f'(x) = cos(x)
		from x = arcsin(arg), simplified sin(x) = arg => sin(x) - arg = 0
	*/
	if (arg < -1 || arg > 1) {
		return __INT_MAX__;
	}
	long double current_x = arg; // start with a x prediction
	while (1) {
		// Simplify the ecuation to get the new x
		long double new_x = current_x - tan(current_x) + (arg / cos(current_x));
		if (new_x - current_x >= -EPS && new_x - current_x <= EPS) {
			/*
				return the new x if the difference between the new x and the
				current x is in [-EPS, EPS]
			*/
			return new_x;
		}
		current_x = new_x; // Continue the process for new value approximation
	}
}

long double arccos(long double arg) {
	return PI/2 - arcsin(arg);
}

long double arctan(long double arg) {
	/* 
		Use Newton-Raphson method
		xk = xk-1 - f(xk-1) / f'(xk-1), with k from 0 to infinity
		The function: f(x) = x^2 - n
		The derivative: f'(x) = 2*x
		from x = arctan(n), simplified tan(x) = n => tan(x) - n = 0
	*/
	long double current_x = arg; // Start with the prediction set to arg
	while (1) {
		// Simplify the ecuation to get the new x
		long double new_x = current_x - (cos(current_x) * cos(current_x)) *
							(tan(current_x) - arg);
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

long double arccot(long double arg) {
	return PI/2 - arctan(arg);
}

long double sqrt(long double n) {
	/* 
		Use Newton-Raphson method
		xk = xk-1 - f(xk-1) / f'(xk-1), with k from 0 to infinity
		The function: f(x) = x^2 - n
		The derivative: f'(x) = 2*x
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
