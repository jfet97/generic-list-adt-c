#include <stdlib.h>

#define CHECK_POINTER_RETURN(P, R) \
    if (P == NULL)                 \
    {                              \
        return R;                  \
    }

#define CHECK_POINTER_RETURN_NULL(P) \
    CHECK_POINTER_RETURN(P, NULL)

#define CHECK_POINTER_RETURN_VOID(P) \
    if (P == NULL)                   \
    {                                \
        return;                      \
    }

#define IF_NOT_NULL(P, CODE) \
    if (P != NULL)           \
    {                        \
        CODE                 \
    }

#define IF_NULL(P, CODE) \
    if (P == NULL)       \
    {                    \
        CODE             \
    }
