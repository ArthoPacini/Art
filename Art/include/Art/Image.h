#ifndef IMAGE_H_
#define IMAGE_H_

//Inclui o <filesystem>
#ifdef USANDO_VERSAO_MODERNA

#include <filesystem>

#ifdef _WIN32 //MSVC++ utiliza experimental
namespace fs = std::experimental::filesystem;
#else
namespace fs = std::filesystem;
#endif
#endif

#include <limits>
#include <thread>
#include <chrono>
#include <algorithm>
#include "Buffer2D.h"
#include "Vec2.h"
#include "RandomInRange.h"
#include "../Interpreter/Function.h"

namespace art
{
template <typename T>
class Image
{
private:
    Buffer2D<T> frameBuffer;
    int64_t width, height;
    int64_t widthBoundPositive, heightBoundPositive;
    int64_t widthBoundNegative, heightBoundNegative;

    std::vector<art::Vec2<int64_t>> DrawingVerticesBuffer;

public:
    Image(const unsigned x, const unsigned y, const T fill_ = T())
    {
        width = x;
        height = y;

        widthBoundPositive = (width / 2) * 2;
        heightBoundPositive = (height / 2) * 2;
        widthBoundNegative = (widthBoundPositive * -1) * 2;
        heightBoundNegative = (heightBoundPositive * -1) * 2;

        //std::cout << "[IMAGE]: Construindo imagem..." << std::endl;
#ifdef USAR_BENCHMARK
        auto startBenchmark = std::chrono::steady_clock::now();
#endif

        frameBuffer.initialize(x, y, fill_);
        //std::cout << "[IMAGE]: Imagem criada..." << std::endl;

#ifdef USAR_BENCHMARK
        auto endBenchmark = std::chrono::steady_clock::now();
        std::cout << "[IMAGE]: Tempo para inicializacao da imagem: " << std::chrono::duration<double, std::milli>(endBenchmark - startBenchmark).count() << " ms" << std::endl;
#endif
    }

    void fill(const T fill_ = T())
    {
        frameBuffer.fill(fill_);
    }

    void clear()
    {
        frameBuffer.initialize(width, height);
    }

    void writeBinary(std::ofstream &outputFile, const T &dataBuffer, const std::ios_base::openmode io_mode = std::ios::binary | std::ios::app)
    {
        outputFile.write((const char *)&dataBuffer, sizeof(dataBuffer));
    }

    void setPixel(int64_t x, int64_t y, const T color = T(std::numeric_limits<T>::max()))
    {
        y *= -1;
        x += (width / 2);
        y += (height / 2);
        if (!validBounds(x, y))
            return;

        frameBuffer(x, y) = color;
    }

    /* DESENHAR A PARTIR DE ARQUIVO */
    void drawFile(std::string fileName, const T color = T(std::numeric_limits<T>::max()))
    {
        std::ifstream file(fileName);
        if (!file)
            return;
        double input;
        bool flipFlop = true;
        while (file >> input)
        {
            if (flipFlop)
                DrawingVerticesBuffer.push_back(art::Vec2<int64_t>(input, 0));
            else
                DrawingVerticesBuffer.back() += art::Vec2<int64_t>(0, input);

            flipFlop = !flipFlop;
        }

        drawMultiLineFunction();
    }

    /* DRAW MULTI LINE */

    void drawMultiLineFunction(art::Vec2<int64_t> const arg, uint64_t &polygonCounter)
    {
        DrawingVerticesBuffer.push_back(arg);
    }

    void drawMultiLineFunction(int64_t const arg, uint64_t &polygonCounter)
    {
        if (polygonCounter % 2 == 0)
            DrawingVerticesBuffer.push_back(art::Vec2<int64_t>(arg, 0));
        else
            DrawingVerticesBuffer.back() += art::Vec2<int64_t>(0, arg);

        polygonCounter++;
    }

    void drawMultiLineFunction(const T color = T(std::numeric_limits<T>::max()))
    {
        art::Vec2<int64_t> verticeBuffer;
        while (DrawingVerticesBuffer.size() - 1)
        {
            verticeBuffer = DrawingVerticesBuffer.back();
            DrawingVerticesBuffer.pop_back();
            drawLine(verticeBuffer, DrawingVerticesBuffer.back(), color);
        }
        DrawingVerticesBuffer.clear();
    }

    template <typename... Args>
    void drawMultiLine(Args const... args)
    {
        if (sizeof...(args) < 2)
            return;
        DrawingVerticesBuffer.reserve(sizeof...(args));
        uint64_t polygonCounter = 0;
        (void)std::initializer_list<int>{
            ((void)drawMultiLineFunction(args, polygonCounter), 0)...};

        drawMultiLineFunction();
    }

