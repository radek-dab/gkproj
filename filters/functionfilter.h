#ifndef FUNCTIONFILTER_H
#define FUNCTIONFILTER_H

#include "filter.h"
#include "function.h"

class FunctionFilter : public Filter
{
public:
    FunctionFilter(const Function &fun)
        : _fun(fun) {}

    const Function & function() const
        { return _fun; }
    void setFunction(const Function &fun)
        { _fun = fun; }

    void apply(Raster &rst, const QRect &win);

private:
    Function _fun;
};

#endif // FUNCTIONFILTER_H
