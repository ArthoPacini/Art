#include "../include/Art/Art.h"
#include <iostream>
#include <limits>

int main()
{
    std::cout << "--== VEC TEST ==--" << std::endl;

    std::cout << "Vec2<double> max = " << std::numeric_limits<art::Vec2<double>>::max();

    std::cout << "Testing Vec2<double>" << std::endl;
    {
        art::Vec2<double> a(1.0, 1.0);
        std::cout << "Vec2<double> a(1.0, 1.0) created..." << std::endl;
        art::Vec2<double> b(2.0, 2.0);
        std::cout << "Vec2<double> b(2.0, 2.0) created..." << std::endl;

        art::Vec2<double> c;
        std::cout << "Vec2<double> c created..." << std::endl;
        c = a + b;
        std::cout << "c = a + b" << std::endl;
        std::cout << "c = " << c << std::endl;
        c = a - b;
        std::cout << "c = a - b" << std::endl;
        std::cout << "c = " << c << std::endl;
        c = a / b;
        std::cout << "c = a / b" << std::endl;
        std::cout << "c = " << c << std::endl;
        c = a * b;
        std::cout << "c = a * b" << std::endl;
        std::cout << "c = " << c << std::endl;

        c = a + 1.5;
        std::cout << "c = a + 1.5" << std::endl;
        std::cout << "c = " << c << std::endl;
        c = a - 1.5;
        std::cout << "c = a - 1.5" << std::endl;
        std::cout << "c = " << c << std::endl;
        c = a / 1.5;
        std::cout << "c = a / 1.5" << std::endl;
        std::cout << "c = " << c << std::endl;
        c = a * 1.5;
        std::cout << "c = a * 1.5" << std::endl;
        std::cout << "c = " << c << std::endl;

        c += a;
        std::cout << "c = a += 1.5" << std::endl;
        std::cout << "c = " << c << std::endl;
        c -= b;
        std::cout << "c = a -= 1.5" << std::endl;
        std::cout << "c = " << c << std::endl;
        c *= a;
        std::cout << "c = a *= 1.5" << std::endl;
        std::cout << "c = " << c << std::endl;
        c /= b;
        std::cout << "c = a /= 1.5" << std::endl;
        std::cout << "c = " << c << std::endl;

        c++;
        std::cout << "c++" << std::endl;
        std::cout << "c = " << c << std::endl;
        c--;
        std::cout << "c--" << std::endl;
        std::cout << "c = " << c << std::endl;
        --c;
        std::cout << "--c" << std::endl;
        std::cout << "c = " << c << std::endl;
        ++c;
        std::cout << "++c" << std::endl;
        std::cout << "c = " << c << std::endl;

        c[0]++;
        std::cout << "c[0]++" << std::endl;
        std::cout << "c = " << c << std::endl;
        c[1]++;
        std::cout << "c[1]++" << std::endl;
        std::cout << "c = " << c << std::endl;

        std::cout << "a == b ? " << (a == b) << std::endl;
        std::cout << "a != b ? " << (a != b) << std::endl;
        std::cout << "a > b ? " << (a > b) << std::endl;
        std::cout << "a < b ? " << (a < b) << std::endl;
        std::cout << "a >= b ? " << (a >= b) << std::endl;
        std::cout << "a <= b ? " << (a <= b) << std::endl;
    }

    {
        art::Vec3<double> a(1.0, 1.0, 1.0);
        std::cout << "Vec2<double> a(1.0, 1.0, 1.0) created..." << std::endl;
        art::Vec3<double> b(2.0, 2.0, 2.0);
        std::cout << "Vec2<double> b(2.0, 2.0, 2.0) created..." << std::endl;

        art::Vec3<double> c;
        std::cout << "Vec2<double> c created..." << std::endl;
        c = a + b;
        std::cout << "c = a + b" << std::endl;
        std::cout << "c = " << c << std::endl;
        c = a - b;
        std::cout << "c = a - b" << std::endl;
        std::cout << "c = " << c << std::endl;
        c = a / b;
        std::cout << "c = a / b" << std::endl;
        std::cout << "c = " << c << std::endl;
        c = a * b;
        std::cout << "c = a * b" << std::endl;
        std::cout << "c = " << c << std::endl;

        c = a + 1.5;
        std::cout << "c = a + 1.5" << std::endl;
        std::cout << "c = " << c << std::endl;
        c = a - 1.5;
        std::cout << "c = a - 1.5" << std::endl;
        std::cout << "c = " << c << std::endl;
        c = a / 1.5;
        std::cout << "c = a / 1.5" << std::endl;
        std::cout << "c = " << c << std::endl;
        c = a * 1.5;
        std::cout << "c = a * 1.5" << std::endl;
        std::cout << "c = " << c << std::endl;

        c += a;
        std::cout << "c = a += 1.5" << std::endl;
        std::cout << "c = " << c << std::endl;
        c -= b;
        std::cout << "c = a -= 1.5" << std::endl;
        std::cout << "c = " << c << std::endl;
        c *= a;
        std::cout << "c = a *= 1.5" << std::endl;
        std::cout << "c = " << c << std::endl;
        c /= b;
        std::cout << "c = a /= 1.5" << std::endl;
        std::cout << "c = " << c << std::endl;

        c++;
        std::cout << "c++" << std::endl;
        std::cout << "c = " << c << std::endl;
        c--;
        std::cout << "c--" << std::endl;
        std::cout << "c = " << c << std::endl;
        --c;
        std::cout << "--c" << std::endl;
        std::cout << "c = " << c << std::endl;
        ++c;
        std::cout << "++c" << std::endl;
        std::cout << "c = " << c << std::endl;

        c[0]++;
        std::cout << "c[0]++" << std::endl;
        std::cout << "c = " << c << std::endl;
        c[1]++;
        std::cout << "c[1]++" << std::endl;
        std::cout << "c = " << c << std::endl;
        c[2]++;
        std::cout << "c[2]++" << std::endl;
        std::cout << "c = " << c << std::endl;

        std::cout << "a == b ? " << (a == b) << std::endl;
        std::cout << "a != b ? " << (a != b) << std::endl;
        std::cout << "a > b ? " << (a > b) << std::endl;
        std::cout << "a < b ? " << (a < b) << std::endl;
        std::cout << "a >= b ? " << (a >= b) << std::endl;
        std::cout << "a <= b ? " << (a <= b) << std::endl;
    }
}
