/**
 * Licensed to the Apache Software Foundation (ASF) under one
 * or more contributor license agreements.  See the NOTICE file
 * distributed with this work for additional information
 * regarding copyright ownership.  The ASF licenses this file
 * to you under the Apache License, Version 2.0 (the
 * "License"); you may not use this file except in compliance
 * with the License.  You may obtain a copy of the License at
 * 
 *  http://www.apache.org/licenses/LICENSE-2.0
 *
 * Unless required by applicable law or agreed to in writing,
 * software distributed under the License is distributed on an
 * "AS IS" BASIS, WITHOUT WARRANTIES OR CONDITIONS OF ANY
 * KIND, either express or implied.  See the License for the
 * specific language governing permissions and limitations
 * under the License.
 */

#include <assert.h>
#include <string.h>

#include "sysinit/sysinit.h"
#include "os/os.h"
#include "bsp/bsp.h"
#include "hal/hal_gpio.h"

/**
 * main
 *
 * The main task for the project.
 *
 * @return int NOTE: this function should never return!
 */

int
main(int argc, char **argv)
{
    int rc;

    sysinit();

    hal_gpio_init_out(LCD_BACKLIGHT_LOW_PIN, 1);
    hal_gpio_init_out(LCD_BACKLIGHT_MED_PIN, 1);
    hal_gpio_init_out(LCD_BACKLIGHT_HIGH_PIN, 1);

    hal_gpio_init_out(VIBRATOR_PIN, 1);

    while (1) {
        /* Wait one second */
        os_time_delay(OS_TICKS_PER_SEC);

        /* Toggle the LED */
        hal_gpio_toggle(LCD_BACKLIGHT_LOW_PIN);
        hal_gpio_toggle(LCD_BACKLIGHT_MED_PIN);
        hal_gpio_toggle(LCD_BACKLIGHT_HIGH_PIN);

        hal_gpio_toggle(VIBRATOR_PIN);
    }
    assert(0);

    return rc;
}
