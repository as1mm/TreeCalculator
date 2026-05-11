#ifndef TREEVOLUMECALCULATOR_H
#define TREEVOLUMECALCULATOR_H

class TreeVolumeCalculator {
public:
    // Статический метод: диаметр (см), высота (м), видовое число = объём (м³)
    static double calculateVolume(double diameterCm, double heightM, double formFactor);
};

#endif
