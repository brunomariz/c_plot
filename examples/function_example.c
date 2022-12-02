#include "../inc/c_plot.h"
#include <time.h>

int main(void)
{
    srand(time(NULL));
    int x[200];
    int y[200];
    x[0] = 0;
    y[0] = 0;
    for (int i = 1; i < 200; i++)
    {
        int disturbance = rand() % 2 * 10 - 5;
        y[i] = y[i - 1] + disturbance;
        x[i] = i;
    }

    CP_Function function;
    function.num_points = 200;
    function.x = x;
    function.y = y;

    c_plot_function_show(&function);

    return 0;
}