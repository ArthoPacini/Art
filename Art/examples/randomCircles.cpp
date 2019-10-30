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
    std::uniform_int_distribution<std::int16_t> random_distribution_radius(0, 256);

    //Cria uma imagem rgb, com alcance de 0 <-> 255
    art::Image<art::Vec3<uint8_t>> imagem(largura, altura, corBranca);

    {
        art::Benchmark benchmark("demorou: "); //Benchmark the code
        for (std::uint32_t i = 0; i < 1024; ++i)
        {
            const std::int16_t randomPositionX = random_distribution_position(mt);
            const std::int16_t randomPositionY = random_distribution_position(mt);
            const std::uint16_t randomRadius = random_distribution_radius(mt);
            imagem.drawCircle(randomPositionX, randomPositionY, randomRadius, corPreto);
        }
    }

    imagem.writeImagePPM("../images_output/randomCircles.ppm");
    imagem.writeImageBMP("../images_output/randomCircles.bmp");
    return 0;
}
