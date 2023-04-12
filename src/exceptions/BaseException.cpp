#include "exceptions/BaseException.h"

BaseException::BaseException(const string &message)
        : runtime_error(message) {}
