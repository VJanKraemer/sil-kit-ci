// Copyright (c) Vector Informatik GmbH. All rights reserved.

#pragma once

#include "silkit/participant/exception.hpp"

#define _SK_STRING(X) #X
#define _SK_QUOTE(X) _SK_STRING(X)

#define SILKIT_ASSERT(EXPR) \
    do {\
        if(!(EXPR)) \
        { \
            throw SilKit::AssertionError("SilKit: Assertion \""  #EXPR  "\" failed in file "\
            __FILE__ ":" _SK_QUOTE(__LINE__)\
            ); \
        } \
    } while(false)
