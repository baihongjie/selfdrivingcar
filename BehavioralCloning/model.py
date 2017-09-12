import cv2
import csv
import numpy as np

lines = []
with open('data/driving_log.csv') as csvfile:
  reader = csv.reader(csvfile)
  for line in reader:
    lines.append(line)

images = []
measurements = []

def AddData(p, measurement):
  filename = p.split('/')[-1]
  current_path = 'data/IMG/' + filename
  image = cv2.imread(current_path)
  images.append(image)
  measurements.append(measurement)
  image_flipped = np.fliplr(image)
  measurement_flipped = -measurement
  images.append(image_flipped)
  measurements.append(measurement_flipped)

for line in lines:
  m = float(line[3])
  AddData(line[0], m)
  AddData(line[1], m+0.2)
  AddData(line[2], m-0.2)

X_train  = np.array(images)
y_train = np.array(measurements)

from keras.models import Sequential
from keras.layers import Flatten, Dense, Lambda
from keras.layers import Convolution2D
from keras.layers.pooling import MaxPooling2D
from keras.layers import Cropping2D
from keras.layers import Dropout

model = Sequential()
model.add(Lambda(lambda x: (x / 255.0) - 0.5, input_shape=(160,320,3)))
model.add(Cropping2D(cropping=((50,25), (0,0))))
model.add(Convolution2D(12, 5, 5, activation='relu'))
model.add(MaxPooling2D())
model.add(Convolution2D(24, 5, 5, activation='relu'))
model.add(MaxPooling2D())
model.add(Convolution2D(36, 5, 5, activation='relu'))
model.add(MaxPooling2D())
model.add(Flatten())
model.add(Dense(120))
model.add(Dropout(0.2))
model.add(Dense(84))
model.add(Dropout(0.2))
model.add(Dense(1))
model.compile(loss='mse', optimizer='adam')
model.fit(X_train, y_train, validation_split=0.2, shuffle=True, nb_epoch=3)
model.save('model.h5')
