#include "image.hpp"

#include <cstdlib>
#include <cassert>


namespace image
{
    bool create_image(Image& image, u32 width, u32 height)
    {
        auto data = std::malloc(sizeof(Pixel) * width * height);
        if (!data)
        {
            return false;
        }

        image.data_ = (Pixel*)data;
        image.width = width;
        image.height = height;

        return true;
    }


    void destroy_image(Image& image)
    {
        if (image.data_)
        {
            std::free(image.data_);
            image.data_ = nullptr;
        }

        image.width = 0;
        image.height = 0;
    }


    ImageView make_view(Image const& image)
    {
        ImageView view{};

        view.width = image.width;
        view.height = image.height;
        view.image_data_ = image.data_;

        return view;
    }


    void fill(ImageView const& view, Pixel color)
    {
        assert(view.width);
        assert(view.height);
        assert(view.image_data_);
        
        for (u32 i = 0; i < view.width * view.height; i++)
        {
            view.image_data_[i] = color;
        }
    }
}