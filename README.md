# Art
Art is a minimalist C++ graphical library

# Documentation

## Integration

[`Art.h`](https://https://github.com/ArthoPacini/Art/blob/master/Art/include/Art/Art.h) is the library header. Just write

```cpp
#include "include/Art/Art.h"
```
to your main file.
do not forget to compile it using -std=c++17 compiler flag.

## Examples

The following examples cover the Art library usage

### Creating an image and saving it

The ```cpp art::Image<T> ``` class holds an image in memory, it creates a 2-dimensional array frameBuffer of type T (usually a ```cpp art::Vec3<std::uint8_t> ``` which holds 3 pixels), and exposes some drawing functions.

The following code creates and saves an image to disk.

```cpp
#include "include/Art/Art.h"

int main()
{
    //Creates a black image with a resolution of 4096x4096
    auto image = art::Image<art::Vec3<std::uint8_t>>(4096, 4096); 

    //Saves image to disk
    image.writeImage("output.bmp");
}
```

Compile it:

```bash
g++ main.cpp -o main -std=c++17
```
or 

```bash
clang++ main.cpp -o main -std=c++17
```

Run it and you should get the corresponding image:
<br/>
![black image 4096x4096](https://i.imgur.com/5i54mrG.png)

<br/>
You may specify a background color on the third constructor parameter 
<br/>

```cpp
#include "include/Art/Art.h"

int main()
{
    //Creates a image object with 2048 width and 2048 height
    //With a custom background
    const auto backgroundColor = art::Vec3<std::uint8_t>(255, 174, 201);
    auto image = art::Image<art::Vec3<std::uint8_t>>(4096, 4096, backgroundColor);

    //Saves image
    image.writeImage("output.bmp");
}
```

Output:
<br/>
![custom background image 4096x4096](https://i.imgur.com/I7MEgmx.png)
<br/>

## Drawing a line

To draw a line, all we need to do is call the ```art::Image::drawLine()``` function.

This function has 2 overloads:
```cpp
void drawLine(const std::int64_t x, const std::int64_t y, const std::int64_t x2, const std::int64_t y2, const T color = T(std::numeric_limits<T>::max()))
```
and
```cpp
drawLine(art::Vec2<std::int64_t> p1, art::Vec2<std::int64_t> p2, const T color = T(std::numeric_limits<T>::max()))
```

We need to specify two points on the image

An usage example:

```cpp
#include "include/Art/Art.h"

int main()
{
    //Creates a image object with 2048 pixels width and 2048 pixels height
    //With a black background (not specified)
    
    //                                             width | height
    auto image = art::Image<art::Vec3<std::uint8_t>>(512, 512);

    //                                x,y       x , y
    //Draws a white line, from point (0,0) to (100,100)
    image.drawLine(0, 0, 100, 100);

    //Saves image
    image.writeImage("output.bmp");
}
```

which produces:

![draw line 0](https://i.imgur.com/Rjwaoee.png)

Note that the default color is white.
You may also specify a custom color, passing it as the last argument:

```cpp
#include "include/Art/Art.h"

int main()
{
    //Creates a image object with 2048 width and 2048 height
    //With a black background
    
    //                                             width | height
    auto image = art::Image<art::Vec3<std::uint8_t>>(512, 512);

    const auto drawingColor = art::Vec3<std::uint8_t>(130, 20, 95);

    //                                x,y       x , y
    //Draws a white line, from point (0,0) to (100,100)
    image.drawLine(0, 0, 100, 100, drawingColor);

    //Saves image
    image.writeImage("output.bmp");
}
```

which produces:

![draw line 1](https://i.imgur.com/5cJ2cGj.png)


You may also use the ```cpp art::Vec2<std::int64_t> ``` class to specify coordinates

```cpp
#include "include/Art/Art.h"

int main()
{
    //Creates a image object with 2048 width and 2048 height
    //With a black background
    
    //                                             width | height
    auto image = art::Image<art::Vec3<std::uint8_t>>(512, 512);

    const auto drawingColor = art::Vec3<std::uint8_t>(130, 20, 95);

    auto firstPoint = art::Vec2<std::int64_t>(0,0);
    auto secondPoint = art::Vec2<std::int64_t>(100,100);

    //                                x,y       x , y
    //Draws a white line, from point (0,0) to (100,100)
    image.drawLine(firstPoint, secondPoint, drawingColor);

    //Saves image
    image.writeImage("output.bmp");
}
```

which produces the same result

## Drawing a circle

To draw a circle, all we need to do is call the ```cpp art::Image::drawCircle() ``` function.
