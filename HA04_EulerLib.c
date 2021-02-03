#include <stdio.h>
#include <stdlib.h>
#include <math.h>
#include "HA04_EulerLib.h"

#define NUMOFSTATES 2

void RHS_MSD(double *rhs, double *y)
{ // mass spring damper

    double m = 1.0; // mass of object
    double c = 2;   // feder constant
    double d = 3;   // damper constant

    double x = y[0]; // position
    double v = y[1]; // speed

    /*calc derivatives and store in rhs*/
    rhs[0] = v;
    rhs[1] = -((d / m) * v + (c / m) * x);
}

void eulerSettings_MSD(simHandle *handle)
{

    /*num of states*/
    handle->numOfStates = (int)NUMOFSTATES;

    /*right hand site*/
    handle->f = &RHS_MSD;

    /*reserve storage for init state vec*/
    handle->stateVecInit = (double *)malloc(sizeof(double) * (handle->numOfStates));
    if (handle->stateVecInit == NULL)
    {
        printf("stateVecInit konnte nicht angelegt werden\n");
        return;
    }

    /*get user defined Simtime*/
    printf("Simtime (in s): \n");
    scanf("%lf", &handle->simTime);

    /*get user defined StepSize*/
    printf("StepSize (in s): \n");
    scanf("%lf", &handle->stepSize);

    /*get init state position*/
    printf("position(t = 0): \n");
    scanf("%lf", &handle->stateVecInit[0]);

    /*get init state speed*/
    printf("speed(t = 0): \n");
    scanf("%lf", &handle->stateVecInit[1]);

    /*reserve storage for states and derivatives*/
    int length = (int)ceil(handle->simTime / handle->stepSize);
    handle->stateVec = (double *)malloc(sizeof(double) * ((handle->numOfStates) * length + 2));
    handle->derivStateVec = (double *)malloc(sizeof(double) * ((handle->numOfStates) * length + 2));

    if (handle->stateVec == NULL || handle->derivStateVec == NULL)
    {
        printf("Der Speicher für stateVec oder deriveStateVec konnte nicht reserviert werden\n");
        return;
    }

    /*init states and derivatives with zero*/
    for (int i = 0; i < ((handle->numOfStates) * length + 2); i++)
    {
        handle->stateVec[i] = 0;
        handle->derivStateVec[i] = 0;
    }
}

void eulerForward(simHandle *handle)
{ // this is called only once
    int numOfStates = handle->numOfStates;
    int integratorSteps = (int)ceil(handle->simTime / handle->stepSize);

    /*write init states*/
    for (int i = 0; i < numOfStates; i++)
    {
        handle->stateVec[i] = handle->stateVecInit[i];
    }
    for (int i = 0; i < integratorSteps; i++)
    {
        /*get derivatives*/
        handle->f(&handle->derivStateVec[i * numOfStates], &handle->stateVec[i * numOfStates]);

        for (int j = 0; j < numOfStates; j++)
        {
            /*euler step*/
            handle->stateVec[numOfStates * (i + 1) + j] = handle->stateVec[i * numOfStates + j] + handle->stepSize * handle->derivStateVec[i * numOfStates + j];
        }
    }
}

void showResults_MSD(simHandle *handle)
{

    /*print data to text file*/
    FILE *fp = fopen("simData.txt", "w");
    if (fp == NULL)
    {
        printf("Datei konnte nicht geöffnet werden!\n");
        return;
    }
    else
    {
        for (int i = 0; i < (int)ceil((handle->simTime) / (handle->stepSize)); i++)
        {
            fprintf(fp, "%lf %lf %lf\n", i * (handle->stepSize), (handle->stateVec[(handle->numOfStates) * i]), (handle->stateVec[(handle->numOfStates) * i + 1]));
        }
    }
    fclose(fp);

    /*call gnuplot*/
    FILE *gnuplotPipe = popen("gnuplot -p", "w");
    if (gnuplotPipe == NULL)
    {
        printf("Gnuplot konnte nicht geöffnet werden\n");
        return;
    }

    fprintf(gnuplotPipe, "set xlabel \"'time in s\"\n");
    fprintf(gnuplotPipe, "set title \"results of simulation\"\n  ");
    fprintf(gnuplotPipe, "plot 'simData.txt' using 1:2 title 'position', 'simData.txt' using 1:3 title 'speed'\n");
    pclose(gnuplotPipe);
}
