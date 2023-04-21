#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <inttypes.h>
#include "freertos/FreeRTOS.h"
#include "freertos/task.h"
#include "freertos/queue.h"
#include "driver/gpio.h"

#define GPIO_OUTPUT_IO_0  GPIO_NUM_2
#define GPIO_OUTPUT_IO_1  GPIO_NUM_3
#define GPIO_OUTPUT_PIN_SEL (1ULL<<GPIO_OUTPUT_IO_0)|(1ULL<<GPIO_OUTPUT_IO_1)


/*
 *  Before making a new proj.
 *  adding path_esp.txt to Settings\Path\
 * */

void gpio_init(){
    gpio_config_t gpio_out ={
            .intr_type = GPIO_INTR_DISABLE,
            .mode = GPIO_MODE_OUTPUT,
            .pull_down_en = GPIO_PULLDOWN_DISABLE,
            .pull_up_en = GPIO_PULLUP_DISABLE,
            .pin_bit_mask = GPIO_OUTPUT_PIN_SEL,
    };
    if(gpio_config(&gpio_out)==ESP_OK){
        printf("success");
    }
    else{
        printf("GPIO CONFIG FAILED");
    }

}
void Print_Hello_World(void* arg){
    while(1){
    printf("Hello World\n");
    vTaskDelay(1000/portTICK_PERIOD_MS);
}
}
void Print_Hxy(void* pVoid){
    while(1){
    printf("Hxy\n");
    vTaskDelay(1000/portTICK_PERIOD_MS);
    }
}
void LED_Beam(){
    while(1){
        gpio_set_level(GPIO_OUTPUT_IO_0,1);
        vTaskDelay(100/portTICK_PERIOD_MS);
        gpio_set_level(GPIO_OUTPUT_IO_0,0);
        vTaskDelay(200/portTICK_PERIOD_MS);
    }
}
void app_main(void)
{
    gpio_init();
    xTaskCreate(Print_Hello_World,"hello_world",2000,NULL,1,NULL);
    xTaskCreate(Print_Hxy,"Xyt",2000,NULL,1,NULL);
    xTaskCreate(&LED_Beam,"LED",2000,NULL,2,NULL);
//   // xTaskCreate(&Print_Hello_World,"Print_Hello_World",100,NULL,2,NULL),
//    xTaskCreate(&Blue_LED_Beam,"Blue_LED_Beam",100,NULL,1,NULL);
//    xTaskCreate(&RED_LED_Beam,"RED_LED_Beam",100,NULL,1,NULL);

}
