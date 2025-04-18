# hausdorff_distance_point_rulling_out

Simple implementation of  Ryu, Jegoon, and Sei-ichiro Kamata, ["An efficient computational algorithm for Hausdorff distance based on points-ruling-out and systematic random sampling"](https://www.sciencedirect.com/science/article/pii/S0031320321000443), Pattern Recognition 114 (2021):107857  

## Usage
See with demo.cpp files  
```
    std::vector<float3> A = genRand(size, {-1, 1}, rm);
    std::vector<float3> B = genRand(size, {0.5, 2.5}, rm);

    auto euclidean = [](float3 x, float3 y){
        float3 arrow{x.x-y.x, x.y-y.y, x.z - y.z};
        return std::sqrtf(arrow.x*arrow.x+arrow.y*arrow.y+arrow.z*arrow.z);
    };
    HDPRO<float3> hdpro(A, B, euclidean, rm);

    std::cout << hdpro.compute() << std::endl;
```
