#include <stdio.h>

#define PI 3.14

// Функция расчета полного реактивного сопротивления
// inductance - индуктивность участка цепи [Гн]
// capacitance - емкость участка цепи [Ф]
// frequency - частота тока [Гц]
double * calc_reactance(const double *const inductance,
                        const double *const capacitance,
                        const double *const frequency) {
    static double result;
    result = 0;

    // Проверка указателей
    if (inductance == NULL || capacitance == NULL || frequency == NULL) {
        return &result;
    }

    // Проверка допустимых значений
    if (*frequency <= 0 || *capacitance <= 0 || *inductance < 0) {
        return &result;
    }

    // Расчеты
    double angular_frequency = 2 * PI * (*frequency);
    double xl = angular_frequency * (*inductance);
    double xc = 1 / ( angular_frequency * (*capacitance) );
    result = xl - xc;

    return &result;
}



int main(void) {
    // Начальная инициализация
    double ind = 0;
    double cap = 0;
    double freq = 0;
    double *react = NULL;

    // Ввод
    int scanf_result = scanf("%lf%lf%lf", &ind, &cap, &freq);
    if (scanf_result != 3) {
        // Ошибка
        return 1;
    }

    // Расчет
    react = calc_reactance(&ind, &cap, &freq);

    // Вывод
    printf("%.2lf", *react);
    return 0;
}
