#include <stdio.h>
#include "pico/stdlib.h"

int main(void)
{
    stdio_init_all();

    printf("================================\n");
    printf("      PICO LIGHT MONITOR\n");
    printf("================================\n");

    while (true)
    {
        printf("Systeme operationnel !\n");

        sleep_ms(1000);
    }

    return 0;
}