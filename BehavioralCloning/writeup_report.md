#**Behavioral Cloning** 

**Behavioral Cloning Project**

The goals / steps of this project are the following:
* Use the simulator to collect data of good driving behavior
* Build, a convolution neural network in Keras that predicts steering angles from images
* Train and validate the model with a training and validation set
* Test that the model successfully drives around track one without leaving the road
* Summarize the results with a written report

## Rubric Points
####1. Submission includes all required files and can be used to run the simulator in autonomous mode

My project includes the following files:
* model.py containing the script to create and train the model
* drive.py for driving the car in autonomous mode
* model.h5 containing a trained convolution neural network 
* writeup_report.md summarizing the results

####2. Submission includes functional code
Using the Udacity provided simulator and my drive.py file, the car can be driven autonomously around the track by executing 
```sh
python drive.py model.h5
```

####3. Submission code is usable and readable

The model.py file contains the code for training and saving the convolution neural network. The file shows the pipeline I used for training and validating the model, and it contains comments to explain how the code works.

###Model Architecture and Training Strategy

####1. Model Architecture 

My model consists of a convolution neural network similar to LENET 
* Firstly, I normalized the data by dividing by 255
* To reduce noise, I crop the data on lower half which is the core part for learning to make driving decisions
* Then I used convolution layer with 12 filters and 5x5 kernel size followed by relu activation; then it is following by max pooling
* Repeat above convolution again using 24 filters.
* Repeat above convolution again using 36 filters.
* Using 120 fully connected layer followed by 0.2 drop out rate.
* Using 84 fully connected layer followed by 0.2 drop out rate.
* Repeat above with 84 fully connected layer.
* output

####2. Reduce overfitting in the model

By using cropping and dropout, overfitting should be alleviated.

####3. Model parameter tuning

The model used an adam optimizer, so the learning rate was not tuned manually.
I chose epoch=10 because loss doesn't decrease as much after 10 and increasing it might cause overfitting.

####4. Training data

To increase training data, I did
* Flip the image and flip the steering value
* Make camera take center/left/right image with steering value slightly adjusted for left/right

After the collection process, I had 20832 number of data points.
I finally randomly shuffled the data set and put 20% of the data into a validation set. 

####5. Result
After training the model, I used drive.py to test it on simulator. The driving works almost perfectly at the beginning! However, when it reached a curve where there is no clear lane, it drove off the road and went into the soil land.
After investigating, I think it is because the training data has too few such data. I decided to recollect training data. I drove 5 laps instead of 2 and clicked steering button strongly during that part of the road.
However, other problems happen: the car drove into the river. I tried a lot and ended up adding more convolution layers and tuning drop out which finally made the driving great.
