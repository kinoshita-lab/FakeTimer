/**
 * @file FakeTimer.h
 * @brief Header Only Library for Arduino Timer-like Interrupt Simulation
 *
 * @author Kazuki Saita <saita@kinoshita-lab.com>
 *
 * Copyright (c) 2022 Kinoshita Lab. All rights reserved.
 *
 */
#pragma once
#ifndef FAKETIMER_H
#define FAKETIMER_H

#include <Arduino.h>
#include <functional>
#include <stdint.h>

class FakeTimer {
public:
  FakeTimer() {}
  void setCallback(std::function<void()> f) { callback = f; }
  void update() {
    if (max_count_ == 0) {
      return;
    }
    const auto now = millis();
    const auto inc = now - prev_millis_;

    count_ += inc;
    prev_millis_ = now;

    if (count_ < max_count_) {
      return;
    }

    count_ = 0;

    if (!callback) {
      return;
    }

    callback();
  }

  void setIntervalMsec(const size_t msec) { max_count_ = msec; }

  void start() { count_ = 0; }

protected:
  size_t count_ = 0;
  size_t max_count_ = 0;
  uint32_t prev_millis_ = 0;

  std::function<void()> callback = nullptr;

private:
  FakeTimer(const FakeTimer &) {}
};

#endif // FAKETIMER_H
