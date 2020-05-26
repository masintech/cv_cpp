import numpy as np
import pandas
import subprocess
import cv2 
# subprocess.call(['./build/detectObjects'])
eye_classifier = cv2.CascadeClassifier('/haarcascade_eye.xml')
