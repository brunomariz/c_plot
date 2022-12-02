#include "../inc/c_plot.h"

int c_plot_util_calculate_spacing(int min_spacing, int max_spacing, float scale)
{
    /// @brief Calculates the minimum number of times scale should be multiplied
    ///        to be greater than min_spacing or maximum number of times scale should
    ///        be divided by to be less than max_spacing
    /// @param min_spacing
    /// @param scale
    if (scale < min_spacing)
    {
        return scale * ceil(min_spacing / scale);
    }
    else if (scale > max_spacing)
    {
        return scale / ceil(scale / max_spacing);
    }
    else
    {
        return scale;
    }
}