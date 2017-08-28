**Traffic Sign Recognition** 

**Build a Traffic Sign Recognition Project**

The goals of this project are the following:
* Load the data set
* Explore, summarize and visualize the data set
* Design, train and test a model architecture
* Use the model to make predictions on new images
* Analyze the softmax probabilities of the new images
* Summarize the results with a written report

## Rubric Points
### Here I will consider the [rubric points](https://review.udacity.com/#!/rubrics/481/view) individually and describe how I addressed each point in my implementation.  

---
### Writeup / README

#### 1. Provide a Writeup / README that includes all the rubric points and how you addressed each one. You can submit your writeup as markdown or pdf. You can use this template as a guide for writing the report. The submission includes the project code.

You're reading it! and here is a link to my [project code](https://github.com/baihongjie/selfdrivingcar/blob/master/TrafficSignClassifier/Traffic_Sign_Classifier.ipynb)

### Data Set Summary & Exploration

#### 1. Provide a basic summary of the data set. In the code, the analysis should be done using python, numpy and/or pandas methods rather than hardcoding results manually.

I used the pandas library to calculate summary statistics of the traffic
signs data set:

* The size of training set is 34799
* The size of the validation set is 4410
* The size of test set is 12630
* The shape of a traffic sign image is 32x32x3
* The number of unique classes/labels in the data set is 43

#### 2. Include an exploratory visualization of the dataset.

Here is an exploratory visualization of the data set.

