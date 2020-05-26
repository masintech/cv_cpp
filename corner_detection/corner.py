
from skimage.io import imread
from skimage.color import rgb2gray
import matplotlib.pyplot as plt
from scipy import ndimage as ndi
from skimage.feature import peak_local_max
from skimage.feature import corner_harris, corner_peaks

img = imread('church00.jpg')
imggray = rgb2gray(img)
from scipy import signal as sig
import numpy as np

def gradient_x(imggray):
    # Sobel operator kernels.
    kernel_x = np.array([[-1, 0, 1], [-2, 0, 2], [-1, 0, 1]])
    return sig.convolve2d(imggray, kernel_x, mode='same')


def gradient_y(imggray):
    kernel_y = np.array([[1, 2, 1], [0, 0, 0], [-1, -2, -1]])
    return sig.convolve2d(imggray, kernel_y, mode='same')


I_x = gradient_x(imggray)
I_y = gradient_y(imggray)

Ixx = ndi.gaussian_filter(I_x**2, sigma=1)
Ixy = ndi.gaussian_filter(I_y*I_x, sigma=1)
Iyy = ndi.gaussian_filter(I_y**2, sigma=1)

k = 0.05
# determinant
detA = Ixx * Iyy - Ixy ** 2
# trace
traceA = Ixx + Iyy
    
harris_response = detA - k * traceA ** 2


# for y in range(offset, height-offset):
#     for x in range(offset, width-offset):
#         Sxx = np.sum(Ixx[y-offset:y+1+offset, x-offset:x+1+offset])
#         Syy = np.sum(Iyy[y-offset:y+1+offset, x-offset:x+1+offset])
#         Sxy = np.sum(Ixy[y-offset:y+1+offset, x-offset:x+1+offset])



#Find determinant and trace, use to get corner response
# det = (Sxx * Syy) - (Sxy**2)
# trace = Sxx + Syy
# r = det - k*(trace**2)


img_copy_for_corners = np.copy(img)
img_copy_for_edges = np.copy(img)
for rowindex, response in enumerate(harris_response):
    for colindex, r in enumerate(response):
        if r > 0:
            # this is a corner
            img_copy_for_corners[rowindex, colindex] = [255,0,0]
        elif r < 0:
            # this is an edge
            img_copy_for_edges[rowindex, colindex] = [0,255,0]

corners = corner_peaks(harris_response)
fig, ax = plt.subplots()
ax.imshow(img, interpolation='nearest', cmap=plt.cm.gray)
ax.plot(corners[:, 1], corners[:, 0], '.r', markersize=3)
plt.show()


# def convolution2d(image, kernel, bias):
#     m, n = kernel.shape
#     if (m == n):
#         y, x = image.shape
#         y = y - m + 1
#         x = x - m + 1
#         new_image = np.zeros((y, x))
#         for i in range(y):
#             for j in range(x):
#                 new_image[i][j] = np.sum(image[i:i+m, j:j+m]*kernel) + bias
#     return new_image


