#ifndef ERROR_CHECK_UTILITIES_H
#define ERROR_CHECK_UTILITIES_H

#define CRITICAL_ERROR 0U
#define SUCCESSFUL 1U
#define NON_CRITICAL_ERROR 2U

#define ERROR_CHECK(func_call) 					\
    do {                                        \
        if ((func_call) == CRITICAL_ERROR) {    \
            return 0;                  			\
        } else if ((func_call) == SUCCESSFUL){  \
            ;                                   \
        } else if ((func_call) == NON_CRITICAL_ERROR){ \
            ;                                   \
        }                                       \
    } while (0)

#endif


//look into having bitwise error flagging and/or status register

/*
 * https://betterembsw.blogspot.com/2016/03/multiple-returns-and-error-checking.html
 * */