![Sample image](https://github.com/baihongjie/selfdrivingcar/blob/master/TrafficSignClassifier/1.png?raw=true)
![Sample image](https://github.com/baihongjie/selfdrivingcar/blob/master/TrafficSignClassifier/2.png?raw=true)
![Sample image](https://github.com/baihongjie/selfdrivingcar/blob/master/TrafficSignClassifier/3.png?raw=true)
![Sample image](https://github.com/baihongjie/selfdrivingcar/blob/master/TrafficSignClassifier/4.png?raw=true)
![Sample image](https://github.com/baihongjie/selfdrivingcar/blob/master/TrafficSignClassifier/5.png?raw=true)

### Design and Test a Model Architecture

#### 1. Describe how you preprocessed the image data.

As a first step, I decided to convert the images to grayscale because this will reduce the noise of the features

Here is an example of a traffic sign image before and after grayscaling.

![Before grayscaling](https://github.com/baihongjie/selfdrivingcar/blob/master/TrafficSignClassifier/6.png?raw=true)
![After grayscaling](https://github.com/baihongjie/selfdrivingcar/blob/master/TrafficSignClassifier/7.png?raw=true)

As a last step, I normalized the image data because that make the algorithm numerically stable.

#### 2. Describe what your final model architecture looks like including model type, layers, layer sizes, connectivity, etc.) Consider including a diagram and/or table describing the final model.

My final model consisted of the following layers:

| Layer         		|     Description	        					| 
|:---------------------:|:---------------------------------------------:| 
| Input         		| 32x32x3 RGB image   							| 
| Convolution 5x5     	| 1x1 stride, valid padding, outputs 28x28x6 	|
| RELU					|												|
| Max pooling	      	| 2x2 stride,  outputs 14x14x6 				|
| Convolution 5x5     	| 1x1 stride, valid padding, outputs 10x10x16 	|
| RELU					|												|
| Max pooling	      	| 2x2 stride,  outputs 5x5x16 				|
| Flatten | outputs 400 				|
| Fully connected		| Output 120        									|
| RELU					|												|
| Fully connected		| Output 84        									|
| RELU					|												|
| Fully connected		| Output 43        									|
| Softmax				| etc.        									|


#### 3. Describe how you trained your model. The discussion can include the type of optimizer, the batch size, number of epochs and any hyperparameters such as learning rate.

To train the model, I used an softmax cross entropy as loss function.
I used AdamOptimizer with learning rate of 0.001
Epoch is set to 40 (only after 30 could I achieve 93% on validation dataset).

#### 4. Describe the approach taken for finding a solution and getting the validation set accuracy to be at least 0.93. 

My final model results were:
* training set accuracy of 0.999
* validation set accuracy of 0.932 
* test set accuracy of 0.918

* What architecture was chosen?
LENET
* Why did you believe it would be relevant to the traffic sign application?
It has been proved to be successful in most problems.
* How does the final model's accuracy on the training, validation and test set provide evidence that the model is working well?
The accuracy are all > 90% which means it is neither much overfitting or underfitting 
 

### Test a Model on New Images

#### 1. Choose five German traffic signs found on the web and provide them in the report. For each image, discuss what quality or qualities might be difficult to classify.

Here are sixteen German traffic signs:

![Yield](https://github.com/baihongjie/selfdrivingcar/blob/master/TrafficSignClassifier/download1.jpg?raw=true)
![Stop](https://github.com/baihongjie/selfdrivingcar/blob/master/TrafficSignClassifier/download2.jpg?raw=true)
![Children crossing](https://github.com/baihongjie/selfdrivingcar/blob/master/TrafficSignClassifier/download3.jpg?raw=true)
![Slippery road](https://github.com/baihongjie/selfdrivingcar/blob/master/TrafficSignClassifier/download4.jpg?raw=true)
![Speed limit (80km/h)](https://github.com/baihongjie/selfdrivingcar/blob/master/TrafficSignClassifier/download5.jpg?raw=true)
![Stop](https://github.com/baihongjie/selfdrivingcar/blob/master/TrafficSignClassifier/download6.jpg?raw=true)
![Road work](https://github.com/baihongjie/selfdrivingcar/blob/master/TrafficSignClassifier/download7.jpg?raw=true)
![Speed limit (30km/h)](https://github.com/baihongjie/selfdrivingcar/blob/master/TrafficSignClassifier/download8.jpg?raw=true)
![No entry](https://github.com/baihongjie/selfdrivingcar/blob/master/TrafficSignClassifier/download9.jpg?raw=true)
![Speed limit (60km/h)](https://github.com/baihongjie/selfdrivingcar/blob/master/TrafficSignClassifier/download10.jpg?raw=true)
![Speed limit (100km/h)](https://github.com/baihongjie/selfdrivingcar/blob/master/TrafficSignClassifier/download11.jpg?raw=true)
![Pedestrians](https://github.com/baihongjie/selfdrivingcar/blob/master/TrafficSignClassifier/download12.jpg?raw=true)
![Keep right](https://github.com/baihongjie/selfdrivingcar/blob/master/TrafficSignClassifier/download13.jpg?raw=true)
![Go straight or right](https://github.com/baihongjie/selfdrivingcar/blob/master/TrafficSignClassifier/download14.jpg?raw=true)
![End of speed limit (80km/h)](https://github.com/baihongjie/selfdrivingcar/blob/master/TrafficSignClassifier/download15.jpg?raw=true)
![Ahead only](https://github.com/baihongjie/selfdrivingcar/blob/master/TrafficSignClassifier/download16.jpg?raw=true)

#### 2. Discuss the model's predictions on these new traffic signs and compare the results to predicting on the test set. At a minimum, discuss what the predictions were, the accuracy on these new predictions, and compare the accuracy to the accuracy on the test set (OPTIONAL: Discuss the results in more detail as described in the "Stand Out Suggestions" part of the rubric).

Here are the results of the prediction:

| Image			        |     Prediction| image	        					| Difficulty | 
|:---------------------:|:---------------------------------------------:| :---------------------------------------------:|:---------------------------------------------:|
| Yield | Ahead only |![Yield](https://github.com/baihongjie/selfdrivingcar/blob/master/TrafficSignClassifier/download1.jpg?raw=true)|  Easy: Sign is on top half of the image|
| Stop | Stop | ![Stop](https://github.com/baihongjie/selfdrivingcar/blob/master/TrafficSignClassifier/download2.jpg?raw=true) |  Medium: Sign is twisted.  |
| Children crossing | Speed limit (60km/h) | ![Children crossing](https://github.com/baihongjie/selfdrivingcar/blob/master/TrafficSignClassifier/download3.jpg?raw=true) |  Difficult: Sign is squeezed after resizing to 32x32|
| Slippery road | Slippery road |![Slippery road](https://github.com/baihongjie/selfdrivingcar/blob/master/TrafficSignClassifier/download4.jpg?raw=true)  |  Easy|
| Speed limit (80km/h) | End of speed limit (80km/h) | ![Speed limit (80km/h)](https://github.com/baihongjie/selfdrivingcar/blob/master/TrafficSignClassifier/download5.jpg?raw=true)  | Medium: sign is squeezed a bit after resizing to 32x32. Also there is watermark.|
| Stop | No passing |![Stop](https://github.com/baihongjie/selfdrivingcar/blob/master/TrafficSignClassifier/download6.jpg?raw=true)  |  Easy. |
| Road work | Road work | ![Road work](https://github.com/baihongjie/selfdrivingcar/blob/master/TrafficSignClassifier/download7.jpg?raw=true) |  Medium: sign is squeezed after resizing to 32x32|
| Speed limit (30km/h) | Road work | ![Speed limit (30km/h)](https://github.com/baihongjie/selfdrivingcar/blob/master/TrafficSignClassifier/download8.jpg?raw=true)  | Medium: sign is squeezed after resizing to 32x32|
| No entry| No entry  | ![No passing](https://github.com/baihongjie/selfdrivingcar/blob/master/TrafficSignClassifier/download9.jpg?raw=true) |  Easy|
| Speed limit (60km/h) | Speed limit (60km/h) | ![Speed limit (60km/h)](https://github.com/baihongjie/selfdrivingcar/blob/master/TrafficSignClassifier/download10.jpg?raw=true)  | Easy|
| Speed limit (100km/h) | Speed limit (80km/h) |![Speed limit (100km/h)](https://github.com/baihongjie/selfdrivingcar/blob/master/TrafficSignClassifier/download11.jpg?raw=true)  |  Difficult: sign is squeezed after resizing to 32x32 and hard to recognize|
| Pedestrians | Turn left ahead | ![Pedestrians](https://github.com/baihongjie/selfdrivingcar/blob/master/TrafficSignClassifier/download12.jpg?raw=true) |  Medium: sign is squeezed after resizing to 32x32|
| Keep right | Yield |![Keep right](https://github.com/baihongjie/selfdrivingcar/blob/master/TrafficSignClassifier/download13.jpg?raw=true) |  Easy|
| Go straight or right | Go straight or right |![Go straight or right](https://github.com/baihongjie/selfdrivingcar/blob/master/TrafficSignClassifier/download14.jpg?raw=true) | Easy|
| End of speed limit (80km/h) | End of no passing by vehicles over 3.5 metric tons |![End of speed limit (80km/h)](https://github.com/baihongjie/selfdrivingcar/blob/master/TrafficSignClassifier/download15.jpg?raw=true) |  Easy|
| Ahead only | Right-of-way at the next intersection |![Ahead only](https://github.com/baihongjie/selfdrivingcar/blob/master/TrafficSignClassifier/download16.jpg?raw=true) | Easy|


The model was able to correctly guess 6 of the 16 traffic signs, which gives an accuracy of 37.5%.
This performs very bad compares to the accuracy on the test set of 91.6%.

By manually checking the result, it looks the model is unable to predict correctly when
1) the image is not centered well enough.
2) the image is twisted.
3) the image is squeezed.
4) some watermark caused noise.

Some image pre-processing such as cropping might be necessary to improve prediction.
Also 32x32 is too small as input to the model.
There are a few easy cases that model failed. Not sure what happened but probably the model is overfitting or not enough training data.


#### 3. Describe how certain the model is when predicting on each of the five new images by looking at the softmax probabilities for each prediction. Provide the top 5 softmax probabilities for each image along with the sign type of each probability.

The code for making predictions on my final model is located in the last cell of the Ipython notebook.

The top five soft max probabilities were

| Image			        |     Prediction| image	        					|
|:---------------------:|:---------------------------------------------:| :---------------------------------------------:|
| Yield | Ahead only:32.233814 Slippery road:29.019138 Go straight or right:23.781366 Children crossing:11.081440 Yield:7.378864|![Yield](https://github.com/baihongjie/selfdrivingcar/blob/master/TrafficSignClassifier/download1.jpg?raw=true)|
| Stop | Stop:19.771164 Turn right ahead:16.488478 Speed limit (70km/h):10.438532 Speed limit (50km/h):8.178452 Road work:4.927989 | ![Stop](https://github.com/baihongjie/selfdrivingcar/blob/master/TrafficSignClassifier/download2.jpg?raw=true) |
| Children crossing | Speed limit (60km/h):18.303318 Speed limit (30km/h):1.378690 Slippery road:-0.395384 Go straight or right:-0.665137 Ahead only:-1.444520 | ![Children crossing](https://github.com/baihongjie/selfdrivingcar/blob/master/TrafficSignClassifier/download3.jpg?raw=true) |
| Slippery road | Slippery road:28.816086 Right-of-way at the next intersection:18.833385 Dangerous curve to the left:18.032318 Double curve:17.156925 Beware of ice/snow:12.703184 |![Slippery road](https://github.com/baihongjie/selfdrivingcar/blob/master/TrafficSignClassifier/download4.jpg?raw=true)  |
| Speed limit (80km/h) | End of speed limit (80km/h):9.193988 Go straight or right:8.339031 Speed limit (30km/h):7.658392 Speed limit (80km/h):7.584309 Ahead only:-0.831196 | ![Speed limit (80km/h)](https://github.com/baihongjie/selfdrivingcar/blob/master/TrafficSignClassifier/download5.jpg?raw=true)  |
| Stop |No passing:18.239706 Yield:18.123661 No passing for vehicles over 3.5 metric tons:17.611416 Priority road:15.845152 Dangerous curve to the left:3.487552 |![Stop](https://github.com/baihongjie/selfdrivingcar/blob/master/TrafficSignClassifier/download6.jpg?raw=true)  |
| Road work | Road work:64.409065 Double curve:11.432398 Wild animals crossing:6.631978 Right-of-way at the next intersection:2.695795 Go straight or left:2.478613 | ![Road work](https://github.com/baihongjie/selfdrivingcar/blob/master/TrafficSignClassifier/download7.jpg?raw=true) |
| Speed limit (30km/h) | Road work:43.407940 Slippery road:31.630814 No passing for vehicles over 3.5 metric tons:12.144956 Ahead only:7.739809 Go straight or right:1.403698 | ![Speed limit (30km/h)](https://github.com/baihongjie/selfdrivingcar/blob/master/TrafficSignClassifier/download8.jpg?raw=true)  |
| No entry| No entry:35.333153 No passing:8.294834 Turn right ahead:7.610146 Yield:7.367533 Turn left ahead:4.408117 | ![No passing](https://github.com/baihongjie/selfdrivingcar/blob/master/TrafficSignClassifier/download9.jpg?raw=true) |
| Speed limit (60km/h) | Speed limit (60km/h):58.587658 Speed limit (30km/h):54.857620 Keep right:24.571083 Go straight or right:22.796919 Speed limit (50km/h):9.996917 | ![Speed limit (60km/h)](https://github.com/baihongjie/selfdrivingcar/blob/master/TrafficSignClassifier/download10.jpg?raw=true)  |
| Speed limit (100km/h) | Speed limit (80km/h):16.932646 End of speed limit (80km/h):14.084743 Speed limit (30km/h):12.356865 Speed limit (100km/h):10.574906 End of no passing by vehicles over 3.5 metric tons:8.505385 |![Speed limit (100km/h)](https://github.com/baihongjie/selfdrivingcar/blob/master/TrafficSignClassifier/download11.jpg?raw=true)  |
| Pedestrians | Turn left ahead:10.467297 Vehicles over 3.5 metric tons prohibited:8.581168 Roundabout mandatory:6.776857 No entry:5.037635 No passing:4.522285 | ![Pedestrians](https://github.com/baihongjie/selfdrivingcar/blob/master/TrafficSignClassifier/download12.jpg?raw=true) |
| Keep right | Yield:38.303062 Ahead only:24.338717 Dangerous curve to the left:21.610338 No passing for vehicles over 3.5 metric tons:7.026790 Road work:6.045825 |![Keep right](https://github.com/baihongjie/selfdrivingcar/blob/master/TrafficSignClassifier/download13.jpg?raw=true) |
| Go straight or right | Go straight or right:38.983105 Right-of-way at the next intersection:27.354635 Children crossing:14.081757 Turn left ahead:4.588902 End of all speed and passing limits:-1.635918 |![Go straight or right](https://github.com/baihongjie/selfdrivingcar/blob/master/TrafficSignClassifier/download14.jpg?raw=true) |
| End of speed limit (80km/h) | End of no passing by vehicles over 3.5 metric tons:13.752259 End of speed limit (80km/h):12.811898 End of all speed and passing limits:8.023116 Roundabout mandatory:6.100760 Speed limit (60km/h):5.698773 |![End of speed limit (80km/h)](https://github.com/baihongjie/selfdrivingcar/blob/master/TrafficSignClassifier/download15.jpg?raw=true) | 
| Ahead only | Right-of-way at the next intersection:23.175037 General caution:23.079329 Speed limit (30km/h):18.286972 Roundabout mandatory:11.118825 Pedestrians:7.036125 |![Ahead only](https://github.com/baihongjie/selfdrivingcar/blob/master/TrafficSignClassifier/download16.jpg?raw=true) | 



















