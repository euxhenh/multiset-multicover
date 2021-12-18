#ifndef UTILS_H
#define UTILS_H

#include <exception>

#ifdef DEBUG
#include <iostream>
using std::cerr;
using std::cout;
using std::endl;
#endif

class Exception : public std::exception {
public:
    Exception(const char* str)
    {
        this->str = str;
    }

    virtual const char* what() const throw()
    {
        return this->str;
    }

private:
    const char* str;
};

#endif // UTILS_H