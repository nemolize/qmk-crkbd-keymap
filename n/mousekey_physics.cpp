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

#include "mousekey_physics.hpp"

static report_mouse_t mouse_report = {};
static uint16_t last_timer_c = 0;
static uint16_t last_timer_w = 0;

const PhysicsConfig move(MOUSEKEY_CURSOR_FORCE, MOUSEKEY_CURSOR_MASS, MOUSEKEY_CURSOR_FRICTION_MUL_DT_GRAVITY_MASS, MOUSEKEY_DT);
const PhysicsConfig wheel(MOUSEKEY_WHEEL_FORCE, MOUSEKEY_WHEEL_MASS, MOUSEKEY_WHEEL_FRICTION_MUL_DT_GRAVITY_MASS, MOUSEKEY_DT);

PhysicsState move_state(move);
PhysicsState wheel_state(wheel);

void mousekey_task_cursor() {
    mouse_report.x = 0;
    mouse_report.y = 0;

    if (timer_elapsed(last_timer_c) < interval) return;

    move_state.advance();
    mouse_report.x = FPN_TO_INT(move_state.getPosition().x);
    mouse_report.y = FPN_TO_INT(move_state.getPosition().y);
}

void mousekey_task_wheel() {
    mouse_report.h = 0;
    mouse_report.v = 0;

    if (timer_elapsed(last_timer_w) < interval_wheel) return;

    mouse_report.h = FPN_TO_INT(wheel_state.accel.x);
    mouse_report.v = FPN_TO_INT(wheel_state.accel.y);
}

int count=0;

void pointing_device_task(void) {
    mousekey_task_cursor();
    mousekey_task_wheel();

    mousekey_send();
}

void mousekey_on(uint8_t code) {
  if      (code == MS_UP)       move_state.accel.y = -move.force;
  else if (code == MS_DOWN)     move_state.accel.y = move.force;
  else if (code == MS_LEFT)     move_state.accel.x = -move.force;
  else if (code == MS_RGHT)    move_state.accel.x = move.force;
  else if (code == MS_WHLU) wheel_state.accel.y = wheel.force;
  else if (code == MS_WHLD) wheel_state.accel.y = -wheel.force;
  else if (code == MS_WHLL) wheel_state.accel.x = wheel.force;
  else if (code == MS_WHLR) wheel_state.accel.x = -wheel.force;
  else if (code == MS_BTN1)     mouse_report.buttons |= MOUSE_BTN1;
  else if (code == MS_BTN2)     mouse_report.buttons |= MOUSE_BTN2;
  else if (code == MS_BTN3)     mouse_report.buttons |= MOUSE_BTN3;
  else if (code == MS_BTN4)     mouse_report.buttons |= MOUSE_BTN4;
  else if (code == MS_BTN5)     mouse_report.buttons |= MOUSE_BTN5;
}

void mousekey_off(uint8_t code) {
  if      (code == MS_UP       && move_state.accel.y < 0) move_state.accel.y = 0;
  else if (code == MS_DOWN     && move_state.accel.y > 0) move_state.accel.y = 0;
  else if (code == MS_LEFT     && move_state.accel.x < 0) move_state.accel.x = 0;
  else if (code == MS_RGHT    && move_state.accel.x > 0) move_state.accel.x = 0;
  else if (code == MS_WHLU && wheel_state.accel.y > 0) wheel_state.accel.y = 0;
  else if (code == MS_WHLD && wheel_state.accel.y < 0) wheel_state.accel.y = 0;
  else if (code == MS_WHLL && wheel_state.accel.x < 0) wheel_state.accel.x = 0;
  else if (code == MS_WHLR && wheel_state.accel.x > 0) wheel_state.accel.x = 0;
  else if (code == MS_BTN1) mouse_report.buttons &= ~MOUSE_BTN1;
  else if (code == MS_BTN2) mouse_report.buttons &= ~MOUSE_BTN2;
  else if (code == MS_BTN3) mouse_report.buttons &= ~MOUSE_BTN3;
  else if (code == MS_BTN4) mouse_report.buttons &= ~MOUSE_BTN4;
  else if (code == MS_BTN5) mouse_report.buttons &= ~MOUSE_BTN5;
}

static void mousekey_debug(void) {
    if (!debug_mouse) return;
    print("mousekey [btn|x y v h](rep/acl): [");
    print_hex8(mouse_report.buttons);
    print("|");
    print_decs(mouse_report.x);
    print(" ");
    print_decs(mouse_report.y);
    print(" ");
    print_decs(mouse_report.v);
    print(" ");
    print_decs(mouse_report.h);
    print("](");
    print_dec(mousekey_repeat);
    print("/");
    print_dec(mousekey_accel);
    print(")\n");
}

void mousekey_send(void) {
  pointing_device_set_report(mouse_report);
  pointing_device_send();
//  mousekey_debug();
//  host_mouse_send(&mouse_report);
  const uint16_t last_timer = timer_read();
  if (mouse_report.x || mouse_report.y) last_timer_c = last_timer;
  if (mouse_report.v || mouse_report.h) last_timer_w = last_timer;
}

void mousekey_clear(void) {
  mouse_report = (report_mouse_t){};
}
