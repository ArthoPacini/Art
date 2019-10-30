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

    //Cria uma imagem rgb, com alcance de 0 <-> 255
    art::Image<art::Vec3<uint8_t>> imagem(largura, altura, corBranca);

    //imagem.drawTriangle(5, 100, 200, 300, 400, 500, corPreto);
    {
        art::Benchmark benchmark("demorou: "); //Benchmark the code
        for (std::uint32_t i = 0; i < 512; ++i)
        {
            const std::int16_t randomPosition1X = random_distribution_position(mt);
            const std::int16_t randomPosition1Y = random_distribution_position(mt);
            const std::int16_t randomPosition2X = random_distribution_position(mt);
            const std::int16_t randomPosition2Y = random_distribution_position(mt);

            imagem.drawRectangle(randomPosition1X, randomPosition1Y, randomPosition2X, randomPosition2Y, corPreto);
        }
    }

    imagem.writeImagePPM("../images_output/randomRectangles.ppm");
    imagem.writeImageBMP("../images_output/randomRectangles.bmp");
    return 0;
}
