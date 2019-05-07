#ifndef _UNIT_H_
#define _UNIT_H_
#include <string>
#include <list>
#include <unordered_map>
#include "../common/coord.h"

using namespace std;
class unit;
class order;
class coord;
typedef long long int64;
typedef list<order> OrderList;
typedef unordered_map<int64,unit> UnitMap;

struct order
{
    unsigned char orderType_;
    union 
    {
        coord coord_;
        unit *targetUnit_;
    }target_;
};

struct UnitDetail
{
    string name_;
    int type_;
    int id_;
    double x_;
    double y_;
    double z_;
    double r_;
    double height_;
    double moveSpeed_;
    double attackSpeed_;
    double turnSpeed_;
    double faceAngle_;
    bool visible_;
    OrderList order_;
};

class unit
{
public:
    unit();
    void reset();
    int create(double x = 0, double y = 0, double r = 0, double faceAngle = 0);
    //set
    void name(const std::string& param);
    void type(int param);
    void id(int param);
    void x(double param);
    void y(double param);
    void z(double param);
    void r(double param);
    void height(double param);
    void moveSpeed(double param);
    void attackSpeed(double param);
    void turnSpeed(double param);
    void faceAngle(double param);
    void visible(bool param);
    void addOrder(order order);
    //get
    UnitDetail detail();
    std::string name();
    int type();
    int id();
    double x();
    double y();
    double z();
    double r();
    double height();
    double moveSpeed();
    double attackSpeed();
    double turnSpeed();
    double faceAngle();
    bool visible();
    OrderList& orderList();
public:
    static UnitMap unitMap_;
    static int index_;
private:
    UnitDetail detail_;
};



#endif