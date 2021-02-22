/*
Copyright 2021 Masaru Nemoto <nemolize@gmail.com>

This program is free software: you can redistribute it and/or modify
it under the terms of the GNU General Public License as published by
the Free Software Foundation, either version 2 of the License, or
(at your option) any later version.

This program is distributed in the hope that it will be useful,
but WITHOUT ANY WARRANTY; without even the implied warranty of
MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
GNU General Public License for more details.

You should have received a copy of the GNU General Public License
along with this program.  If not, see <http://www.gnu.org/licenses/>.
*/

#pragma once

#ifdef __cplusplus
extern "C" {
#endif

#include <math.h>
#include "host.h"
#include "timer.h"
#include "debug.h"

#include "./fixed_point_number.h"

void pointing_device_task(void);
void pointing_device_set_report(report_mouse_t newMouseReport);
void pointing_device_send(void);

//void pointing_device_task(void);
void mousekey_on(uint8_t code);
void mousekey_off(uint8_t code);
void mousekey_clear(void);
void mousekey_send(void);

#ifdef __cplusplus
}
#endif

struct Vector {
  FIXED_POINT_NUMBER x, y;
  Vector() : x(0), y(0) {}
};

struct PhysicsConfig {
  FIXED_POINT_NUMBER force, mass, friction, dtDivMath;
  PhysicsConfig(
    float force,
    float mass,
    float friction,
    float dt
  ):
    force(FLOAT_TO_FPN(force)),
    mass(FLOAT_TO_FPN(mass)),
    friction(FLOAT_TO_FPN(friction)),
    dtDivMath(FLOAT_TO_FPN(dt/mass))
  {};
};

struct PhysicsState {
public:
  PhysicsState(PhysicsConfig config) : accel(), velocity(), config(config) {}
  void advance(){
    velocity.x += FPN_MUL(accel.x, config.dtDivMath);  // v=at, a = F/m
    velocity.y += FPN_MUL(accel.y, config.dtDivMath);
    apply_friction_2d(config, velocity);
  }
  const Vector& getPosition() {
    return velocity;
  }

  Vector accel;
  Vector velocity;
private:
  PhysicsConfig config;
  void apply_friction_2d(const PhysicsConfig &conf, Vector &velocity) {
    velocity.x = apply_friction_1d(conf, velocity.x);
    velocity.y = apply_friction_1d(conf, velocity.y);
  }
  FIXED_POINT_NUMBER apply_friction_1d(
    const PhysicsConfig &conf,
    FIXED_POINT_NUMBER velocity
  ) {
    const auto sign = (velocity > 0) - (velocity < 0);
    velocity -= sign * conf.friction;  //
    const auto afterSign = (velocity > 0) - (velocity < 0);
    return sign != afterSign? 0 : velocity;
  }
};

#ifndef MOUSEKEY_FRAMERATE
#define MOUSEKEY_FRAMERATE 60.0
#endif
#ifndef MOUSEKEY_WHEEL_FRAMERATE
#define MOUSEKEY_WHEEL_FRAMERATE 60.0
#endif
#ifndef MOUSEKEY_GRAVITY
#define MOUSEKEY_GRAVITY 9.8
#endif
#ifndef MOUSEKEY_CURSOR_FORCE
#define MOUSEKEY_CURSOR_FORCE 1100
#endif
#ifndef MOUSEKEY_CURSOR_MASS
#define MOUSEKEY_CURSOR_MASS 1
#endif
#ifndef MOUSEKEY_CURSOR_FRICTION
#define MOUSEKEY_CURSOR_FRICTION 95
#endif
#ifndef MOUSEKEY_WHEEL_FORCE
#define MOUSEKEY_WHEEL_FORCE 64
#endif
#ifndef MOUSEKEY_WHEEL_MASS
#define MOUSEKEY_WHEEL_MASS 1
#endif
#ifndef MOUSEKEY_WHEEL_FRICTION
#define MOUSEKEY_WHEEL_FRICTION 6
#endif

#define MOUSEKEY_DT (1.0 / MOUSEKEY_FRAMERATE)
#define MOUSEKEY_CURSOR_FRICTION_MUL_DT_GRAVITY_MASS (MOUSEKEY_CURSOR_FRICTION * MOUSEKEY_GRAVITY * MOUSEKEY_DT * (float)MOUSEKEY_CURSOR_MASS)
#define MOUSEKEY_WHEEL_FRICTION_MUL_DT_GRAVITY_MASS (MOUSEKEY_WHEEL_FRICTION * MOUSEKEY_GRAVITY * MOUSEKEY_DT * (float)MOUSEKEY_CURSOR_MASS)
static const int interval = 1000 / MOUSEKEY_FRAMERATE;
static const int interval_wheel = 1000 / MOUSEKEY_WHEEL_FRAMERATE;
#define MOUSEKEY_CURSOR_DT_DIV_MASS FLOAT_TO_FPN(MOUSEKEY_DT / MOUSEKEY_CURSOR_MASS)
#define MOUSEKEY_WHEEL_DT_DIV_MASS FLOAT_TO_FPN(MOUSEKEY_DT / MOUSEKEY_WHEEL_MASS)

