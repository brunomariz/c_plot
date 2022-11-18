#include "../inc/c_plot.h"

int main(void)
{
    int x[10] = {0, 1, 2, 3, 4, 5, 6, 7, 8, 9};
    int y[10] = {0, 1, 4, 9, 16, 25, 36, 49, 64, 81};
    CP_Function function;
    function.num_points = 10;
    function.x = x;
    function.y = y;

    c_plot_function_show(&function);

    return 0;
}