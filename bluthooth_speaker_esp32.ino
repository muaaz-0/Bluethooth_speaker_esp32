#include <Wire.h>
#include <Adafruit_GFX.h>
#include <Adafruit_SSD1306.h>
#include "BluetoothA2DPSink.h"
#include "AudioTools.h"

#if CONFIG_FREERTOS_UNICORE
static const BaseType_t app_cpu=0;
#else 
static const BaseType_t app_cpu=1;
#endif

static TaskHandle_t task_OLED_Handle= NULL ;
static TaskHandle_t task_Speaker_Handle= NULL ;


BluetoothA2DPSink a2dp_sink;

#define SCREEN_WIDTH 128 
#define SCREEN_HEIGHT 64 

Adafruit_SSD1306 display(SCREEN_WIDTH, SCREEN_HEIGHT, &Wire, -1);

void task_OLED(void *parameter) {
  
  while(1) {
    display.println("Bluetooth Speaker");
    display.display();
     delay(100);
  }
}


 /*void task_Speaker(void *parameter){
  
 while(1){


  }
  }*/

void setup() {

 Serial.begin(115200);

 //----------------------------------- 
  i2s_pin_config_t my_pin_config={
        .bck_io_num = 27,
    .ws_io_num = 26,
    .data_out_num = 25,
    .data_in_num=I2S_PIN_NO_CHANGE
  };
 
    a2dp_sink.set_pin_config(my_pin_config);
    
a2dp_sink.start("MyMusic");

  if(!display.begin(SSD1306_SWITCHCAPVCC, 0x3C)) { 
    Serial.println(F("SSD1306 allocation failed"));
    for(;;);
  }
  delay(2000);
  
  display.clearDisplay();

  display.setTextSize(2);
  display.setTextColor(WHITE);
  display.setCursor(0, 10);
    //-----------------------------

    xTaskCreatePinnedToCore( task_OLED,
                                "Display OLED",
                                2000,
                                NULL,
                                2,
                                &task_OLED_Handle,
                                app_cpu);
   /* xTaskCreatePinnedToCore( task_Speaker,
                              "Connect Speaker",
                              2000,
                              NULL,
                              2,
                              &task_Speaker_Handle,
                              app_cpu);*/
}

void loop() {
}
