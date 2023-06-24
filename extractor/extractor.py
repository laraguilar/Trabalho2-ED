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

def read_descriptors(descriptor_filename):
    descriptors = []
    d_line = []
    array = []

    with open(descriptor_filename, "r") as fp:
        size = int(fp.readline().split()[0])
        i = 0
        
        while i < size:
            line = fp.readline()
            first = line[0]
            last = line[(len(line))-2:][0]

            if(first == "["):
                array = []
                d_line = []

                array = line[1:].split()

                for j in array:
                    d_line.append(np.float32(j))

            elif( last == "]"):
                array = line[:(len(line))-2].split()

                for j in array:
                    d_line.append(np.float32(j))
            
                descriptors.append(d_line)
                i += 1
            else:
                array = line.split()

                for j in array:
                    d_line.append(np.float32(j))
        print("Descritores lidos com sucesso!")
        
    return descriptors


def main(argv):

    sift = cv.SIFT_create()

    bf = cv.BFMatcher(cv.NORM_L2, crossCheck=True)

    img_name = sys.argv[1]
    descriptor_filename = sys.argv[2]

    img = cv.imread(img_name)
    img= cv.cvtColor(img, cv.COLOR_BGR2GRAY)

    keypoints_1, descriptors = sift.detectAndCompute(img, None)


    # write_file(descriptor_filename, descriptors)
    # soma = 0

    return 0

if __name__ == "__main__":
    main(sys.argv)


