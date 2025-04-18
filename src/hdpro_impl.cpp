#include "hdpro.h"

template <typename T>
std::vector<T> HDPRO<T>::rullingout(std::vector<T> &S, std::vector<float> &W, float cmax){
    std::vector<T> res;

    for(int i = 0; i<S.size(); i++){
        if(W[i] > cmax)
            res.push_back(S[i]);
    }

    return res;
}

template <typename T>
void HDPRO<T>::EBHD(std::vector<T> &A, std::vector<T> &B, std::vector<float> &V, float &cmax){
    int isp = B.size() / 2;
	for (int x = 0; x < A.size(); x++) {
		float cmin = inf, dist1 = inf, dist2 = inf;

		int y = isp - 1; int z = isp;
		while (y > 0 || z < B.size()) {
			if (y >= 0) {
				dist1 = distanceFunc(A[x], B[y]);
				if (dist1 < V[y]) {
					V[y] = dist1;
				}
			}
			if (z < B.size()) {
				dist2 = distanceFunc(A[x], B[z]);
				if (dist2 < V[z]) {
					V[z] = dist2;
				}
			}
			
			cmin = fminf(fminf(dist1,dist2), cmin);
			if (cmin <= cmax)
			{
				isp = dist1 < dist2 ? y : z;
				break;
			}
			y--;
			z++;
		}
		if (cmin > cmax)
			cmax = cmin;
	}
}

template <typename T>
void HDPRO<T>::TMDC(std::vector<T> &A, std::vector<T> &B, std::vector<float> &U, std::vector<float> &V, float &cmax){
    delta = B.size() / lambda;
	std::uniform_int_distribution<> dis(0, delta - 1);
	int osp = dis(random_machine);
	int isp = A.size() / 2;

	for (int x = osp; x < B.size(); x += delta) {
		float cmin = inf;
		float dist1 = inf;
		float dist2 = inf;

		int y = isp - 1; int z = isp;
		while (y > 0 || z < A.size()) {
			if (y >= 0) {
				dist1 = distanceFunc(B[x],A[y]);
				if (dist1 < U[y]) {
					U[y] = dist1;
				}
			}
			if (z < A.size()) {
				dist2 = distanceFunc(B[x],A[z]);
				if (dist2 < U[z]) {
					U[z] = dist2;
				}
			}
			float dist = fminf(dist1, dist2);
			
			if (dist < V[x])
				V[x] = dist;

			cmin = fminf(dist, cmin);
			if (cmin <= cmax)
			{
				isp = dist1 < dist2 ? y : z;
				break;
			}
			y--;
			z++;
		}
		if (cmin > cmax)
			cmax = cmin;
	}
}

template <typename T>
float HDPRO<T>::compute(){
    result = 0;
    U = std::vector<float>(source.size(), inf);
    V = std::vector<float>(target.size(), inf);
    TMDC(source, target, U, V, result);
    std::vector<T> Sro = rullingout(source, U, result);
    EBHD(Sro, target, V, result);

    return result;
}

template class HDPRO<float3>;