#include "../inc/c_plot.h"

int c_plot_internal_menu_reset_scale_button_draw(SDL_Renderer *renderer, CP_MouseInfo *mouse_info, CP_MenuInfo *menu_info, int menu_bg_height)
{
    int button_hot = 0;
    int button_active = 0;
    if (mouse_info->current_mouse_position.x > menu_info->position->x && mouse_info->current_mouse_position.x < menu_info->position->x + 30 &&
        mouse_info->current_mouse_position.y > menu_info->position->y && mouse_info->current_mouse_position.y < menu_info->position->y + 30)
    {
        button_hot = 1;
        if (mouse_info->mouse_down)
        {
            button_active = 1;
        }
    }
    int padding = button_hot ? 8 : 9;
    int lines_length = button_hot ? 5 : 3;
    SDL_SetRenderDrawColor(renderer, 0, 0, 0, 255 * 0.5);
    // Top left
    SDL_RenderDrawLine(renderer, menu_info->position->x + padding, menu_info->position->y + padding, menu_info->position->x + padding, menu_info->position->y + padding + lines_length);
    SDL_RenderDrawLine(renderer, menu_info->position->x + padding, menu_info->position->y + padding, menu_info->position->x + padding + lines_length, menu_info->position->y + padding);
    // Top right
    SDL_RenderDrawLine(renderer, menu_info->position->x + menu_bg_height - padding, menu_info->position->y + padding, menu_info->position->x + menu_bg_height - padding - lines_length, menu_info->position->y + padding);
    SDL_RenderDrawLine(renderer, menu_info->position->x + menu_bg_height - padding, menu_info->position->y + padding, menu_info->position->x + menu_bg_height - padding, menu_info->position->y + padding + lines_length);

    // Bottom left
    SDL_RenderDrawLine(renderer, menu_info->position->x + padding, menu_info->position->y + menu_bg_height - padding, menu_info->position->x + padding, menu_info->position->y + menu_bg_height - padding - lines_length);
    SDL_RenderDrawLine(renderer, menu_info->position->x + padding, menu_info->position->y + menu_bg_height - padding, menu_info->position->x + padding + lines_length, menu_info->position->y + menu_bg_height - padding);
    // Bottom right
    SDL_RenderDrawLine(renderer, menu_info->position->x + menu_bg_height - padding, menu_info->position->y + menu_bg_height - padding, menu_info->position->x + menu_bg_height - padding - lines_length, menu_info->position->y + menu_bg_height - padding);
    SDL_RenderDrawLine(renderer, menu_info->position->x + menu_bg_height - padding, menu_info->position->y + menu_bg_height - padding, menu_info->position->x + menu_bg_height - padding, menu_info->position->y + menu_bg_height - padding - lines_length);

    return button_active ? 1 : 0;
}

int c_plot_menu_draw(SDL_Renderer *renderer, CP_MouseInfo *mouse_info, CP_MenuInfo *menu_info)
{
    const int menu_bg_width = 30;
    const int menu_bg_height = 30;

    SDL_Rect menu_bg_rect;
    menu_bg_rect.h = menu_bg_height;
    menu_bg_rect.w = menu_bg_width;
    menu_bg_rect.x = menu_info->position->x;
    menu_bg_rect.y = menu_info->position->y;
    // Draw menu bg
    SDL_SetRenderDrawColor(renderer, 0, 0, 0, 255 * 0.1);
    SDL_RenderFillRect(renderer, &menu_bg_rect);
    // Draw reset zoom button
    int clicked_scale_button = c_plot_internal_menu_reset_scale_button_draw(renderer, mouse_info, menu_info, menu_bg_height);
    return clicked_scale_button;
}
