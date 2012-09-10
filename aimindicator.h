#ifndef __AIM_INDICATOR__
#define __AIM_INDICATOR__

#include "point.h"
#include "resourcemgr.h"

class AimIndicator
{
  private:
    double red;
    double green;
    double blue;
    ResourceMgr* resourceMgr;

  public:
    AimIndicator();
    AimIndicator( double r, double g, double b );
    ~AimIndicator();
    void setColor( double r, double g, double b );
    void draw( Point center, double radius, double angle );

};
#endif
