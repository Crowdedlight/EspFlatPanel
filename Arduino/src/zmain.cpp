// Alpaca Ascom control of flat-panel running on FastLED compatible LED strips. 

#include <Arduino.h>

#define BLINK_INTERVAL 200 // blink every 200ms

unsigned long last_blink;
int led_state;

/*
******* REMEMBER TO EDIT CONFIG.H FOR YOUR CONFIGURATION *******
*/
void setup ()
  {
    
    // setup LED Pin
    pinMode(LED_BUILTIN, OUTPUT);
    last_blink = millis();
    led_state = HIGH;
    digitalWrite(LED_BUILTIN, led_state);
  }  // end of setup

void loop ()
  {
    // get time
    unsigned long curr_millis = millis();

    // blink led to show we are still running
    if ((curr_millis - last_blink) > BLINK_INTERVAL) {
      // flip led state
      led_state = led_state ? LOW : HIGH;
      digitalWrite(LED_BUILTIN, led_state);
      last_blink = curr_millis;
    }

    // update loop

  }  // end of loop
