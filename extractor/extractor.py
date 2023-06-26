import sys
import numpy as np
import cv2 as cv
import matplotlib.pyplot as plt

def write_file(descriptor_filename, descriptors):
    with open(descriptor_filename, "w") as fp:
        fp.write(str(len(descriptors)) + " " + str(len(descriptors[0])) + "\n")
        for i in range(0, len(descriptors)):
            fp.write(str(descriptors[i]) + "\n")
    print("Descritores escritos com sucesso!")
    return 0

def main(argv):
    img_name = sys.argv[1]
    descriptor_filename = sys.argv[2]

    img = cv.imread(img_name, cv.COLOR_BGR2GRAY)

    sift = cv.SIFT_create()

    keypoints_1, descriptors = sift.detectAndCompute(img, None)

    write_file(descriptor_filename, descriptors)
    return 0

if __name__ == "__main__":
    main(sys.argv)
