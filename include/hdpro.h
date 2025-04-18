#pragma once
#include <vector>
#include <functional>
#include <random>
#include <algorithm>

#ifdef HDPRO_EXPORTS
    #define HDPRO_API __declspec(dllexport)
#else
    #define HDPRO_API __declspec(dllimport)
#endif

struct float3 {
    float x, y, z;
};

template <typename T>
class HDPRO_API HDPRO {
protected:
    std::vector<float> U;
    std::vector<float> V;
    float result;
    
    int lambda = 100;
    int delta;

    std::mt19937 random_machine;

    const float inf = std::numeric_limits<float>().max();

public:
    std::vector<T> source;
    std::vector<T> target;
    std::function<float(T,T)> distanceFunc;

protected:
    void EBHD(std::vector<T> &A, std::vector<T> &B, std::vector<float> &V, float &cmax);
    void TMDC(std::vector<T> &A, std::vector<T> &B, std::vector<float> &U, std::vector<float> &V, float &cmax);
    std::vector<T> rullingout(std::vector<T> &S, std::vector<float> &W, float cmax);

public:
    HDPRO(): random_machine(std::random_device{}()){}
    HDPRO(std::vector<T> _s, std::vector<T> _t, std::function<float(T,T)> _df, std::mt19937 _rm = std::mt19937(std::random_device{}())) : source(_s), target(_t), distanceFunc(_df), random_machine(_rm) {}

    float compute();
};