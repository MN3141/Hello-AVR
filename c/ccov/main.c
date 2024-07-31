#include <avr/io.h>
#include "../../workspace/ccov/gcov_public.h"

        int main(void)
        {
            __gcov_call_constructors();
            DDRB=1;
        while (1) 
            {
                PORTB=1;
                __gcov_exit();
            }
        }
        