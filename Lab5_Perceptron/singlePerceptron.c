#include <stdio.h>
#include <stdlib.h>

#define sgn(x) ((x > 0) ? 1 : -1)

int main(void)
{
    unsigned long long dimensions;
    printf("Please enter the number of dimensions of the vector\n");
    scanf(" %llu", &dimensions);
    long double *weightVector = malloc(dimensions * sizeof(long double));
    for (unsigned long long int i = 0; i < dimensions; ++i)
    {
        printf("Please enter %lluth entry of initial weight vector\n", i);
        scanf(" %Lf", &weightVector[i]);
    }
    printf("Initial weight vector -");
    for (unsigned long long int i = 0; i < dimensions; ++i)
    {
        printf(" %Lf", weightVector[i]);
    }
    putchar('\n');
    long double learningRate;
    printf("Please enter learning rate\n");
    scanf(" %Lf", &learningRate);
    unsigned long long numInputs;
    printf("Please enter number of inputs\n");
    scanf(" %llu", &numInputs);
    long double **inputs = malloc(numInputs * sizeof(long double *));
    for (unsigned long long i = 0; i < numInputs; ++i)
    {
        inputs[i] = malloc(dimensions * sizeof(long double));
    }
    for (unsigned long long i = 0; i < numInputs; ++i)
    {
        for (unsigned long long j = 0; j < dimensions; ++j)
        {
            printf("Please enter %llu input vector %llu entry\n", i, j);
            scanf(" %Lf", &inputs[i][j]);
        }
    }
    int *desiredOutput = malloc(numInputs * sizeof(int));
    for (unsigned long long i = 0; i < numInputs; ++i)
    {
        printf("Please enter desired output for vector %llu\n", i);
        scanf(" %d", &desiredOutput[i]);
    }
    long double net;
    long double error;
    int output;
    unsigned long long iterations = 0;
    do
    {
        error = 0;
        for (unsigned long long i = 0; i < numInputs; ++i)
        {
            net = 0;
            for (unsigned long long j = 0; j < dimensions; ++j)
            {
                net += inputs[i][j] * weightVector[j];
            }
            output = sgn(net);
            if (output != desiredOutput[i])
            {
                for (unsigned long long j = 0; j < dimensions; ++j)
                {
                    weightVector[j] = weightVector[j] + learningRate * (desiredOutput[i] - output) * inputs[i][j];
                }
            }
            error += desiredOutput[i] - output;
        }
        printf("Iteration - %llu Error - %.9Lf\nWeight Vector -", iterations, error);
        for (unsigned long long j = 0; j < dimensions; ++j)
        {
            printf(" %Lf", weightVector[j]);
        }
        putchar('\n');
        ++iterations;
    } while (error != 0);
    printf("\nFinal weight vector -");
    for (unsigned long long i = 0; i < dimensions; ++i)
    {
        printf(" %Lf", weightVector[i]);
    }
}