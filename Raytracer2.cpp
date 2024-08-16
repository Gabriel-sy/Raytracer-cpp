#include "color.h"
#include "ray.h"
#include "vec3.h"

#include <iostream>

//Função para saber se o raio bateu na esfera, é bem complicada, mas basicamente, para saber se um ponto está dentro de uma esfera é:
//x^2+y^2+z^2=r^2, se essa equação for verdade, o ponto está na superficie (porque sim, se as coordenadas sao iguais ao raio, eles estao
//na distancia certinha, acho q é isso), se for maior, o ponto ta fora, se for menor, o ponto ta dentro, daí, se a esfera não 
// estiver no centro da imagem(0, 0, 0), precisamos de outra equação, (Cx - x)^2+(Cy - y)^2+(Cz - z)^2 = r^2,
//essa vai ser a equação, para posicionar a esfera em um lugar arbitrário(eu acho), C(x,y,z) sendo o ponto do centro da esfera.
//Adaptando a equação para que (x,y,z) sejam o raio, fica: (C - P(t)).(C - P(t)) = r^2, para qualquer ponto t, em que essa equação seja
//Verdadeira, o raio intercepta a esfera. Multiplicando e simplificando essa bosta, fica: t^2d⋅d−2td⋅(C−Q)+(C−Q)⋅(C−Q)−r^2=0,
//t é o q a gente quer descobrir, d é a direção(do raio), Q é a origem(do raio), C é o ponto do centro da esfera, bom, resolvendo para t:
// a = d.d, b = 2d.(C-Q), c = (C−Q)⋅(C−Q)−r^2, essa bosta desse código pega o a, b e c com base em um raio r, e um centro(?),
//essa bomba retorna o discriminant(delta da eq), se for negativo(sem solução) o raio não bate na esfera, se for positivo(mais de uma
//solução), o raio toca na esfera em dois pontos, se for zero(uma solução), o raio bate na esfera uma vez, é isso. 
// MUITO SIMPLES!(misericordia)
//center é o centro da esfera
bool hit_sphere(const point3& center, double radius, const ray& r) {
    //Vetor que vai da origem do raio, até o centro da esfera.
    vec3 oc = center - r.origin();
    auto a = dot(r.direction(), r.direction());
    auto b = -2.0 * dot(r.direction(), oc);
    auto c = dot(oc, oc) - radius * radius;
    auto discriminant = b * b - 4 * a * c;
    return (discriminant >= 0);
}

//Quando é com esse &, não pode modificar o objeto que recebe.
//A função pega o raio de cada pixel (sim, cada pixel tem um raio) e faz coisas com ele.
color ray_color(const ray& r) {
    //Se o raio bater na esfera, no z = -1(É -1, porque, como a gente viu, a câmera está em (0,0,0) e o espaço que a gente criou virtual,
    //Z é na frente da câmera, mas para valores negativos) y é para cima e x é para a esquerda, relativos a câmera.
    if (hit_sphere(point3(0, 0, -1), 0.8, r))
        return color(1, 0, 0);
    //Gradiente de entre azul e branco
    vec3 unit_direction = unit_vector(r.direction());
    auto a = 0.5 * (unit_direction.y() + 1.0);
    return (1.0 - a) * color(1.0, 1.0, 1.0) + a * color(0.5, 0.7, 1.0);
}

int main()
{
    auto aspect_ratio = 16.0 / 9.0;
    int image_width = 400;

    // Calculate the image height, and ensure that it's at least 1.
    int image_height = int(image_width / aspect_ratio);
    image_height = (image_height < 1) ? 1 : image_height;

    // Camera

    auto focal_length = 1.0;
    auto viewport_height = 2.0;
    auto viewport_width = viewport_height * (double(image_width) / image_height);
    auto camera_center = point3(0, 0, 0);

    // Tamanho do viewport horizontal e vertical
    auto viewport_u = vec3(viewport_width, 0, 0);
    auto viewport_v = vec3(0, -viewport_height, 0);

    // Distância horizontal dos pixels
    auto pixel_delta_u = viewport_u / image_width;
    // Distância vertical dos pixels
    auto pixel_delta_v = viewport_v / image_height;

    // Calculate the location of the upper left pixel.
    auto viewport_upper_left = camera_center
        - vec3(0, 0, focal_length) - viewport_u / 2 - viewport_v / 2;
    //Localização do pixel inicial(0,0)
    auto pixel00_loc = viewport_upper_left + 0.5 * (pixel_delta_u + pixel_delta_v);


    std::cout << "P3\n" << image_width << ' ' << image_height << "\n255\n";

    //Um raio para cada pixel.
    for (int j = 0; j < image_height; j++)
    {
        std::clog << "\rScanlines remaining: " << (image_height - j) << ' ' << std::flush;
        for (int i = 0; i < image_width; i++)
        {
            //Uau, para cada pixel, pega o centro desse pixel e cria um vetor para a direção do raio desse pixel especifico
            vec3 pixel_center = pixel00_loc + (i * pixel_delta_u) + (j * pixel_delta_v);
            vec3 ray_direction = pixel_center - camera_center;
            //Cria um raio do centro da camera(origem) até a direção do raio(direção)
            ray r(camera_center, ray_direction);

            //Pega a cor do pixel
            color pixel_color = ray_color(r);
            //Criando um objeto color, como color é um vec3, estamos usando o construtor para fazer um vetor (x,y,z) com (red, green, blue)
            //auto pixel_color = color(double(i) / (image_width - 1), double(j) / (image_height - 1), 0);
            write_color(std::cout, pixel_color);
        }

    }

    std::clog << "\rDone.                 \n";

}