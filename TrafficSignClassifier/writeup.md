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

Here are five German traffic signs:

![Yield](https://github.com/baihongjie/selfdrivingcar/blob/master/TrafficSignClassifier/download1.jpg?raw=true)
![Stop](https://github.com/baihongjie/selfdrivingcar/blob/master/TrafficSignClassifier/download2.jpg?raw=true)
![Children crossing](https://github.com/baihongjie/selfdrivingcar/blob/master/TrafficSignClassifier/download3.jpg?raw=true)
![Slippery road](https://github.com/baihongjie/selfdrivingcar/blob/master/TrafficSignClassifier/download4.jpg?raw=true)
![Speed limit (80km/h)](https://github.com/baihongjie/selfdrivingcar/blob/master/TrafficSignClassifier/download5.jpg?raw=true)
![Stop](https://github.com/baihongjie/selfdrivingcar/blob/master/TrafficSignClassifier/download6.jpg?raw=true)
![Road work](https://github.com/baihongjie/selfdrivingcar/blob/master/TrafficSignClassifier/download7.jpg?raw=true)
![Speed limit (30km/h)](https://github.com/baihongjie/selfdrivingcar/blob/master/TrafficSignClassifier/download8.jpg?raw=true)
![No passing](https://github.com/baihongjie/selfdrivingcar/blob/master/TrafficSignClassifier/download9.jpg?raw=true)
![Speed limit (60km/h)](https://github.com/baihongjie/selfdrivingcar/blob/master/TrafficSignClassifier/download10.jpg?raw=true)
![Speed limit (100km/h)](https://github.com/baihongjie/selfdrivingcar/blob/master/TrafficSignClassifier/download11.jpg?raw=true)
![Pedestrians](https://github.com/baihongjie/selfdrivingcar/blob/master/TrafficSignClassifier/download12.jpg?raw=true)
![Keep right](https://github.com/baihongjie/selfdrivingcar/blob/master/TrafficSignClassifier/download13.jpg?raw=true)
![Go straight or right](https://github.com/baihongjie/selfdrivingcar/blob/master/TrafficSignClassifier/download14.jpg?raw=true)
![End of speed limit (80km/h)](https://github.com/baihongjie/selfdrivingcar/blob/master/TrafficSignClassifier/download15.jpg?raw=true)
![Ahead only](https://github.com/baihongjie/selfdrivingcar/blob/master/TrafficSignClassifier/download16.jpg?raw=true)

#### 2. Discuss the model's predictions on these new traffic signs and compare the results to predicting on the test set. At a minimum, discuss what the predictions were, the accuracy on these new predictions, and compare the accuracy to the accuracy on the test set (OPTIONAL: Discuss the results in more detail as described in the "Stand Out Suggestions" part of the rubric).

Here are the results of the prediction:

| Image			        |     Prediction	        					| 
|:---------------------:|:---------------------------------------------:| 
| Yield | Ahead only | 
| Stop | Stop 										|
| Children crossing | Speed limit (60km/h)											|
| Slippery road		      		| Slippery road |
| Speed limit (80km/h) | End of speed limit (80km/h) |

| Stop | No passing |
| Road work | Road work |
| Speed limit (30km/h) | Road work |
| No passing | No entry |
| Speed limit (60km/h) | Speed limit (60km/h) |

| Speed limit (100km/h) | Speed limit (80km/h) |
| Pedestrians | Turn left ahead |
| Keep right | Yield |
| Go straight or right | Go straight or right |
| End of speed limit (80km/h) | End of no passing by vehicles over 3.5 metric tons |
| Ahead only | Right-of-way at the next intersection |


The model was able to correctly guess 5 of the 16 traffic signs, which gives an accuracy of 31.25%.
This performs very bad compares to the accuracy on the test set of 91.6%.

By manually checking the result, it looks the model is unable to predict correctly when
1) the image is not centered well enough.
2) the image is twisted.
3) the image is squeezed.
4) the image is not clear after scaling.

Some image pre-processing such as cropping might be necessary to improve prediction.


#### 3. Describe how certain the model is when predicting on each of the five new images by looking at the softmax probabilities for each prediction. Provide the top 5 softmax probabilities for each image along with the sign type of each probability.

The code for making predictions on my final model is located in the last cell of the Ipython notebook.

For the first image, the model is relatively sure that this is a 'Ahead only' but it is a yield sign.
The top five soft max probabilities were

| Probability         	|     Prediction	        					| 
|:---------------------:|:---------------------------------------------:| 
| 32%         			| Ahead only| 
| 29%     				| Slippery road 										|
| 23%					| Go straight or right											|
| 11%	      			| Children crossing					 				|
| 7%				    | Yield     							|

etc
