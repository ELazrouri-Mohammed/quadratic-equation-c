#include <stdio.h>
#include <math.h>
#include <complex.h>
double complex X1, X2;
double discriminan(int a, int b, int c)
{
    double D = b * b - 4 * (a * c);
    return D;
}
void posi(int a, int b, int c)
{
    X1 = (-b + sqrt(discriminan(a, b, c))) / (2.0 * a);
    X2 = (-b - sqrt(discriminan(a, b, c))) / (2.0 * a);
    printf("X1 = %.2f \n", creal(X1));
    printf("X2 = %.2f \n", creal(X2));
}
void zero(int a, int b, int c)
{
    X1 = -b / (2.0 * a);
    printf("X = %.2f\n", creal(X1));
}
void nega(int a, int b, int c)
{
    double complex D = discriminan(a, b, c);

    X1 = (-b + (csqrt(D))) / (2.0 * a);
    X2 = (-b - (csqrt(D))) / (2.0 * a);
    printf("X1 = %.2f + %.2fi\n", creal(X1), cimag(X1));
    printf("X2 = %.2f + %.2fi\n", creal(X2), cimag(X2));
}

int main()
{
    int a, b, c;
    printf("Enter the valeur of a : \n");
    scanf("%d", &a);
    printf("Enter the valeu of b : \n");
    scanf("%d", &b);
    printf("Enter la valeur de c : \n");
    scanf("%d", &c);
    double D = discriminan(a, b, c);
    if (a == 0 && b == 0 && c == 0)
    {
        printf("X ∈ ℝ, all real numbers are solutions.\n");
    }
    else if (a == 0 && b == 0 && c != 0)
    {
        printf("The equation has no real solution (ℝ).\n");
    }

    else if (a == 0 && c == 0)
    {
        printf("X = 0 ");
    }

    else if (a == 0 && b != 0)
    {
        X1 = -((float)c) / b;
        printf("X = %.2f ", creal(X1));
    }
    else
    {
        if (D > 0)
        {
            posi(a, b, c);
        }
        else if (D == 0)
        {
            zero(a, b, c);
        }
        else
        {
            nega(a, b, c);
        }
    }
}
