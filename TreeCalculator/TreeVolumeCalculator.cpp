#include "TreeVolumeCalculator.h"
#include <cmath>

// Вычисление кубатуры
double TreeVolumeCalculator::calculateVolume(double diameterCm, double heightM, double formFactor) {
    double radiusM = (diameterCm / 100.0) / 2.0;
    double area = M_PI * radiusM * radiusM;
    return area * heightM * formFactor;
}