    template <typename... Args>
    void drawMultiLine(const T color = T(std::numeric_limits<T>::max()), Args const... args)
    {
        if (sizeof...(args) < 2)
            return;
        DrawingVerticesBuffer.reserve(sizeof...(args));
        uint64_t polygonCounter = 0;
        (void)std::initializer_list<int>{
            ((void)drawMultiLineFunction(args, polygonCounter), 0)...};

        drawMultiLineFunction(color);
    }

    void drawMultiLine(std::vector<int64_t> &vertices, const T color = T(std::numeric_limits<T>::max()))
    {
        if (vertices.size() < 4 || vertices.size() % 2 != 0)
            return;

        uint64_t polygonCounter = 0;
        for (const auto &vertex : vertices)
            drawMultiLineFunction(vertex, polygonCounter);

        drawMultiLineFunction(color);
    }

    void drawMultiLine(std::vector<art::Vec2<int64_t>> vertices, const T color = T(std::numeric_limits<T>::max()))
    {
        if (vertices.size() < 2)
            return;

        uint64_t polygonCounter = 0;
        for (const auto &vertex : vertices)
            drawMultiLineFunction(vertex, polygonCounter);

        drawMultiLineFunction(color);
    }

    /* DRAW POLYGON */

    void drawPolygonFunction(art::Vec2<int64_t> const arg, uint64_t &polygonCounter)
    {
        DrawingVerticesBuffer.push_back(arg);
    }

    void drawPolygonFunction(int64_t const arg, uint64_t &polygonCounter)
    {
        if (polygonCounter % 2 == 0)
            DrawingVerticesBuffer.push_back(art::Vec2<int64_t>(arg, 0));
        else
            DrawingVerticesBuffer.back() += art::Vec2<int64_t>(0, arg);

        polygonCounter++;
    }

    void drawPolygonFunction(const T color = T(std::numeric_limits<T>::max()))
    {
        drawLine(DrawingVerticesBuffer.front(), DrawingVerticesBuffer.back(), color);

        art::Vec2<int64_t> verticeBuffer;
        while (DrawingVerticesBuffer.size() - 1)
        {
            verticeBuffer = DrawingVerticesBuffer.back();
            DrawingVerticesBuffer.pop_back();
            drawLine(verticeBuffer, DrawingVerticesBuffer.back(), color);
        }
        DrawingVerticesBuffer.clear();
    }

    template <typename... Args>
    void drawPolygon(Args const... args)
    {
        if (sizeof...(args) < 3)
            return;
        DrawingVerticesBuffer.reserve(sizeof...(args));
        uint64_t polygonCounter = 0;
        (void)std::initializer_list<int>{
            ((void)drawPolygonFunction(args, polygonCounter), 0)...};

        drawPolygonFunction();
    }

    template <typename... Args>
    void drawPolygon(const T color = T(std::numeric_limits<T>::max()), Args const... args)
    {
        if (sizeof...(args) < 3)
            return;
        DrawingVerticesBuffer.reserve(sizeof...(args));
        uint64_t polygonCounter = 0;
        (void)std::initializer_list<int>{
            ((void)drawPolygonFunction(args, polygonCounter), 0)...};

        drawPolygonFunction(color);
    }

    void drawPolygon(std::vector<int64_t> &vertices, const T color = T(std::numeric_limits<T>::max()))
    {
        if (vertices.size() < 4 || vertices.size() % 2 != 0)
            return;

        uint64_t polygonCounter = 0;
        for (const auto &vertex : vertices)
            drawPolygonFunction(vertex, polygonCounter);

        drawPolygonFunction(color);
    }

    void drawPolygon(std::vector<art::Vec2<int64_t>> vertices, const T color = T(std::numeric_limits<T>::max()))
    {
        if (vertices.size() < 2)
            return;

        uint64_t polygonCounter = 0;
        for (const auto &vertex : vertices)
            drawPolygonFunction(vertex, polygonCounter);

        drawPolygonFunction(color);
    }

    void drawRectangle(art::Vec2<int64_t> p1, art::Vec2<int64_t> p2, const T color = T(std::numeric_limits<T>::max()))
    {
        drawRectangle(p1.getX(), p1.getY(), p2.getX(), p2.getY(), color);
    }

    void drawRectangle(int64_t x1, int64_t y1, int64_t x2, int64_t y2, const T color = T(std::numeric_limits<T>::max()))
    {
        drawLine(x1, y1, x2, y1, color); //desenha topo
        drawLine(x1, y1, x1, y2, color); //desenha lado esquerdo
        drawLine(x2, y1, x2, y2, color); //desenha lado direito
        drawLine(x1, y2, x2, y2, color); //desenha em baixo
    }

    void drawTriangle(art::Vec2<int64_t> p1, art::Vec2<int64_t> p2, art::Vec2<int64_t> p3, const T color = T(std::numeric_limits<T>::max()))
    {
        drawTriangle(p1.getX(), p1.getY(), p2.getX(), p2.getY(), p3.getX(), p3.getY(), color);
    }

