# Art
Art is a simple C++ graphical library

# Documentation

## Integration

[`Art.h`](https://https://github.com/ArthoPacini/Art/blob/master/Art/include/Art/Art.h) is the single required file to include. You need to add

```cpp
#include "include/Art/Art.h"
```
to the files you want to process images. is necessary to enable C++17 on compile (e.g., -std=c++17 for GCC and Clang).

## Examples

The following examples cover all of the Art library usage

### Creating an image and saving it

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

Output of above code:
<br/>
![black image 4096x4096](https://i.imgur.com/5i54mrG.png)

<br/>
You may specify a background color like
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

To draw a line, all we need is to call the ```cpp art::Image::drawLine()``` function, passing the line start point x1,y1 and the line ending point x2,y2:

```cpp
#include "include/Art/Art.h"

int main()
{
    //Creates a image object with 2048 width and 2048 height
    //With a black background
    auto image = art::Image<art::Vec3<std::uint8_t>>(512, 512);

    //                                x,y       x , y
    //Draws a white line, from point (0,0) to (100,100)
    image.drawLine(0, 0, 100, 100);

    //Saves image
    image.writeImage("output.bmp");
}
```

![draw line 0](https://i.imgur.com/Rjwaoee.png)

Note that the default color is white.
You may also specify a custom color, passing it on the last argument:

```cpp
#include "include/Art/Art.h"

int main()
{
    //Creates a image object with 2048 width and 2048 height
    //With a black background
    auto image = art::Image<art::Vec3<std::uint8_t>>(512, 512);

    const auto drawingColor = art::Vec3<std::uint8_t>(130, 20, 95);

    //                                x,y       x , y
    //Draws a white line, from point (0,0) to (100,100)
    image.drawLine(0, 0, 100, 100, drawingColor);

    //Saves image
    image.writeImage("output.bmp");
}
```

![draw line 0](https://i.imgur.com/5cJ2cGj.png)

