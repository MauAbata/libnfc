/*-
 * Free/Libre Near Field Communication (NFC) library
 *
 * Libnfc historical contributors:
 * Copyright (C) 2009      Roel Verdult
 * Copyright (C) 2009-2013 Romuald Conty
 * Copyright (C) 2010-2012 Romain Tartière
 * Copyright (C) 2010-2013 Philippe Teuwen
 * Copyright (C) 2012-2013 Ludovic Rousseau
 * See AUTHORS file for a more comprehensive list of contributors.
 * Additional contributors of this file:
 *
 * This program is free software: you can redistribute it and/or modify it
 * under the terms of the GNU Lesser General Public License as published by the
 * Free Software Foundation, either version 3 of the License, or (at your
 * option) any later version.
 *
 * This program is distributed in the hope that it will be useful, but WITHOUT
 * ANY WARRANTY; without even the implied warranty of MERCHANTABILITY or
 * FITNESS FOR A PARTICULAR PURPOSE.  See the GNU General Public License for
 * more details.
 *
 * You should have received a copy of the GNU Lesser General Public License
 * along with this program.  If not, see <http://www.gnu.org/licenses/>
 */

/**
 * @file acr122_usb.h
 * @brief Driver for ACR122 devices using direct USB connection (without PCSC)
 */

#ifndef __NFC_DRIVER_ACR122_USB_H__
#define __NFC_DRIVER_ACR122_USB_H__

#include <nfc/nfc-types.h>

#define ACR122_LED_NO_CHANGE 0xFFu
#define ACR122_LED_OFF 0x00u
#define ACR122_LED_ON 0x01u
#define ACR122_LED_START_ON 0x02u
#define ACR122_LED_BLINK 0x04u

#define ACR122_STATE_TO_BITS(state) ( \
    (state == 0xFFu) ? 0x00u \
                     : (state & ACR122_LED_ON) \
                       | (0x04u) \
                       | ((state & ACR122_LED_START_ON) << 0x03u) \
                       | ((state & ACR122_LED_BLINK) << 0x04u))

#define ACR122_BUZZER_OFF 0x00
#define ACR122_BUZZER_ON_T1 0x01
#define ACR122_BUZZER_ON_T2 0x02
#define ACR122_BUZZER_ON_ALL 0x03

typedef struct {
    uint8_t red;
    uint8_t green;
    uint8_t blink_on;
    uint8_t blink_off;
    uint8_t blink_repetition;
    uint8_t buzzer;
} acr122_led_state;

#define ACR122_LED_DEFAULT() { \
    ACR122_LED_NO_CHANGE, \
    ACR122_LED_NO_CHANGE, \
    0x1E, 0x1E, 0x00, ACR122_BUZZER_OFF \
}

extern const struct nfc_driver acr122_usb_driver;
int acr122_set_led_state(nfc_device *pnd, acr122_led_state *state);

#endif // ! __NFC_DRIVER_ACR122_USB_H__
