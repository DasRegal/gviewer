#ifndef GLOB_STATE_H
#define GLOB_STATE_H

#include <inc/point.h>

class GlobState
{
public:
    GlobState();

private:
    Point glob_point_;
    Point local_point_;
};

#endif // GLOB_STATE_H
