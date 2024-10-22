#include <esp_log.h>
#include "mesh_network.h"

#define NET_SSID "ELHP"
#define NET_PASSWD "eletra2023"
#define MESH_PASSWD "meterfarm"

QueueHandle_t mesh_send_q;
QueueHandle_t mesh_rcv_q;

bool is_mesh_connected = false;
int mesh_layer = -1;
esp_netif_t *netif_sta = NULL;

void ip_events(void *args, esp_event_base_t event_base, int32_t event_id, void *event_data)
{
    ip_event_got_ip_t *event = (ip_event_got_ip_t *)event_data;
    ESP_LOGI(NET_TAG, "<IP_EVENT_STA_GET> IP:" IPSTR, IP2STR(&event->ip_info.ip));
}


bool is_mesh_parent_connected()
{
    return is_mesh_connected;
}

/*
char* get_mesh_root_ip()
{

}
*/

void mesh_rcv_p2p_task()
{

}

void mesh_send_p2p_task()
{

} 

void wifi_events()
{

}

void mesh_init()
{
    ESP_ERROR_CHECK(esp_mesh_init());
    ESP_ERROR_CHECK(esp_event_handler_register(MESH_EVENT, ESP_EVENT_ANY_ID, &mesh_events, NULL));

    mesh_cfg_t config = MESH_INIT_CONFIG_DEFAULT();
    memcpy((uint8_t *) &config.mesh_id, MAC_ADDR, 6);

    config.channel = 0;
    config.router.ssid_len = strlen(NET_SSID);
    memcpy((uint8_t *) &config.router.ssid, NET_SSID, config.router.ssid_len);
    memcpy((uint8_t *) &config.router.password, NET_PASSWD, strlen(NET_PASSWD));

    config.mesh_ap.max_connection = 2;
    config.mesh_ap.nonmesh_max_connection = 1;

    memcpy((uint8_t *)&config.mesh_ap.password, MESH_PASSWD, strlen(MESH_PASSWD));

    ESP_ERROR_CHECK(esp_mesh_set_config(&config));
    ESP_ERROR_CHECK(esp_mesh_start());
    ESP_ERROR_CHECK(esp_mesh_set_self_organized(true, true));
}

void wifi_init()
{
    esp_err_t ret = nvs_flash_init();
    if (ret == ESP_ERR_NVS_NO_FREE_PAGES || ret == ESP_ERR_NVS_NEW_VERSION_FOUND)
    {
        ESP_ERROR_CHECK(nvs_flash_erase());
        ret = nvs_flash_init();
    }

    ESP_ERROR_CHECK(ret);

    ESP_ERROR_CHECK(esp_netif_init());
    
    ESP_ERROR_CHECK(esp_event_loop_create_default());
    
    ESP_ERROR_CHECK(esp_netif_create_default_wifi_mesh_netifs(&netif_sta, NULL));
    
    wifi_init_config_t config = WIFI_INIT_CONFIG_DEFAULT();
    ESP_ERROR_CHECK(esp_wifi_init(&config));
    //ESP_ERROR_CHECK(esp_event_handler_register(WIFI_EVENT, ESP_EVENT_ANY_ID, &wifi_events, NULL));
    ESP_ERROR_CHECK(esp_event_handler_register(IP_EVENT, ESP_EVENT_ANY_ID, &ip_events, NULL));
    ESP_ERROR_CHECK(esp_wifi_set_storage(WIFI_STORAGE_FLASH));
    ESP_ERROR_CHECK(esp_wifi_start());
}

void mesh_system_init()
{
    wifi_init();
    mesh_init();
}