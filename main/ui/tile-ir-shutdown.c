#include "tile-ir-shutdown.h"

static tile_t ir_shutdown_tile;
static widget_button_t shutdown_btn;
static widget_label_t shutdown_lbl;
TaskHandle_t xHandle = NULL;

volatile bool is_shutingdown = false;

void shutdown_toggle(struct widget_t *p_widget)
{  
    if ( !is_shutingdown )
    {
        widget_button_set_text(&shutdown_btn, "Stop");
        xTaskCreate(tvbgone, "TVBGone", 10000, NULL, tskIDLE_PRIORITY, &xHandle);        
        is_shutingdown = true;
    }
    else 
    {
        widget_button_set_text(&shutdown_btn, "Start");
        vTaskDelete(xHandle);        
        is_shutingdown = false;
    }
}

tile_t *tile_ir_shutdown_init(void)
{
    tile_init(&ir_shutdown_tile, NULL);

    widget_label_init(&shutdown_lbl, &ir_shutdown_tile, 10, 5, 120, 50, "TVBGone");
    widget_button_init(&shutdown_btn, &ir_shutdown_tile, (240 - 120) / 2, 240 / 2, 120, 30, "Start");
    widget_button_set_handler(&shutdown_btn, shutdown_toggle);

    return &ir_shutdown_tile;
}