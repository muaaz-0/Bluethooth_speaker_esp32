#include "BluetoothA2DPSink.h"


//I2SStream i2s;
BluetoothA2DPSink a2dp_sink;

void setup() {
  i2s_pin_config_t my_pin_config={
        .bck_io_num = 27, z
    .ws_io_num = 26,
    .data_out_num = 25,
    .data_in_num=I2S_PIN_NO_CHANGE
  };
  /*
    auto cfg = i2s.defaultConfig();
    cfg.pin_bck = 27;
    cfg.pin_ws = 26;
    cfg.pin_data = 25;
    i2s.begin(cfg);
*/
    a2dp_sink.set_pin_config(my_pin_config);
    a2dp_sink.start("MyMusic");
}

void loop() {
}
