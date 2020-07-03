#ifndef POWER_HPP
#define POWER_HPP

// Функция возведения в степень с оптимизацией для целочисленных степеней известных на этапе компиляции.

namespace metamath {

template<int64_t N, class Type> constexpr std::enable_if_t<(N > 0 && N % 2 == 0), Type> power(Type);
template<int64_t N, class Type> constexpr std::enable_if_t<(N > 0 && N % 2 == 1), Type> power(Type);

template<int64_t N, class Type>
constexpr std::enable_if_t<(N < 0), Type> power(Type x) {
    return 1 / power<-N>(x);
}

template<int64_t N, class Type>
constexpr std::enable_if_t<(N == 0), Type> power(Type) {
    return 1;
}

template<int64_t N, class Type>
constexpr std::enable_if_t<(N > 0 && N % 2 == 0), Type> power(Type x) {
    Type temp = power<N / 2>(x);
    return temp * temp;
}

template<int64_t N, class Type>
constexpr std::enable_if_t<(N > 0 && N % 2 == 1), Type> power(Type x) {
    return power<N - 1>(x) * x;
}

};

#endif