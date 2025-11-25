#include <stdio.h>

/**
* before_main - function that runs before main
*
* Description: This function is executed automatically before main
* due to the constructor attribute.
*/
void before_main(void) __attribute__ ((constructor));

void before_main(void)
{
printf("You're beat! and yet, you must allow,\n);
printf("I bore my house upon my back	!\n");
}
