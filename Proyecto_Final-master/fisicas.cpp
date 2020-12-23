#include "fisicas.h"
#include <math.h>
#include <cmath>

Fisicas::Fisicas(float posX_, float posY_, float velX_, float velY_, float masa_, float radio_, float K_, float F_)
{
    PX = posX_; //pos en x
    PY = posY_; //pos en y
    mass = masa_; // masa del cuerpo
    R = radio_; //radio del cuerpo
    VX = velX_; //vel en x
    VY = velY_; //vel en y
    AX = 0; //acel en x
    AY = 0; //acel en y
    G = 10; //gravedad
    K = K_; //Resistencia del aire
    F = F_; //Friccion
    V = 0; //vector de velocidad
    dt = 0.1; //delta tiempo
}

Fisicas::~Fisicas()
{

}

void Fisicas::Formulas()
{
    V = pow(((VX*VX)+(VY*VY)),(1/2));
    angulo = atan2(VY,VX);
    AX = -((K*(V*V)*(R*R))/mass)*cos(angulo);
    AY = (-((K*(V*V)*(R*R))/mass)*sin(angulo))-G;
    PX = PX + ((VX*(dt)))+(((AX*(dt*dt)))/2);
    PY = PY + ((VY*(dt)))+(((AY*(dt*dt)))/2);
    VX = VX + AX*dt;
    VY = VY + AY*dt;
}


float Fisicas::getPY() const
{
    return PY;
}

float Fisicas::getMass() const
{
    return mass;
}

float Fisicas::getR() const
{
    return R;
}

float Fisicas::getVX() const
{
    return VX;
}

float Fisicas::getVY() const
{
    return VY;
}

float Fisicas::getE() const
{
    return F;
}

float Fisicas::getPX() const
{
    return PX;
}

void Fisicas::set_vel(float vx, float vy, float px, float py)
{
    VX = vx;
    VY = vy;
    PX = px;
    PY = py;
}
//
