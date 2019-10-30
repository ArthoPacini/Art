#include "../include/Art/Art.h"

#include <random>

int main()
{
    //Criar o objeto imagem
    const int16_t altura = 1024;
    const int16_t largura = 1024;
    const art::Vec3<uint8_t> corPreto = art::Vec3<uint8_t>(0);
    const art::Vec3<uint8_t> corBranca = art::Vec3<uint8_t>(255);

    std::random_device rd;
    std::mt19937 mt(rd());
    std::uniform_int_distribution<std::int16_t> random_distribution_position(-512, 512);
    std::uniform_int_distribution<std::uint8_t> random_distribution_vertices(0, 32);

    //Cria uma imagem rgb, com alcance de 0 <-> 255
    art::Image<art::Vec3<uint8_t>> imagem(largura, altura, corBranca);

    //imagem.drawTriangle(5, 100, 200, 300, 400, 500, corPreto);
    std::vector<art::Vec2<std::int64_t>> poligon;
    {
        art::Benchmark benchmark("demorou: "); //Benchmark the code
        for (std::uint32_t i = 0; i < 32; ++i)
        {
            const std::uint8_t polygonVerticesCount = random_distribution_vertices(mt);
            poligon.clear();
            poligon.reserve(polygonVerticesCount);
            for (std::uint8_t i = 0; i < polygonVerticesCount; ++i)
                poligon.emplace_back(art::Vec2<std::int64_t>(random_distribution_position(mt), random_distribution_position(mt)));

            imagem.drawPolygon(poligon, corPreto);
        }
    }

    imagem.writeImagePPM("../images_output/randomPolygons.ppm");
    imagem.writeImageBMP("../images_output/randomPolygons.bmp");
    return 0;
}
