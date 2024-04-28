#pragma once
#include "math.h"
#include "define.h"

float easeOutSine(float x) {

    return sin((x * PI) / 2);
}

float easeInExpo(float x) {
    return x == 1 ? 1 : 1 - pow(2, -10 * x);
}