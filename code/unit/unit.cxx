#include "unit.h"
UnitMap unit::unitMap_;
int unit::index_=0;
#define XXXX 
unit::unit()
{
    reset();
}

void unit::reset()
{
    this->detail_.name_.clear();
    this->detail_.id_=0;
    this->detail_.x_=0;
    this->detail_.y_=0;
    this->detail_.z_=0;
    this->detail_.height_=0;
    this->detail_.moveSpeed_=0;
    this->detail_.attackSpeed_=0;
    this->detail_.turnSpeed_=0;
    this->detail_.faceAngle_=0;
    this->detail_.visible_=true;
}

int unit::create(double x, double y, double r, double faceAngle)
{
    this->detail_.id_=index_++;
    this->detail_.moveSpeed_=255;
    this->detail_.turnSpeed_=3.0;
    this->detail_.faceAngle_=faceAngle;
    this->detail_.r_=r;
    unitMap_[this->detail_.id_]=*this;
    return this->detail_.id_;
}

void unit::name(const std::string& param)
{
    this->detail_.name_=param;
}

void unit::type(int param)
{
    this->detail_.type_=param;
}

void unit::id(int param)
{
    this->detail_.id_=param;
}

void unit::x(double param)
{
    this->detail_.x_=param;
}

void unit::y(double param)
{
    this->detail_.y_=param;
}

void unit::z(double param)
{
    this->detail_.z_=param;
}

void unit::r(double param)
{
    this->detail_.r_=param;
}

void unit::height(double param)
{
    this->detail_.height_=param;
}

void unit::moveSpeed(double param)
{
    this->detail_.moveSpeed_=param;
}

void unit::attackSpeed(double param)
{
    this->detail_.attackSpeed_=param;
}

void unit::turnSpeed(double param)
{
    this->detail_.turnSpeed_=param;
}

void unit::faceAngle(double param)
{
    this->detail_.faceAngle_=fmod(param, 360.0);
}

void unit::visible(bool param)
{
    this->detail_.visible_=param;
}

void unit::addOrder(order order)
{
     this->detail_.order_.push_back(order);
}

UnitDetail unit::detail()
{
    return this->detail_;
}

string unit::name()
{
    return this->detail_.name_;
}

int unit::type()
{
    return this->detail_.type_;
}

int unit::id()
{
    return this->detail_.id_;
}

double unit::x()
{
    return this->detail_.x_;
}

double unit::y()
{
    return this->detail_.y_;
}

double unit::z()
{
    return this->detail_.z_;
}

double unit::r()
{
    return this->detail_.r_;
}

double unit::height()
{
    return this->detail_.height_;
}

double unit::moveSpeed()
{
    return this->detail_.moveSpeed_;
}

double unit::attackSpeed()
{
    return this->detail_.attackSpeed_;
}

double unit::turnSpeed()
{
    return this->detail_.turnSpeed_;
}

double unit::faceAngle()
{
    return this->detail_.faceAngle_;
}

bool unit::visible()
{
    return this->detail_.visible_;
}
OrderList& unit::orderList()
{
    return this->detail_.order_;
}


