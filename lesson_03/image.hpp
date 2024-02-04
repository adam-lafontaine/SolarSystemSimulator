#include "types.hpp"


namespace image
{
    class RGBAu8
    {
    public:
        u8 red;
        u8 green;
        u8 blue;
        u8 alpha;
    };

    using Pixel = RGBAu8;


    class Image
    {
    public:
        u32 width = 0;
        u32 height = 0;

        Pixel* data_ = nullptr;
    };


    class ImageView
    {
    public:
        u32 width = 0;
        u32 height = 0;

        Pixel* image_data_ = nullptr;
    };


    constexpr inline Pixel to_pixel(u8 red, u8 green, u8 blue, u8 alpha)
    {
        Pixel p{};
        p.red = red;
        p.green = green;
        p.blue = blue;
        p.alpha = alpha;

        return p;
    }


    constexpr inline Pixel to_pixel(u8 red, u8 green, u8 blue)
    {
        return to_pixel(red, green, blue, 255);
    }


    constexpr inline Pixel to_pixel(u8 gray)
    {
        return to_pixel(gray, gray, gray);
    }


    bool create_image(Image& image, u32 width, u32 height);

    void destroy_image(Image& image);

    
    ImageView make_view(Image const& image);


    void fill(ImageView const& view, Pixel color);
}