#include "../include/Art/Art.h"

int main()
{
    //Criar o objeto imagem
    const int16_t altura = 8;
    const int16_t largura = 8;

    //Cria uma imagem rgb, com alcance de 0 <-> 255
    art::Image<art::Vec3<uint8_t>> imagem(largura, altura, art::Vec3<uint8_t>(0, 0, 0));

    //art::Buffer2D<art::Vec3<uint8_t>> frameBuffer = imagem.getFrameBuffer(); // = art::Vec3<uint8_t>(0);
    imagem(1, 1) = art::Vec3<uint8_t>(255);
    imagem(1, 2) = art::Vec3<uint8_t>(255);
    imagem(2, 1) = art::Vec3<uint8_t>(255);
    imagem(2, 2) = art::Vec3<uint8_t>(255);

    imagem(5, 1) = art::Vec3<uint8_t>(127);
    imagem(5, 2) = art::Vec3<uint8_t>(127);
    imagem(6, 1) = art::Vec3<uint8_t>(127);
    imagem(6, 2) = art::Vec3<uint8_t>(127);

    imagem(1, 5) = art::Vec3<uint8_t>(255, 0, 0);
    imagem(2, 5) = art::Vec3<uint8_t>(0, 255, 0);
    imagem(3, 5) = art::Vec3<uint8_t>(0, 0, 255);
    imagem(4, 5) = art::Vec3<uint8_t>(30, 60, 90);

    imagem.writeImagePPM("../images_output/randomDude.ppm");
    imagem.writeImageBMP("../images_output/randomDude.bmp");
    return 0;
}
