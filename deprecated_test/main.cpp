#include <stdio.h>

__declspec(deprecated)
void test(void)
{
    printf("I'm deprecated");
}

int main()
{
    test();
    return 0;
}