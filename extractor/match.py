import sys
import numpy as np
import cv2 as cv
import matplotlib.pyplot as plt

# iterate the descriptor and return it as a numpy list
def read_descriptors(descriptor_filename):
    descriptors = []
    d_line = []
    l = []

    with open(descriptor_filename, "r") as fp:
        size = int(fp.readline().split()[0])
        i = 0
        while i < size:
            line = fp.readline()
            first = line[0]
            last = line[(len(line))-2:][0]

            if(first == "["):
                l = []
                d_line = []
                l = line[1:].split()
                for j in l:
                    d_line.append(np.float32(j))
            elif( last == "]"):
                l = line[:(len(line))-2].split()
                for j in l:
                    d_line.append(np.float32(j))
                descriptors.append(np.float32(d_line))
                i += 1
            else:
                l = line.split()
                for j in l:
                    d_line.append(np.float32(j))
    return descriptors


def main(argv):
    descriptor_path1 = sys.argv[1]
    descriptor_path2 = sys.argv[2]

    descriptor1 = np.array(read_descriptors(descriptor_path1))    
    descriptor2 = np.array(read_descriptors(descriptor_path2))

    # make the match of the images 
    bf = cv.BFMatcher()
    matches = bf.knnMatch(descriptor1, descriptor2, k=2)

    # filter the score of similarity between the two descriptors
    good_matches = []
    for m, n in matches:
        if m.distance < 0.75 * n.distance:
            good_matches.append([m])

    # get the number of good matches
    n_matches = len(good_matches)

    # write the number of matches into a file for get them on the C program
    with open("query/matches", "wt") as fp:
        fp.write(str(n_matches))

    return n_matches

if __name__ == "__main__":
    main(sys.argv)