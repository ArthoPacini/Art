#include <iostream>
#include <string>
#include <vector>
#include <fstream>
#include <chrono>
#include <thread>
#include <cmath>
#include <random>

//Inclui o <filesystem>
#ifdef USANDO_VERSAO_MODERNA

#include <filesystem>

#ifdef _WIN32 //MSVC++ utiliza experimental
namespace fs = std::experimental::filesystem;
#else
namespace fs = std::filesystem;
#endif
#endif

#define USAR_BENCHMARK

#include "../include/Art/Art.h"
/*
#include "Vec3.h"
#include "Vec2.h"
#include "Buffer2D.h"
#include "Image.h"
#include "Colors.h" //define colors
#include "Function.h"
*/

int main()
{
#ifndef USANDO_VERSAO_MODERNA
    //std::cout << "Compilado SEM suporte a biblioteca <filesystem>" << std::endl;
#else
    //std::cout << "Compilado COM suporte a biblioteca <filesystem>" << std::endl;
#endif

#ifndef USAR_BENCHMARK
    //std::cout << "Compilado SEM benchmark" << std::endl;
#else
    //std::cout << "Compilado COM benchmark" << std::endl;
#endif
    //Criar o objeto imagem
    const int16_t altura = 4096;
    const int16_t largura = 4096;

    //Cria uma imagem rgb, com alcance de 0 <-> 255
    art::Image<art::Vec3<uint8_t>> imagem(largura, altura, art::Vec3<uint8_t>(86, 182, 96));

#ifdef USAR_BENCHMARK
    //Este objeto vai ser usado para medir o tempo de desenho
    auto startBenchmark = std::chrono::steady_clock::now();
#endif

    /*              LINHA RETA              */

    //Para desenhar uma linha eh muito simples, basta chamar a funcao drawLine() do objeto imagem
    //Passando as coordenadas de origem x1,y1 e as de destino x2,y2
    //Exemplo: desenhando uma linha do ponto {-100,-100} ate {100,100}
    imagem.drawLine(-100, -100, 100, 100);
    //Esta linha fora desenhada com a cor branca, eh possivel especificar uma cor

    //Por exemplo, desenhando uma linha com cor vermelha:
    imagem.drawLine(100, -100, -100, 100, art::Vec3<uint8_t>(255, 0, 0));

    //Tambem pode ser desenhado com as cores pre definidas no header Colors.h, como: VERMELHO, VERDE, AZUL, AMARELO, MAGENTA etc...
    imagem.drawLine(0, 100, 0, -100, AMARELO);

    //As coordenadas tambem podem ser passadas por objetos Vec2<T>, por exemplo:
    art::Vec2<int64_t> exCoordenada1Line(-100, 100);
    art::Vec2<int64_t> exCoordenada2Line(100, 100);

    imagem.drawLine(exCoordenada1Line, exCoordenada2Line);

    //Esta linha fora desenhada com a cor branca, eh possivel especificar uma cor, por exemplo:
    art::Vec2<int64_t> exCoordenada3Line(-500, 500);
    art::Vec2<int64_t> exCoordenada4Line(500, 500);
    imagem.drawLine(exCoordenada3Line, exCoordenada4Line, art::Vec3<uint8_t>(255, 0, 0));

    //Ou utilizar uma cor pre definida no header Colors.h
    art::Vec2<int64_t> exCoordenada5Line(-600, 600);
    art::Vec2<int64_t> exCoordenada6Line(600, 600);
    imagem.drawLine(exCoordenada5Line, exCoordenada6Line, AMARELO);

    /*              CIRCULO             */

    //Para desenhar um circulo basta chamar a funcao drawCircle() do objeto imagem
    //Passando as coordenadas do ponto central x1,y1 e seu raio r
    imagem.drawCircle(0, 0, 250);

    //Este circulo fora desenhado com a cor branca, eh possivel especificar uma cor, por exemplo:
    imagem.drawCircle(0, 0, 500, art::Vec3<uint8_t>(255, 255, 0));

    //Ou utilizar uma cor pre definida no header Colors.h
    imagem.drawCircle(0, 0, 750, ROSA);

    //O circulo tambem pode ser desenhado usando um objeto Vec2<T>, por exemplo:
    art::Vec2<int64_t> exCoordenada1Circle(0, 0);
    imagem.drawCircle(exCoordenada1Circle, 300);

    //Este circulo fora desenhado com a cor branca, eh possivel especificar uma cor, por exemplo:
    art::Vec2<int64_t> exCoordenada2Circle(-500, -500);
    imagem.drawCircle(exCoordenada2Circle, 150, art::Vec3<uint8_t>(255, 0, 0));

    //Ou utilizar uma cor pre definida no header Colors.h
    art::Vec2<int64_t> exCoordenada3Circle(-750, -750);
    imagem.drawCircle(exCoordenada3Circle, 150, ROSA);

    /*              TRIANGULO               */

    //Para desenhar um triangulo, basta chamar a funcao DrawTriangle() do objeto imagem
    //Passando as coordenadas dos tres vertices do triangulo, x1 y1, x2 y2, x3 y3
    imagem.drawTriangle(-150, -50, 150, -50, 0, 150);

    //Este triangulo fora desenhado com a cor branca, eh possivel especificar uma cor, por exemplo:
    imagem.drawTriangle(-250, -100, 250, -100, 0, 250, art::Vec3<uint8_t>(255, 0, 0));

    //Ou utilizar uma cor pre definida no header Colors.h
    imagem.drawTriangle(-300, -150, 300, -150, 0, 300, LARANJA);

    //O triangulo tambem pode ser desenhado usando objetos Vec2<T>, por exemplo:
    art::Vec2<int64_t> exCoordenada1Triangulo(-200, -100);
    art::Vec2<int64_t> exCoordenada2Triangulo(200, -100);
    art::Vec2<int64_t> exCoordenada3Triangulo(0, 200);
    imagem.drawTriangle(exCoordenada1Triangulo, exCoordenada2Triangulo, exCoordenada3Triangulo);

    //Este triangulo fora desenhado com a cor branca, eh possivel especificar uma cor, por exemplo:
    art::Vec2<int64_t> exCoordenada4Triangulo(-300, -200);
    art::Vec2<int64_t> exCoordenada5Triangulo(300, -200);
    art::Vec2<int64_t> exCoordenada6Triangulo(0, 300);
    imagem.drawTriangle(exCoordenada4Triangulo, exCoordenada5Triangulo, exCoordenada6Triangulo, art::Vec3<uint8_t>(0, 0, 255));

    //Ou utilizar uma cor pre definida no header Colors.h
    art::Vec2<int64_t> exCoordenada7Triangulo(-400, -300);
    art::Vec2<int64_t> exCoordenada8Triangulo(400, -300);
    art::Vec2<int64_t> exCoordenada9Triangulo(0, 400);
    imagem.drawTriangle(exCoordenada7Triangulo, exCoordenada8Triangulo, exCoordenada9Triangulo, VERDE);

    /*              RETANGULO               */

    //Para desenhar um retangulo, basta chamar a funcao drawRectangle() do objeto imagem
    //Passando as coordenadas dos dois vertices das extremidades do retangulo, x1 y1, x2 y2
    imagem.drawRectangle(-300, -300, 300, 300);

    //Este triangulo fora desenhado com a cor branca, eh possivel especificar uma cor, por exemplo:
    imagem.drawRectangle(-400, -400, 400, 400, art::Vec3<uint8_t>(0, 255, 0));

    //Ou utilizar uma cor pre definida no header Colors.h
    imagem.drawRectangle(-500, -500, 500, 500, AZUL);

    //O retangulo tambem pode ser desenhado usando objetos Vec2<T>, por exemplo:
    art::Vec2<int64_t> exCoordenada1Retangulo(-600, -600);
    art::Vec2<int64_t> exCoordenada2Retangulo(600, 600);
    imagem.drawRectangle(exCoordenada1Retangulo, exCoordenada2Retangulo);

    //Este retangulo fora desenhado com a cor branca, eh possivel especificar uma cor, por exemplo:
    art::Vec2<int64_t> exCoordenada3Retangulo(-700, -700);
    art::Vec2<int64_t> exCoordenada4Retangulo(700, 700);
    imagem.drawRectangle(exCoordenada3Retangulo, exCoordenada4Retangulo, art::Vec3<uint8_t>(255, 0, 0));

    //Ou utilizar uma cor pre definida no header Colors.h
    art::Vec2<int64_t> exCoordenada5Retangulo(-800, -800);
    art::Vec2<int64_t> exCoordenada6Retangulo(800, 800);
    imagem.drawRectangle(exCoordenada5Retangulo, exCoordenada6Retangulo, AZUL);

    /*              MULTI LINE               */

    //Para desenhar uma Multi Line, basta chamar a funcao drawMultiLine() do objeto imagem
    //Passando as coordenadas dos vertices da multi line

    //Eh possivel passar parametros ilimitados
    imagem.drawMultiLine(500, -500, 600, -400, 500, -400, 600, -300, 500, -300);

    //Esta multi line fora desenhada com a cor branca, eh possivel especificar uma cor, por exemplo:
    imagem.drawMultiLine(art::Vec3<uint8_t>(255, 0, 0), 50, -500, 150, -400, 50, -400, 150, -300, 50, -300);

    //Ou utilizar uma cor pre definida no header Colors.h
    imagem.drawMultiLine(ROSA, 700, -500, 600, -400, 700, -400, 600, -300, 700, -300);

    //A multi line tambem pode ser desenhada usando objetos Vec2<T>, por exemplo:
    imagem.drawMultiLine(art::Vec2<int64_t>(600, 1000), art::Vec2<int64_t>(650, 1100), art::Vec2<int64_t>(600, 1200));
    //Eh possivel passar parametros ilimitados

    //Esta multi line fora desenhado com a cor branca, eh possivel especificar uma cor, por exemplo:
    imagem.drawMultiLine(art::Vec3<uint8_t>(255, 0, 0), art::Vec2<int64_t>(650, 1000), art::Vec2<int64_t>(700, 1100), art::Vec2<int64_t>(650, 1200));

    //Ou utilizar uma cor pre definida no header Colors.h
    imagem.drawMultiLine(ROSA, art::Vec2<int64_t>(750, 1000), art::Vec2<int64_t>(800, 1100), art::Vec2<int64_t>(750, 1200));

    //A multi line tambem pode ser desenhada usando std::vectors de numeros contendo as respectivas coordenadas x,y exemplo:
    std::vector<int64_t> exCoordenadas1MultiLineNum = {500, 1000, 550, 1100, 500, 1200};
    imagem.drawMultiLine(exCoordenadas1MultiLineNum);

    //Esta multi line fora desenhado com a cor branca, eh possivel especificar uma cor, por exemplo:
    std::vector<int64_t> exCoordenadas2MultiLineNum = {400, 1000, 450, 1100, 400, 1200};
    imagem.drawMultiLine(exCoordenadas2MultiLineNum, AZUL);

    //A multi line tambem pode ser desenhada usando std::vectos de Vec2<T> contendo as respectivas coordenadas, exemplo:
    std::vector<art::Vec2<int64_t>> exCoordenadas3MultiLineNum = {art::Vec2<int64_t>(300, 1000), art::Vec2<int64_t>(350, 1100), art::Vec2<int64_t>(300, 1200)};
    imagem.drawMultiLine(exCoordenadas3MultiLineNum);

    //Esta multi line fora desenhado com a cor branca, eh possivel especificar uma cor, por exemplo:
    std::vector<art::Vec2<int64_t>> exCoordenadas4MultiLineNum = {art::Vec2<int64_t>(200, 1000), art::Vec2<int64_t>(250, 1100), art::Vec2<int64_t>(200, 1200)};
    imagem.drawMultiLine(exCoordenadas4MultiLineNum, VERMELHO);

    /*              POLYGON               */

    //Para desenhar um polygon, basta chamar a funcao drawPolygon() do objeto imagem
    //Passando as coordenadas dos vertices do polygon

    //Eh possivel passar parametros ilimitados
    imagem.drawPolygon(-1000, -200, -800, 0, -1000, 200, -1200, 0);

    //Este polygon fora desenhada com a cor branca, eh possivel especificar uma cor, por exemplo:
    imagem.drawPolygon(art::Vec3<uint8_t>(255, 0, 0), -1000, 0, -800, 200, -1000, 400, -1200, 200);

    //Ou utilizar uma cor pre definida no header Colors.h
    imagem.drawPolygon(ROSA, -1000, 200, -800, 400, -1000, 600, -1200, 400);

    //A multi line tambem pode ser desenhada usando objetos Vec2<T>, por exemplo:
    imagem.drawPolygon(art::Vec2<int64_t>(-1000, 400), art::Vec2<int64_t>(-800, 600), art::Vec2<int64_t>(-1000, 800), art::Vec2<int64_t>(-1200, 600));
    //Eh possivel passar parametros ilimitados

    //Este polygon fora desenhado com a cor branca, eh possivel especificar uma cor, por exemplo:
    imagem.drawPolygon(art::Vec3<uint8_t>(255, 0, 0), art::Vec2<int64_t>(-1000, 600), art::Vec2<int64_t>(-800, 800), art::Vec2<int64_t>(-1000, 1000), art::Vec2<int64_t>(-1200, 800));

    //Ou utilizar uma cor pre definida no header Colors.h
    imagem.drawPolygon(ROSA, art::Vec2<int64_t>(-1000, 800), art::Vec2<int64_t>(-800, 1000), art::Vec2<int64_t>(-1000, 1200), art::Vec2<int64_t>(-1200, 1000));

    //O polygon tambem pode ser desenhada usando std::vectors de numeros contendo as respectivas coordenadas x,y exemplo:
    std::vector<int64_t> exCoordenadas1Polygon = {-1000, 1000, -1200, 1200, -1000, 1400, -800, 1200};
    imagem.drawPolygon(exCoordenadas1Polygon);

    //Este polygon fora desenhado com a cor branca, eh possivel especificar uma cor, por exemplo:
    std::vector<int64_t> exCoordenadas2Polygon = {-1000, 1200, -1200, 1400, -1000, 1600, -800, 1400};
    imagem.drawPolygon(exCoordenadas2Polygon, AZUL);

    //O polygon tambem pode ser desenhada usando std::vectos de Vec2<T> contendo as respectivas coordenadas, exemplo:
    std::vector<art::Vec2<int64_t>> exCoordenadas3Polygon = {art::Vec2<int64_t>(-1000, 1400), art::Vec2<int64_t>(-800, 1600), art::Vec2<int64_t>(-1000, 1800), art::Vec2<int64_t>(-1200, 1600)};
    imagem.drawPolygon(exCoordenadas3Polygon);

    //Este polygon fora desenhado com a cor branca, eh possivel especificar uma cor, por exemplo:
    std::vector<art::Vec2<int64_t>> exCoordenadas4Polygon = {art::Vec2<int64_t>(-1000, 1600), art::Vec2<int64_t>(-800, 1800), art::Vec2<int64_t>(-1000, 2000), art::Vec2<int64_t>(-1200, 1800)};
    imagem.drawPolygon(exCoordenadas4Polygon, VERMELHO);

    /* DRAW FROM FILE */

    //Para carregar um arquivo contendo os valores x,y e desenhar os mesmos, basta chamar a funcao drawFile()
    //Passando o nome do arquivo
    imagem.drawFile("inputTextExample.txt");

    //Agora, um exemplo para desenhar funcoes:
    //Um for loop percorre horizontalmente a imagem
    //O ponto (0,0) eh o centro da imagem, sendo assim, em uma imagem 512x512 por exemplo, -256 e +256 sao as duas extremidades horizontais
    //Assim o loop precisa comecar na extremidade da esquerda, que eh igual a largura da imagem dividido por dois, multiplicado por -1 (para inverter o sinal),
    //Ate a largura da imagem dividido por dois

    /* DRAW FUNCTIONS */

    //Para desenhar funcoes, basta chamar a funcao drawFunction do objeto imagem, passando a funcao desejada
    //Exemplo:

    imagem.drawFunction("x^2+(x*2)");
    //Esta funcao sera desenhada em cor branca

    //Esta funcao fora desenhada com a cor branca, eh possivel especificar uma cor, por exemplo:
    imagem.drawFunction("x^3", MAGENTA);

    //Caso a funcao fique muito estreita, eh possivel esticar a mesma, utilizando-se de um fator de esticamento
    //Porem eh necessario especificar uma cor, exemplo:

    const int8_t esticamentoHorizontal = 16;
    //Define o esticamento horizontal e vertical da funcao, para a melhor visualizacao dos graficos
    imagem.drawFunction("x^2*(1-2)", AZUL, esticamentoHorizontal);

#ifdef USAR_BENCHMARK
    //Mostrar o tempo total de desenho
    auto endBenchmark = std::chrono::steady_clock::now();
    std::cout << "[DRAW]: Tempo de desenho (draw time): " << std::chrono::duration<double, std::milli>(endBenchmark - startBenchmark).count() << " ms" << std::endl;
#endif

//Escreve imagem!

//Caso estiver usando a nova biblioteca <filesystem> do C++17, passa uma referencia de um std::filesystem::path ou std::string
//Caso contrario, deve ser passado uma std::string
#ifdef USANDO_VERSAO_MODERNA
    //Passando um objeto std::filesystem::path
    fs::path imagemOutput = fs::current_path();
    imagemOutput /= "output.ppm";
    imagem.writeImagePPM(imagemOutput);
#else
    //Passando apenas uma std::string
    //imagem.writeImage()
    imagem.writeImage("../images_output/renderHelloWorld.ppm");
    imagem.writeImage("../images_output/renderHelloWorld.bmp");
#endif

    return 0;
}

//That's just a really nice random number generator
template <typename T>
T random_in_range(T range_start = std::numeric_limits<T>::min(), T range_end = std::numeric_limits<T>::max())
{
    std::mt19937 rng;
    rng.seed(std::random_device()());
    std::uniform_int_distribution<T> dist(range_start, range_end);
    return dist(rng);
}
