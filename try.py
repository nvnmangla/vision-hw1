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
h = make_highpass_filter()
blur = convolve_image(im, h, 1)
feature_normalize(blur)
save_image(blur, "dog-highpass")

im = load_image("data/dog.jpg")
s = make_sharpen_filter()
sharp = convolve_image(im, s, 1)
feature_normalize(sharp)
save_image(sharp, "sharp")


im = load_image("data/dog.jpg")
e = make_emboss_filter()
g = make_gaussian_filter(2)
blur = convolve_image(im, e, 1)
feature_normalize(blur)
save_image(blur, "emboss")

im = load_image("data/dog.jpg")
f = make_gaussian_filter(2)
blur = convolve_image(im, f, 1)
save_image(blur, "dog-gauss")


im = load_image("data/dog.jpg")
f = make_gaussian_filter(2)
lfreq = convolve_image(im, f, 1)
hfreq = sub_image(im,lfreq)
reconstruct = add_image(lfreq,hfreq)
save_image(lfreq, "low-frequency")
save_image(hfreq, "high-frequency")
save_image(reconstruct, "reconstruct")

im = load_image("data/forest.jpg")
res = sobel_image(im)
mag = res[0]
angle = res[1]
feature_normalize(mag)
feature_normalize(angle)
save_image(mag, "magnitude")
save_image(angle, "gradient")

im = load_image("data/forest.jpg")
res = colorize_sobel(im)
feature_normalize(res)
save_image(res, "magnitude_color")
