#include "inc/glob_state.h"

GlobState::GlobState()
    : sysType_(ABS)
    , glob_point_(0.0, 0.0, 0.0)
    , local_point_(0.0, 0.0, 0.0)

{
}

void GlobState::SetSystemType(systemType_t sysType)
{
    sysType_ = sysType;
}

GlobState::systemType_t GlobState::GetSystemType(void)
{
    return sysType_;
}

void  GlobState::SetGlobX(float x, systemType_t sysType)
{
    if (sysType == ABS)
        glob_point_.SetX(x);
    else
        glob_point_.SetX(glob_point_.GetX() + x);
}

void  GlobState::SetGlobY(float y, systemType_t sysType)
{
    if (sysType == ABS)
        glob_point_.SetY(y);
    else
        glob_point_.SetY(glob_point_.GetY() + y);
}

void  GlobState::SetGlobZ(float z, systemType_t sysType)
{
    if (sysType == ABS)
        glob_point_.SetZ(z);
    else
        glob_point_.SetZ(glob_point_.GetZ() + z);
}

float GlobState::GetGlobX(void)
{
    return glob_point_.GetX();
}

float GlobState::GetGlobY(void)
{
    return glob_point_.GetY();
}

float GlobState::GetGlobZ(void)
{
    return glob_point_.GetZ();
}

void  GlobState::SetLocalX(float x)
{
    local_point_.SetX(x);
}

void  GlobState::SetLocalY(float y)
{
    local_point_.SetY(y);
}

void  GlobState::SetLocalZ(float z)

{
    local_point_.SetZ(z);
}

float GlobState::GetLocalX(void)
{
    return local_point_.GetX();
}

float GlobState::GetLocalY(void)
{
    return local_point_.GetY();
}

float GlobState::GetLocalZ(void)
{
    return local_point_.GetZ();
}
