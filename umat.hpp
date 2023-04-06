#ifndef UMAT_HPP
#define UMAT_HPP

#include <iostream>

#include <SMAAspUserSubroutines.h>

extern "C" void FOR_NAME(umat, UMAT)(
    double *stress, double *statev, double *ddsdde, double *sse, double *spd,
    double *scd, double *rpl, double *ddsddt, double *drplde, double *drpldt,
    double *stran, double *dstran, double *time, double *dtime, double *temp,
    double *dtemp, double *predef, double *dpred, char *cmname, int *ndi,
    int *nshr, int *ntens, int *nstatv, double *props, int *nprops,
    double *coords, double *drot, double *pnewdt, double *celent, double *dfgrd0,
    double *dfgrd1, int *noel, int *npt, int *layer, int *kspt,
    int *kstep, int *kinc, short cmname_len)
{
    std::cout << "\n-- umat --\n"
              << "props: [" << props[0] << ", " << props[1] << "]\n"
              << "name: " << cmname << "\n";

    double E = props[0];
    double NU = props[1];
    double G = E / 2.0 / (1.0 + NU);

    // Update strain
    double eps[3];
    for (int i = 0; i < 3; i++)
        eps[i] = stran[i] + dstran[i];

    // Calculation of the stress
    double c1 = E / (1 - NU * NU);
    double c2 = c1 * NU;
    stress[0] = c1 * eps[0] + c2 * eps[1];
    stress[1] = c2 * eps[0] + c1 * eps[1];
    stress[2] = G * eps[2];

    //	Isotropic elastic stiffness matrix ddsdde as a 9x1-Vector
    for (int i = 0; i < 3; i++)
    {
        for (int j = 0; j < 3; j++)
        {
            ddsdde[3 * i + j] = 0.0;
        }
    }
    ddsdde[0] = c1;
    ddsdde[1] = c2;
    ddsdde[3] = c2;
    ddsdde[4] = c1;
    ddsdde[8] = G;
}

#endif // UMAT_HPP
