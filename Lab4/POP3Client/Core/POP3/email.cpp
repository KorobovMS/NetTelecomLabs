#include "email.h"

Email::Email(int n, const Headers& h, const QString& b) :
    number(n),
    headers(h),
    body(b)
{
}