    void drawTriangle(int64_t x1, int64_t y1, int64_t x2, int64_t y2, int64_t x3, int64_t y3, const T color = T(std::numeric_limits<T>::max()))
    {
        drawLine(x1, y1, x2, y2, color);
        drawLine(x2, y2, x3, y3, color);
        drawLine(x3, y3, x1, y1, color);
    }

    void drawCircle(art::Vec2<int64_t> p, int64_t raio, const T color = T(std::numeric_limits<T>::max()))
    {
        drawCircle(p.getX(), p.getY(), raio, color);
    }

    void drawCircle(int64_t xCenter, int64_t yCenter, int64_t raio, const T color = T(std::numeric_limits<T>::max()))
    {
        int64_t x = raio;
        int64_t y = 0;
        int64_t d = 1 - raio;

        while (x > y)
        {
            setPixel(x + xCenter, y + yCenter, color);
            setPixel(x + xCenter, -y + yCenter, color);
            setPixel(-x + xCenter, y + yCenter, color);
            setPixel(-x + xCenter, -y + yCenter, color);
            setPixel(y + xCenter, x + yCenter, color);
            setPixel(y + xCenter, -x + yCenter, color);
            setPixel(-y + xCenter, x + yCenter, color);
            setPixel(-y + xCenter, -x + yCenter, color);
            y = y + 1;
            if (d < 0)
                d = d + 2 * y + 1;
            else
            {
                x = x - 1;
                d = d + 2 * (y - x) + 1;
            }
        }

        // fonte(melhor): https://www.cs.helsinki.fi/group/goa/mallinnus/ympyrat/ymp1.html
        // fonde: http://groups.csail.mit.edu/graphics/classes/6.837/F98/Lecture6/circle.html
    }

    bool const validBounds(int64_t x, int64_t y) const
    {
        if (x < width && x > 0 && y < height && y > 0)
            return true;
        return false;
    }

    void drawLine(art::Vec2<int64_t> p1, art::Vec2<int64_t> p2, const T color = T(std::numeric_limits<T>::max()))
    {
        drawLine(p1.getX(), p1.getY(), p2.getX(), p2.getY(), color);
    }

    inline void drawLine(const int64_t x, const int64_t y, const int64_t x2, const int64_t y2, const T color = T(std::numeric_limits<T>::max()))
    {
        bool yLonger = false;
        int64_t incrementVal;

        int64_t shortLen = y2 - y;
        int64_t longLen = x2 - x;
        if (abs(shortLen) > abs(longLen))
        {
            std::swap(shortLen, longLen);
            /*shortLen ^= longLen; 
                longLen  ^= shortLen; 
                shortLen ^= longLen;*/
            yLonger = true;
        }

        if (longLen < 0)
            incrementVal = -1;
        else
            incrementVal = 1;

        double divDiff;
        if (shortLen == 0)
            divDiff = longLen;
        else
            divDiff = (double)longLen / (double)shortLen;
        if (yLonger)
        {
            for (int64_t i = 0; i != longLen; i += incrementVal)
            {
                setPixel(x + (int64_t)((double)i / divDiff), y + i, color);
            }
        }
        else
        {
            for (int64_t i = 0; i != longLen; i += incrementVal)
            {
                setPixel(x + i, y + (int64_t)((double)i / divDiff), color);
            }
        }
    }

    bool yInside(int64_t y)
    {
        if (y < heightBoundPositive && y > heightBoundNegative)
            return true;

        return false;
    }

    art::Vec2<int64_t> getRange(art::Vec2<int64_t> range, unsigned sliceNumber, unsigned maxSlices, const bool getRangeForDraw = false)
    {
        bool doNormalize = false;
        if (range.getX() < 0)
        {
            doNormalize = true;
            range += range.getY();
        }

        uint16_t resto = range.getY() % maxSlices;

        int64_t rangeStart = range.getX() + (sliceNumber * (range.getY() / maxSlices));
        int64_t rangeEnd;

        if ((sliceNumber + 1) == maxSlices)
        {
            rangeEnd = rangeStart + (range.getY() / maxSlices) - 1 + resto;
            while (rangeEnd >= range.getY())
                rangeEnd--;
        }
        else
            rangeEnd = rangeStart + (range.getY() / maxSlices) - 1;

        if (getRangeForDraw)
        {
            if (doNormalize)
                return art::Vec2<int64_t>(rangeStart, rangeEnd - 1);
            else
                return art::Vec2<int64_t>(rangeStart, rangeEnd - 1) - 3;
        }

        if (doNormalize)
            return art::Vec2<int64_t>(rangeStart, rangeEnd - 1) - (range.getY() / 2);

        return art::Vec2<int64_t>(rangeStart, rangeEnd - 1);
    }

