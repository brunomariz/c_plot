#include "../inc/c_plot.h"
#include <time.h>

int main(void)
{
    srand(time(NULL));
    int x[20] = {0, 1, 2, 3, 4, 5, 6, 7, 8, 9, 10, 11, 12, 13, 14, 15, 16, 17, 18, 19};
    int y[20] = {0, rand() % 20, rand() % 20, rand() % 20, rand() % 20, rand() % 20, rand() % 20, rand() % 20, rand() % 20, rand() % 20, rand() % 20, rand() % 20, rand() % 20, rand() % 20, rand() % 20, rand() % 20, rand() % 20, rand() % 20, rand() % 20, 25};
    CP_Function function;
    function.num_points = 20;
    function.x = x;
    function.y = y;

    c_plot_function_show(&function);

    return 0;
}