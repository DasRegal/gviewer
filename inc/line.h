#ifndef LINE_H
#define LINE_H

#include "inc/point.h"

class Line
{
public:
    struct sLine
    {
        Point start;
        Point end;
        bool isVisible;
    };

    Line();

private:
    sLine line_;

};

#endif // LINE_H
