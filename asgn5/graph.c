#include <math.h>
#include <stdio.h>
#define EPSILON 1e-14
double Abs(double x);

/*
 * Compute the square root of x >= 0.
 */
double Sqrt(double x);

/*
 * Compute the sine of x.
 */
double Sin(double x);

/*
 * Compute the cosine of x.
 */
double Cos(double x);

/*
 * Compute the tangent of x.
 *
 * NOTE:
 * Tan(M_PI / 2) will not be undefined for two reasons:
 * (1) the IEEE 754 double precision standard cannot perfectly represent
 *     pi in binary; and
 * (2) the Taylor-Maclaurin series used to approximate Cos(pi/2) will not
 *     converge to 0.
 *  Therefore, it will instead to converge to a very, very small
 *  number resulting in a very, very large value of Tan(pi/2).
 */
double Tan(double x);

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

// Your trig function implementations
int main(void) {
    FILE *fp = fopen("results.csv", "w"); // Create a CSV file for graphing
    if (fp == NULL) {
        perror("Error opening file");
        return 1;
    }

    fprintf(fp, "x,my_sin,math_sin,diff_sin,my_cos,math_cos,diff_cos,my_tan,math_tan,diff_tan\n");

    for (double x = -10.0; x <= 10.0; x += 1.0) {
        double my_sin_val = Sin(x);
        double math_sin_val = sin(x);
        double diff_sin = fabs(my_sin_val - math_sin_val);

        double my_cos_val = Cos(x);
        double math_cos_val = cos(x);
        double diff_cos = fabs(my_cos_val - math_cos_val);

        double my_tan_val = Tan(x);
        double math_tan_val = tan(x);
        double diff_tan = fabs(my_tan_val - math_tan_val);

        fprintf(fp, "%.2f,%.40f,%.40f,%.40f,%.40f,%.40f,%.40f,%.40f,%.40f,%.40f\n", x, my_sin_val,
            math_sin_val, diff_sin, my_cos_val, math_cos_val, diff_cos, my_tan_val, math_tan_val,
            diff_tan);
    }

    fclose(fp);
    return 0;
}
