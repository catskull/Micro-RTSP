#pragma once

#ifndef ARDUINO_ARCH_ESP32
#define INCLUDE_SIMDATA
#endif

#ifdef INCLUDE_SIMDATA
extern unsigned const char capture_jpg[];
extern unsigned const char test_jpg[];
extern unsigned int test_jpg_len, capture_jpg_len;
#endif
