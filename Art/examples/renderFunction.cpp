#include "../include/Art/Art.h"

#include <string>
#include <iostream>

int main()
{

    std::string expression;

    int16_t height = 512;
    int16_t width = 512;
    int64_t horizontalStretching = 8;

    std::cout << "image height > ";
    std::cin >> height;
    std::cin.ignore();

    std::cout << "image width > ";
    std::cin >> width;
    std::cin.ignore();

    std::cout << "horizontal Stretching (default is 8, none is 1, the higher the number, the more stretched the output will be) > ";
    std::cin >> horizontalStretching;
    std::cin.ignore();

    //Create image object
    art::Image<art::Vec3<uint8_t>> image(height, width);

    while (true)
    {
        std::cout << "\nWrite 'exit' to close or 'clear' to clear image" << std::endl;
        std::cout << "Expression > ";

        getline(std::cin, expression);
        if (expression == "clear")
            image.clear();

        else if (expression == "exit")
            break;

        else
        {
            std::cout << "Calculating and rendering image..." << std::endl;
            image.drawFunction(expression, BRANCO, horizontalStretching);
            std::cout << "Rendered successfully..." << std::endl;
        }

        image.writeImagePPM("../images_output/renderFunctionOutput.ppm");
        image.writeImageBMP("../images_output/renderFunctionOutput.bmp");
        std::cout << "Image saved successfully..." << std::endl;
    }

    return 0;
}