#include <stdint.h>

#include <esp_log.h>
#include <lwip/sockets.h>
#include <lwip/sys.h>

#include "common.h"
#include "net_tasks.h"

//TODO:Change this after getting a static ip for the server
#define SERVER_IP "191.52.224.162"

TaskHandle_t net_client_t_handle;
TaskHandle_t net_server_t_handle;

void net_client_task(void *args)
{
    uint8_t buffer[BUFF_SIZE];
    char * rcv_buffer;
    int flag = 0;

    mesh_addr_t sender;
    mesh_data_t data;

    struct sockaddr_in dest_addr = 
    {
        .sin_addr.s_addr = inet_addr(SERVER_IP),
        .sin_family = AF_INET,
        .sin_port = htons(SERVER_PORT)
    };

    int sock = socket(AF_INET, SOCK_DGRAM, IPPROTO_IP);

    while(1)
    {
        /*
        if(esp_mesh_recv(&sender, &data, portMAX_DELAY, &flag, NULL, 0) == ESP_OK){
            asprintf(&tx_buf, "remetente: "MACSTR", msg: %s\n", MAC2STR(sender.addr), data.data); // prepara buffer para envio
            ESP_LOGI(MESH_TAG, "%s", tx_buf); // imprime buffer nos logs
            sendto(sock, tx_buf, strlen(tx_buf), 0, (struct sockaddr *)&dest_addr, sizeof(dest_addr)); // enviar buffer para servidor remoto
            free(tx_buf);
        }
        */
    }

}

void net_server_task(void *args)
{
    uint8_t buffer[BUFF_SIZE] = {0};
    mesh_data_t data;
    data.data = buffer;
    data.size = BUFF_SIZE;

    struct sockaddr_in dest_addr = 
    {
        .sin_addr.s_addr = inet_addr(SERVER_IP),
        .sin_family = AF_INET,
        .sin_port = htons(CLIENT_PORT)
    };

    int sock = socket(AF_INET, SOCK_DGRAM, IPPROTO_IP);
    bind(sock, (struct sockaddr *)&dest_addr, sizeof(dest_addr));

    while(1)
    {

    }
}

void net_system_init()
{
    if(&net_client_t_handle == NULL)
    {
        xTaskCreatePinnedToCore(net_client_task, "NET CLIENT", 2048, NULL, configMAX_PRIORITIES - 3, &net_client_t_handle, 0);
    }

    if(&net_server_t_handle == NULL)
    {    
        xTaskCreatePinnedToCore(net_server_task, "NET SERVER", 2048, NULL, configMAX_PRIORITIES - 3, &net_server_t_handle, 0);
    }
}