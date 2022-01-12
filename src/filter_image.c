
#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include <math.h>
#include <assert.h>
#include "image.h"
#define TWOPI 6.2831853


void l1_normalize(image im)

{
    for (int c = 0;c < im.c;c++) {
        float sum = 0;
        for (int i = 0;i < im.h;i++) {
            for (int j = 0;j < im.w;j++) {
                sum += get_pixel(im, j, i, c);
            }

        }
        for (int i = 0;i < im.h;i++) {
            for (int j = 0;j < im.w;j++) {
                float v;
                v = get_pixel(im, j, i, c) / sum;
                set_pixel(im, j, i, c, v);
            }

        }


    }
}

image make_box_filter(int w)
{
    // TODO
    image filter = make_image(w, w, 1);
    for (int i = 0;i < w;i++) {
        for (int j = 0;j < w;j++) {
            set_pixel(filter, j, i, 0, 1);
        }
    }

    l1_normalize(filter);
    return filter;
}
float apply_filter(image im, image filter, int j, int i, int channel) {
    float sum = 0;

    int mid = (filter.w % 2 == 0) ? filter.w / 2 : (filter.w + 1) / 2;
    for (int a = 0;a < filter.h;++a) {
        for (int b = 0;b < filter.w;++b) {
            float value = get_pixel(im, b + j - mid + 1, a + i - mid + 1, channel) * get_pixel(filter, b, a, 0);
            sum = sum + value;
        }

    }
    return sum;
}

image convolve_image(image im, image filter, int preserve)
{
    float val;
    image blur = make_image(im.w, im.h, im.c);
    for (int channel = 0;channel < im.c;channel++) {
        for (int i = 0;i < im.h;i++) {
            for (int j = 0;j < im.w;j++) {
                val = apply_filter(im, filter, j, i, channel);
                set_pixel(blur, j, i, channel, val);
            }
        }
    }
    feature_normalize(blur);

    return blur;
}




image make_highpass_filter()
{
    // TODO
    image highpass = make_image(3, 3, 1);

    // Row 1
    set_pixel(highpass, 0, 0, 0, 0);
    set_pixel(highpass, 1, 0, 0, -1);
    set_pixel(highpass, 2, 0, 0, 0);
    // Row 2
    set_pixel(highpass, 0, 1, 0, -1);
    set_pixel(highpass, 1, 1, 0, 4);
    set_pixel(highpass, 2, 1, 0, -1);
    // Row 3
    set_pixel(highpass, 0, 2, 0, 0);
    set_pixel(highpass, 1, 2, 0, -1);
    set_pixel(highpass, 2, 2, 0, 0);


    return highpass;
}

image make_sharpen_filter()
{
    image highpass = make_image(3, 3, 1);

    // Row 1
    set_pixel(highpass, 0, 0, 0, 0);
    set_pixel(highpass, 1, 0, 0, -1);
    set_pixel(highpass, 2, 0, 0, 0);
    // Row 2
    set_pixel(highpass, 0, 1, 0, -1);
    set_pixel(highpass, 1, 1, 0, 5);
    set_pixel(highpass, 2, 1, 0, -1);
    // Row 3
    set_pixel(highpass, 0, 2, 0, 0);
    set_pixel(highpass, 1, 2, 0, -1);
    set_pixel(highpass, 2, 2, 0, 0);



    return highpass;
    // TODO
    // return make_image(1,1,1);
}

image make_emboss_filter()
{
    // TODO  image highpass = make_image(3, 3, 1);
    image highpass = make_image(3, 3, 1);

    // Row 1
    set_pixel(highpass, 0, 0, 0, -2);
    set_pixel(highpass, 1, 0, 0, -1);
    set_pixel(highpass, 2, 0, 0, 0);
    // Row 2
    set_pixel(highpass, 0, 1, 0, -1);
    set_pixel(highpass, 1, 1, 0, 1);
    set_pixel(highpass, 2, 1, 0, 1);
    // Row 3
    set_pixel(highpass, 0, 2, 0, 0);
    set_pixel(highpass, 1, 2, 0, 1);
    set_pixel(highpass, 2, 2, 0, 2);


    return highpass;
    // return make_image(1,1,1);
}

// Question 2.2.1: Which of these filters should we use preserve when we run our convolution and which ones should we not? Why?
// Answer: TODO

// Question 2.2.2: Do we have to do any post-processing for the above filters? Which ones and why?
// Answer: TODO

image make_gaussian_filter(float sigma)

{
    int size = 6 * sigma;
    size = (size % 2 == 0) ? size + 1 : size;
    image filter = make_image(size, size, 1);
    int x, y;
    for (int i = 0;i < filter.h;i++) {
        for (int j = 0;j < filter.w;j++) {
            x = j - (filter.w + 1) / 2;
            y = i - (filter.h + 1) / 2;
            float value = (1 / (2 * 3.14 * sigma * sigma)) * exp(-(x * x + y * y) / (2 * sigma * sigma));
            set_pixel(filter, j, i, 0, value);
        }
    }


    return filter;
}

image add_image(image a, image b)
{
    // TODO
    return make_image(1, 1, 1);
}

image sub_image(image a, image b)
{
    // TODO
    return make_image(1, 1, 1);
}

image make_gx_filter()
{
    // TODO
    return make_image(1, 1, 1);
}

image make_gy_filter()
{
    // TODO
    return make_image(1, 1, 1);
}

void feature_normalize(image im)
{

    for (int c = 0;c < im.c;c++) {
        float min = 0;
        float max = 0;
        float value = 0;
        for (int i = 0;i < im.h;i++) {
            for (int j = 0;j < im.w;j++) {

                min = (min <= get_pixel(im, j, i, c)) ? min : get_pixel(im, j, i, c);
                max = (max >= get_pixel(im, j, i, c)) ? min : get_pixel(im, j, i, c);
            }
        }
    
        for (int i = 0;i < im.h;i++) {
            for (int j = 0;j < im.w;j++) {
                value = (max - min == 0) ? 0 : (get_pixel(im, j, i, c) - min) / (max - min);
                set_pixel(im, j, i, c, value);
            }
        }
    }
}

//     for (int i = 0;i < im.h;i++) {
//         for (int j = 0;j < im.w;j++) {
//             float v;
//             v = get_pixel(im, j, i, c) / sum;
//             set_pixel(im, j, i, c, v);
//         }

//     }
// }


image* sobel_image(image im)
{
    // TODO
    return calloc(2, sizeof(image));
}

image colorize_sobel(image im)
{
    // TODO
    return make_image(1, 1, 1);
}
