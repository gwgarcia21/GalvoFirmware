#pragma once
// clang-format off

/*
    3axis_v4.h
    Part of Grbl_ESP32

    Pin assignments for the ESP32 Development Controller, v4.1 and later.
    https://github.com/bdring/Grbl_ESP32_Development_Controller
    https://www.tindie.com/products/33366583/grbl_esp32-cnc-development-board-v35/

    2018    - Bart Dring
    2020    - Mitch Bradley

    Grbl_ESP32 is free software: you can redistribute it and/or modify
    it under the terms of the GNU General Public License as published by
    the Free Software Foundation, either version 3 of the License, or
    (at your option) any later version.

    Grbl is distributed in the hope that it will be useful,
    but WITHOUT ANY WARRANTY; without even the implied warranty of
    MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
    GNU General Public License for more details.

    You should have received a copy of the GNU General Public License
    along with Grbl_ESP32.  If not, see <http://www.gnu.org/licenses/>.
*/


/*#define MACHINE_NAME            "DueGalvoScanner"

#define X_STEP_PIN              GPIO_NUM_12
#define X_DIRECTION_PIN         GPIO_NUM_14
#define Y_STEP_PIN              GPIO_NUM_26
#define Y_DIRECTION_PIN         GPIO_NUM_15

#define X_LIMIT_PIN             GPIO_NUM_17
#define Y_LIMIT_PIN             GPIO_NUM_17

#define STEPPERS_DISABLE_PIN    GPIO_NUM_13
#define SPINDLE_TYPE            SpindleType::LASER
#define LASER_OUTPUT_PIN        GPIO_NUM_2              // labeled SpinPWM
#define DEFAULT_LASER_MODE      1                       // false
#define COOLANT_FLOOD_PIN       GPIO_NUM_25             // labeled Flood

#define CONTROL_SAFETY_DOOR_PIN GPIO_NUM_35             // labeled Door,  needs external pullup //DUE-MODIFICOU

#define DEFAULT_HOMING_CYCLE_0 bit(Y_AXIS)
#define DEFAULT_HOMING_CYCLE_1 bit(X_AXIS)

#define DEFAULT_HOMING_DIR_MASK         1
#define DEFAULT_HOMING_ENABLE           1       // $22 
#define DEFAULT_HOMING_SEEK_RATE        4000.0  // mm/min
#define DEFAULT_HOMING_DEBOUNCE_DELAY   250     // msec (0-65k)
#define DEFAULT_HOMING_PULLOFF          3.0     // mm
#define DEFAULT_HOMING_FEED_RATE        250.0   // mm/min

#define DEFAULT_SOFT_LIMIT_ENABLE 0 // false
#define DEFAULT_HARD_LIMIT_ENABLE 0  // true	

// =========== AXIS DIRECTION ======

#define DEFAULT_DIRECTION_INVERT_MASK 6  // $3 

// ===========  AXIS RESOLUTION ======

#define DEFAULT_X_STEPS_PER_MM 80.0     // $100 
#define DEFAULT_Y_STEPS_PER_MM 80.0     // $100 

// ============ AXIS MAX SPPED =========

#define DEFAULT_X_MAX_RATE 10000.0  // mm/min // $110 
#define DEFAULT_Y_MAX_RATE 10000.0  // mm/min // $111

// ============== Axis Acceleration =========

#define DEFAULT_X_ACCELERATION 1500.0 // $120 
#define DEFAULT_Y_ACCELERATION 1500.0 // $121

// ========= AXIS MAX TRAVEL ============

#define DEFAULT_X_MAX_TRAVEL 420.0  // $130 mm NOTE: Must be a positive value.
#define DEFAULT_Y_MAX_TRAVEL 320.0  // mm NOTE: Must be a positive value.

#define DEFAULT_SPINDLE_RPM_MAX 1200.0 */
