#include <stdio.h>
#include <math.h>
#include <malloc.h>

/* funtion declaration */
unsigned long *getPointsFrom_y(unsigned long *y_to_squared_mod_p, unsigned long *p);

const unsigned long ZERO = 0u, ONE = 1u;

int main(int argc, char const *argv[])
{
    unsigned long a = 3u, b = 8u, p = 13u;
    unsigned long **points_over_fP_p = NULL;

    if (argc >= 4)
    {
        printf("The arguments supplied are: \na=%s\nb=%s\np=%s\n", argv[1], argv[2], argv[3]);
        a = strtoul(argv[1], NULL, 0);
        b = strtoul(argv[2], NULL, 0);
        p = strtoul(argv[3], NULL, 0);

        if (argc > 4)
            printf("Ignoring everything else\n");
    }
    else if (argc < 3)
    {
        printf("Too few arguments supplied.\n");
    }

    printf("Calculating finite field over p=%lu (b = %lu) (a = %lu)\n(allocating mem...)\n", p, b, a);
    points_over_fP_p = (unsigned long **)malloc(sizeof(unsigned long) * p);
    if (points_over_fP_p == NULL)
    {
        printf("\n\nError allocating memory for the result...\n\n");
        return -1;
    }
    printf("Iterating over the ring FP_p in Z where p=%lu\n\n", p);

    for (unsigned long x = ZERO; x < p; x++)
    {
        unsigned long y_to_squared_mod_p = ZERO, y_x = ZERO;
        printf("\n\n Calculating y^2=x^3+ax+b ... for x=%lu \r\n Calculating y^2=(%lu^3)+(%lu*%lu)+%lu", x, x, a, x, b);
        y_x = (x * x * x) + (a * x) + b;
        printf("\ny^2=%lu", y_x);
        y_to_squared_mod_p = y_x % p;

        points_over_fP_p = (unsigned long **)realloc(points_over_fP_p, sizeof(unsigned long) * p * (x + 1));
        if (points_over_fP_p == NULL)
        {
            printf("\n\nError reallocating memory for the result...\n\n");
            return -1;
        }
        points_over_fP_p[x] = getPointsFrom_y(&y_to_squared_mod_p, &p);
    }
    /* print result */
    printf("\n\nPrinting resulting elliptic curve points over a finite field of p=%lu:\n", p);
    printf("Point (x,y)=0 (because dra. nareli says so :v\n");
    for (unsigned long x = ZERO; x < p; x++)
    {
        if (points_over_fP_p[x] != NULL)
        {
            for (int i = 0; i < p; i++)
            {
                if (points_over_fP_p[x][i] != -1)
                    printf("Point (x,y)=(%lu,%lu)\n", x, points_over_fP_p[x][i]);
                else
                    break;
            }
        }
        free(points_over_fP_p[x]);
    }
    free(points_over_fP_p);
    return 0;
}

unsigned long *getPointsFrom_y(unsigned long *y_to_squared_mod_p, unsigned long *p)
{
    printf("\r\n Calculating square root for %lu in the integer ring of finite field %lu \n", *y_to_squared_mod_p, *p);
    int counter_valid_y_square_values = 0;
    unsigned long *y_square_values = NULL;
    for (unsigned long y_square = ONE; y_square < (*p); y_square++)
    {
        unsigned long y_squared = y_square * y_square % (*p);
        bool isValidSquare = y_squared == (*y_to_squared_mod_p);

        printf("  Asserting y=%lu...", y_square);
        if (isValidSquare)
        {
            counter_valid_y_square_values++;
            // allocate memory for the y values and leave uninitialized
            if (counter_valid_y_square_values <= 1)
            {
                y_square_values = (unsigned long *)malloc(sizeof(unsigned long) * counter_valid_y_square_values);
                if (y_square_values == NULL)
                {
                    printf("Error - unable to allocate required memory\n");
                    return NULL;
                }
                else
                    y_square_values[counter_valid_y_square_values - 1] = y_square;
            }
            else
            {
                y_square_values = (unsigned long *)realloc(y_square_values, counter_valid_y_square_values * sizeof(unsigned long));
                if (y_square_values == NULL)
                {
                    printf("Error - unable to re-allocate required memory\n");
                    return NULL;
                }
                else
                    y_square_values[counter_valid_y_square_values - 1] = y_square;
            }
            printf("  VALID (index=%d)-> Square root for %lu^2=%lu mod %lu", counter_valid_y_square_values, y_square, *y_to_squared_mod_p, *p);
            /* the last element is NULL, 1 element before is valid*/
            y_square_values = (unsigned long *)realloc(y_square_values, (counter_valid_y_square_values + 1) * sizeof(unsigned long));
            if (y_square_values == NULL)
            {
                printf("Error - unable to re-allocate required memory\n");
                return NULL;
            }
            y_square_values[counter_valid_y_square_values] = -1;
        }
        else
            printf("  INVALID.");
        printf("\n");
    }
    return y_square_values;
}
