# Art
Art is a simple C++ graphical library

# Documentation

## art::Image

The art::Image object is the main object that holds image data

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

Compile it with your favorite compiler, example:
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

To draw a line, all we need is to call the drawLine() function from the art::Image object, so let's draw a simple line:

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


