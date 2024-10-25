#pragma once
#include "common.h"

TaskHandle_t send_meter_t_handle;
TaskHandle_t check_health_t_handle;

void send_meter_attrib_task(void *args)
{

}

void check_mesh_health_task(void *args)
{

}

void init_utility_systems()
{
    if(send_meter_t_handle == NULL)
    {
        xTaskCreatePinnedToCore(send_meter_attrib_task, "SEND ATTRIB", 2048, NULL, 2, send_meter_attrib_task, 1);
    }
    
    if(check_health_t_handle == NULL)
    {
        xTaskCreatePinnedToCore(check_mesh_health_task, "CHECK HEALTH", 2048, NULL, 2, check_health_t_handle, 0);
    }
}