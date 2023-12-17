#ifndef UTIL_HPP
#define UTIL_HPP

using namespace std;

class Util {
public:
    // Constructor
    Util();

    // Destructor
    ~Util();

    // Other member functions and variables
    static bool pixel_out_of_bounds(int surface_width, int surface_height, int x, int y);
};

#endif // UTIL_HPP
