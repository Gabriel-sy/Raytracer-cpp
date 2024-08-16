#ifndef RAY_H
#define RAY_H

#include "vec3.h"

//Um raio tem uma origem e uma direção, origem é um point3(que é um vec3) e um vec3 puro.
class ray {
public:
    ray() {}

    ray(const point3& origin, const vec3& direction) : orig(origin), dir(direction) {}

    //Retornam a origem e a direção, não retornam o objeto em si, é só pra bizoiar.
    const point3& origin() const { return orig; }
    const vec3& direction() const { return dir; }

    //Função para uma posição em um raio.
    point3 at(double t) const {
        return orig + t * dir;
    }

private:
    point3 orig;
    vec3 dir;
};

#endif