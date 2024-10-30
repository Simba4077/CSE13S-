#include "mathlib.h"

#include "math.h"

#include <stdio.h>
#define EPSILON 1e-14
double Abs(double x) {
    if (x < 0) {
        x = x * (-1);
    }
    return x;
}

double Sqrt(double x) {
    if (x < 0) {
        return nan("nan");
    }

    double old = 0.0;
    double new = 1.0;

    while (Abs(old - new) > EPSILON) {
        old = new;
        new = 0.5 * (old + (x / old));
    }

    return new;
}

double Sin(double x) {
    //to normalize the input
    x = fmod(x, 2 * M_PI);
    if (x > 2 * M_PI) {
        x = 2 * M_PI - x;
    }

    if (x < 0) {
        x = 2 * M_PI + x;
    }
    double sum = 0.0;
    double x_to_the_k = x;
    double k_fact = 1.0;

    double k = 1.0;

    double neg = 1.0;

    while (1) {
        double term = (x_to_the_k * neg) / k_fact;
        if (Abs(term) < EPSILON) {
            break;
        }
        sum += term;
        x_to_the_k = x_to_the_k * x * x;

        k_fact = k_fact * (k + 1) * (k + 2);

        k += 2.0;
        neg = neg * (-1);
    }
    return sum;
}

double Cos(double x) {
    //normalize the input
    if (x > 2 * M_PI) {
        x = 2 * M_PI - (x - 2 * M_PI);
    }

    if (x < 0) {
        x = 2 * M_PI + x;
    }

    double sum = 0.0;
    double x_to_the_k = 1.0;
    double k_fact = 1.0;
    double k = 0.0;
    double neg = 1.0;

    while (1) {
        double term = (x_to_the_k * neg) / k_fact;
        if (Abs(term) < EPSILON) {
            break;
        }
        sum += term;
        x_to_the_k = x_to_the_k * x * x;
        k_fact *= (k + 1) * (k + 2);
        k += 2.0;
        neg = neg * (-1);
    }

    return sum;
}

double Tan(double x) {

    double tan = Sin(x) / Cos(x);

    return tan;
}
