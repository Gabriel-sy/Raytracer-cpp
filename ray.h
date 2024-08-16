#ifndef RAY_H
#define RAY_H

#include "vec3.h"

//Um raio tem uma origem e uma dire��o, origem � um point3(que � um vec3) e um vec3 puro.
class ray {
public:
    ray() {}

    ray(const point3& origin, const vec3& direction) : orig(origin), dir(direction) {}

    //Retornam a origem e a dire��o, n�o retornam o objeto em si, � s� pra bizoiar.
    const point3& origin() const { return orig; }
    const vec3& direction() const { return dir; }

    //Fun��o para uma posi��o em um raio.
    point3 at(double t) const {
        return orig + t * dir;
    }

private:
    point3 orig;
    vec3 dir;
};

#endif