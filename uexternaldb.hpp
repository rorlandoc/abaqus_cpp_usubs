#ifndef UEXTERNALDB_HPP
#define UEXTERNALDB_HPP

#include <iostream>
#include <string>

#include <SMAAspUserSubroutines.h>

std::string get_stage(int stage_flag);

extern "C" void FOR_NAME(uexternaldb, UEXTERNALDB)(
    const int &lop, const int &lrestart,
    const double (&time)[2], const double &dtime,
    const int &kstep, const int &kinc)
{
    std::cout << "\n-- uexternaldb --\n"
              << "lop     : " << lop << " [" << get_stage(lop) << "]\n"
              << "lrestart: " << lrestart << "\n"
              << "time    : [" << time[0] << ", " << time[1] << "]\n"
              << "dtime   : " << dtime << "\n"
              << "kstep   : " << kstep << "\n"
              << "kinc    : " << kinc << std::endl;
}

std::string get_stage(int stage_flag)
{
    switch (stage_flag)
    {
    case 0:
        return "analysis start";
    case 1:
        return "increment start";
    case 2:
        return "increment end";
    case 3:
        return "analysis end";
    case 4:
        return "restart analysis start";
    case 5:
        return "step start";
    case 6:
        return "step end";
    default:
        return "unknown";
    }
}

#endif // UEXTERNALDB_HPP
