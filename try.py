from uwimg import *
im = load_image("data/dogsmall.jpg")
a = nn_resize(im, im.w*5, im.h*5)
save_image(a, "dog4x-nn")

im = load_image("data/dogsmall.jpg")
a = bilinear_resize(im, im.w*2, im.h*2)
save_image(a, "dog4x-bl")

im = load_image("data/dog.jpg")
f = make_box_filter(7)
blur = convolve_image(im, f, 1)
save_image(blur, "dog-box7")

im = load_image("data/dog.jpg")
f = make_highpass_filter()
blur = convolve_image(im, f, 1)

save_image(blur, "dog-highpass")

im = load_image("data/dog.jpg")
s = make_sharpen_filter();
sharp = convolve_image(im, s, 1)
save_image(sharp, "sharp")

im = load_image("data/dog.jpg")
e = make_emboss_filter()
blur = convolve_image(im, e, 1)
save_image(blur, "emboss")

im = load_image("dog-box.jpg")
f = make_gaussian_filter(2)
blur = convolve_image(im, f, 1)
save_image(blur, "dog-gauss")




# im = load_image("data/square.jpg")
# f = make_box_filter(7)
# blur = convolve_image(im, f, 1)
# thumb = nn_resize(blur, blur.w//2, blur.h//2)
# save_image(thumb, "dogthumb")
