#include <Arduino.h>
#include "LED.h"
#include <OneButton.h>

LED led(LED_PIN, LED_ACT);

void btnPush();
void btnHold();
OneButton button(BTN_PIN, !BTN_ACT);

void setup()
{
    led.off();
    button.attachClick(btnPush);
    button.attachLongPressStart(btnHold);
}

void loop()
{
    led.loop();
    button.tick();
}

void btnPush()
{
    led.flip();
}

void btnHold()
{
    led.blink(200);
}