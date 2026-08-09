#pragma once

struct Button {
  int x, y, w, h;
};

constexpr Button BTN_OFF   = {   0, 80, 58, 48 };
constexpr Button BTN_HEAT  = {  58, 80, 58, 48 };
constexpr Button BTN_COOL  = { 116, 80, 58, 48 };
constexpr Button BTN_FAN   = { 174, 80, 58, 48 };
constexpr Button BTN_PLUS  = { 232,  0, 64, 64 };
constexpr Button BTN_MINUS = { 232, 64, 64, 64 };
