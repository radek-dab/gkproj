#ifndef ASSERT_H
#define ASSERT_H

#include <QtGlobal>

#define UNREACHED() Q_ASSERT_X(0, __FUNCTION__, "should not be reached")

#endif // ASSERT_H
