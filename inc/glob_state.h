#ifndef GLOB_STATE_H
#define GLOB_STATE_H

#include <inc/point.h>
#include <inc/line.h>
#include <vector>

class GlobState
{
public:
    typedef enum
    {
        ABS = 0,
        REL
    } systemType_t;

    typedef struct
    {
        unsigned int countPoint;
        bool         isCompleteLine;
        Line::sLine  line;

    }  formatLine_t;

    GlobState();
    void  SetGlobX(float x, systemType_t sysType = ABS);
    void  SetGlobY(float y, systemType_t sysType = ABS);
    void  SetGlobZ(float z, systemType_t sysType = ABS);
    float GetGlobX(void);
    float GetGlobY(void);
    float GetGlobZ(void);

    void SetSystemType(systemType_t sysType);
    systemType_t GetSystemType(void);
    void SetFormatLine(formatLine_t fLine);
    void GetFormatLine(formatLine_t *fLine);
    void SetLine(Line line);
    Line GetLine(void);
    void AddLineToList(formatLine_t fLine);
    bool IsListEmpty(void);

    void  SetLocalX(float x);
    void  SetLocalY(float y);
    void  SetLocalZ(float z);
    float GetLocalX(void);
    float GetLocalY(void);
    float GetLocalZ(void);

private:
    systemType_t sysType_;
    Point        glob_point_;
    Point        local_point_;
    formatLine_t formatLine_;
    Line         line_;
    std::vector<Line::sLine> lineArray_;
};

#endif // GLOB_STATE_H
