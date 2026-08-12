#ifndef ARDUINO_H
#define ARDUINO_H

#include <iostream>
#include <cstdlib>
#include <stdint.h>

// Émulation minimale de la classe Serial Arduino pour PC
class HardwareSerial {
public:
    void begin(long) {}
    operator bool() { return true; }
    void print(const char* s) { std::cout << s; }
    void print(int n) { std::cout << n; }
    void print(float f, int) { std::cout << f; }
    void println(const char* s) { std::cout << s << std::endl; }
    void println(int n) { std::cout << n << std::endl; }
    void println(float f, int) { std::cout << f << std::endl; }
    void println() { std::cout << std::endl; }
    void flush() {}
};

extern HardwareSerial Serial;
inline unsigned long millis() { return 1000; }
inline void delay(unsigned long ms) { /* Pas de vrai délai sur PC pour aller vite */ }
#define F(s) s
#define RTC_DATA_ATTR
#define pinMode(a, b)
#define digitalWrite(a, b)
#define HIGH 1
#define LOW 0
#define OUTPUT 1

#endif