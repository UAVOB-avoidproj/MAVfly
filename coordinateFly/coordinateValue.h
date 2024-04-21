#ifndef __COORDINATE_VALUE_H__
#define __COORDINATE_VALUE_H__

#include <string>

class coordinateValue {
public:
    coordinateValue(std::string name, double value) : name_(name), value_(value) {}

    std::string getName() const { return name_; }
    double getValue() const { return value_; }

private:
    std::string name_;
    double value_;
};

#endif // __COORDINATE_VALUE_H__