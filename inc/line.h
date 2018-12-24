#ifndef LINE_H
#define LINE_H

#include "point.h"

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
    void SetPointStart(Point start);
    void SetPointEnd(Point start);

    Point GetPointStart(void);
    Point GetPointEnd(void);

private:
    sLine line_;

};

#endif // LINE_H
