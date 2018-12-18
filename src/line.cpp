#include "inc/line.h"

Line::Line()
    : line_(sLine{Point(), Point(), true})
{

}

void Line::SetPointStart(Point start)
{
    line_.start = start;
}

void Line::SetPointEnd(Point end)
{
    line_.end = end;
}

Point Line::GetPointStart(void)
{
    return line_.start;
}

Point Line::GetPointEnd(void)
{
    return line_.end;
}