    void drawFunction(std::string expression, const T color = T(std::numeric_limits<T>::max()), const int64_t esticamentoHorizontal = 1)
    {
        DrawingVerticesBuffer.clear();
        art::Function function(expression);

        const int64_t rangeEnd = (frameBuffer.getWidth() / 2);
        const int64_t rangeStart = rangeEnd * -1;

        for (int64_t x = rangeStart; x < rangeEnd; x++)
        {
            const int64_t yResult = function.getResult(x);

            //Just add the result to DrawingBuffer if it actually appears in the image, otherwise skip it
            if (yInside(yResult))
                DrawingVerticesBuffer.push_back(art::Vec2<int64_t>(x * esticamentoHorizontal, yResult));

            //Uncomment below line to show progress...
            //std::cout << "[CALCULATING]: " << x << " of " << rangeEnd << " steps..." << std::endl;
        }

        drawMultiLineFunction(color);
    }

#ifdef USANDO_VERSAO_MODERNA
    void const writeImagePPM(fs::path filePath, const std::ios_base::openmode io_mode = std::ios::binary | std::ios::app)
    {
        if (fs::exists(filePath))
            fs::remove(filePath);

        //ESCREVE HEADER
        std::ofstream file(filePath.string().c_str());
        file << "P6\n"
             << frameBuffer.getLargura() << ' ' << frameBuffer.getAltura() << "\n"
             << static_cast<unsigned>(std::numeric_limits<T>::max()) << "\n";
        file.close();

        file.open(filePath.string().c_str(), io_mode);
        //ESCREVE IMAGEM
        frameBuffer.writeToDisk(file);
        file.close();
    }
#endif

    std::size_t const doesFileNameHasExtension(const std::string &fileName)
    {
        for (std::size_t i = fileName.length() - 1; i != 0; --i)
            if (fileName[i] == '.')
                return i;

        return 0;
    }

    std::string const getFileNameExtension(const std::string &fileName, std::size_t dotPosition)
    {
        return fileName.substr(dotPosition, fileName.length() - dotPosition);
    }

    void const writeImage(const std::string &fileName)
    {
        const std::size_t hasExtension = doesFileNameHasExtension(fileName);
        if (hasExtension == 0)
        {
            writeImageRAW("output.raw");
            return;
        }

        const std::string extension = getFileNameExtension(fileName, hasExtension);
        if (extension == ".bmp")
        {
            writeImageBMP(fileName);
            return;
        }
        if (extension == ".ppm")
        {
            writeImagePPM(fileName);
            return;
        }
        else
            writeImageRAW(fileName);
    }

    void const writeImagePPM(const std::string &fileName, const std::ios_base::openmode io_mode = std::ios::binary | std::ios::app) const
    {
        //std::cout << "[IMAGEM]: Escrevendo imagem .ppm..." << std::endl;
        //ESCREVE HEADER
        std::ofstream file(fileName.c_str(), std::ios::trunc);
        file << "P6\n"
             << frameBuffer.getLargura() << ' ' << frameBuffer.getAltura() << "\n"
             << /*static_cast<unsigned>(*/ std::numeric_limits<T>::max() /*)*/ << "\n";
        file.close();

        file.open(fileName.c_str(), io_mode);
        //ESCREVE IMAGEM
        frameBuffer.writeToDisk(file);
        file.close();

        //std::cout << "[IMAGEM]: Imagem .ppm escrita..." << std::endl;
    }

    void writeImageRAW(const std::string &fileName, const std::ios_base::openmode io_mode = std::ios::binary | std::ios::app)
    {
        std::ofstream fileOutput(fileName, std::ios::trunc);
        fileOutput.close();
        fileOutput.open(fileName, io_mode);
        frameBuffer.writeToDisk(fileOutput);
        fileOutput.close();
    }

    void writeImageBMP(const std::string &fileName, const std::ios_base::openmode io_mode = std::ios::binary | std::ios::app)
    {
        //std::cout << "[IMAGEM]: Escrevendo imagem .bmp..." << std::endl;
        std::ofstream fileOutput(fileName, std::ios::trunc);
        fileOutput.close();
        fileOutput.open(fileName, io_mode);
        frameBuffer.writeToDiskBMP(fileOutput);
        fileOutput.close();
        //std::cout << "[IMAGEM]: Imagem .bmp escrita..." << std::endl;
    }

    uint64_t getSizeInBytes()
    {
        return frameBuffer.getSizeInBytes() + sizeof(this);
    }

    const T &operator()(uint64_t x, uint64_t y) const
    {
        return frameBuffer(x, y);
    }

    T &operator()(uint64_t x, uint64_t y)
    {
        return frameBuffer(x, y);
    }
};
} // namespace art
#endif