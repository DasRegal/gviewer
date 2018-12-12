#ifndef POINT_H
#define POINT_H

class Point
{
public:
    struct sPoint {
        float x;
        float y;
        float z;
    };

    Point(float x = 0.0, float y = 0.0, float z = 0.0);
    void SetX(float x = 0.0);
    void SetY(float y = 0.0);
    void SetZ(float z = 0.0);

    float GetX(void);
    float GetY(void);
    float GetZ(void);

private:
    sPoint point_;
};

#endif // POINT_H
