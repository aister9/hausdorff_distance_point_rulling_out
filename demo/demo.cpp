#include "hdpro.h"
#include <iostream>
#include <random>

struct float2{
    float x, y;
};

std::vector<float3> genRand(int size, float2 range, std::mt19937 &rm){
    std::vector<float3> lval;
    std::uniform_real_distribution<float> dis(range.x, range.y);
    for(int i = 0; i<size; i++){
        float3 data = {dis(rm), dis(rm),dis(rm)};
        lval.push_back(data);
    }
    return lval;
}

int main(){
    int seed = 100000001;
    std::mt19937 rm(seed);
    
    int size = 100000;

    std::vector<float3> A = genRand(size, {-1, 1}, rm);
    std::vector<float3> B = genRand(size, {0.5, 2.5}, rm);

    auto euclidean = [](float3 x, float3 y){
        float3 arrow{x.x-y.x, x.y-y.y, x.z - y.z};
        return std::sqrtf(arrow.x*arrow.x+arrow.y*arrow.y+arrow.z*arrow.z);
    };
    HDPRO<float3> hdpro(A, B, euclidean, rm);

    std::cout << hdpro.compute() << std::endl;
}