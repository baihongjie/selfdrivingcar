#**Traffic Sign Recognition** 

**Build a Traffic Sign Recognition Project**

The goals of this project are the following:
* Load the data set
* Explore, summarize and visualize the data set
* Design, train and test a model architecture
* Use the model to make predictions on new images
* Analyze the softmax probabilities of the new images
* Summarize the results with a written report

## Rubric Points
###Here I will consider the [rubric points](https://review.udacity.com/#!/rubrics/481/view) individually and describe how I addressed each point in my implementation.  

---
###Writeup / README

####1. Provide a Writeup / README that includes all the rubric points and how you addressed each one. You can submit your writeup as markdown or pdf. You can use this template as a guide for writing the report. The submission includes the project code.

You're reading it! and here is a link to my [project code](https://github.com/udacity/CarND-Traffic-Sign-Classifier-Project/blob/master/Traffic_Sign_Classifier.ipynb)

###Data Set Summary & Exploration

####1. Provide a basic summary of the data set. In the code, the analysis should be done using python, numpy and/or pandas methods rather than hardcoding results manually.

I used the pandas library to calculate summary statistics of the traffic
signs data set:

* The size of training set is 34799
* The size of the validation set is 4410
* The size of test set is 12630
* The shape of a traffic sign image is 32x32x3
* The number of unique classes/labels in the data set is 43

####2. Include an exploratory visualization of the dataset.

Here is an exploratory visualization of the data set.

![Sample image][https://github.com/baihongjie/selfdrivingcar/blob/master/TrafficSignClassifier/1.png?raw=true]
![Sample image][https://github.com/baihongjie/selfdrivingcar/blob/master/TrafficSignClassifier/2.png?raw=true]
![Sample image][https://github.com/baihongjie/selfdrivingcar/blob/master/TrafficSignClassifier/3.png?raw=true]
![Sample image][https://github.com/baihongjie/selfdrivingcar/blob/master/TrafficSignClassifier/4.png?raw=true]
![Sample image][https://github.com/baihongjie/selfdrivingcar/blob/master/TrafficSignClassifier/5.png?raw=true]

###Design and Test a Model Architecture

####1. Describe how you preprocessed the image data. What techniques were chosen and why did you choose these techniques? Consider including images showing the output of each preprocessing technique. Pre-processing refers to techniques such as converting to grayscale, normalization, etc. (OPTIONAL: As described in the "Stand Out Suggestions" part of the rubric, if you generated additional data for training, describe why you decided to generate additional data, how you generated the data, and provide example images of the additional data. Then describe the characteristics of the augmented training set like number of images in the set, number of images for each class, etc.)

As a first step, I decided to convert the images to grayscale because this will reduce the noise of the features

Here is an example of a traffic sign image before and after grayscaling.

![Before grayscaling][https://github.com/baihongjie/selfdrivingcar/blob/master/TrafficSignClassifier/6.png?raw=true]
![After grayscaling][https://github.com/baihongjie/selfdrivingcar/blob/master/TrafficSignClassifier/7.png?raw=true]

As a last step, I normalized the image data because that make the algorithm numerically stable.

####2. Describe what your final model architecture looks like including model type, layers, layer sizes, connectivity, etc.) Consider including a diagram and/or table describing the final model.

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


####3. Describe how you trained your model. The discussion can include the type of optimizer, the batch size, number of epochs and any hyperparameters such as learning rate.

To train the model, I used an softmax cross entropy as loss function.
I used AdamOptimizer with learning rate of 0.001
Epoch is set to 40 (only after 30 could I achieve 93% on validation dataset).

####4. Describe the approach taken for finding a solution and getting the validation set accuracy to be at least 0.93. Include in the discussion the results on the training, validation and test sets and where in the code these were calculated. Your approach may have been an iterative process, in which case, outline the steps you took to get to the final solution and why you chose those steps. Perhaps your solution involved an already well known implementation or architecture. In this case, discuss why you think the architecture is suitable for the current problem.

My final model results were:
* training set accuracy of 1.0
* validation set accuracy of 0.942 
* test set accuracy of 0.916

If a well known architecture was chosen:
* What architecture was chosen?
LENET
* Why did you believe it would be relevant to the traffic sign application?
It has been proved to be successful in most problems.
* How does the final model's accuracy on the training, validation and test set provide evidence that the model is working well?
The accuracy are all > 90% which means it is neither much overfitting or underfitting 
 

###Test a Model on New Images

####1. Choose five German traffic signs found on the web and provide them in the report. For each image, discuss what quality or qualities might be difficult to classify.

Here are five German traffic signs:

![Vehicles over 3.5 metric tons prohibited][https://github.com/baihongjie/selfdrivingcar/blob/master/TrafficSignClassifier/8.png?raw=true]
![Speed limit (30km/h)][https://github.com/baihongjie/selfdrivingcar/blob/master/TrafficSignClassifier/9.png?raw=true]
![Keep right][https://github.com/baihongjie/selfdrivingcar/blob/master/TrafficSignClassifier/10.png?raw=true]
![Turn right ahead][https://github.com/baihongjie/selfdrivingcar/blob/master/TrafficSignClassifier/11.png?raw=true]
![Right-of-way at the next intersection][https://github.com/baihongjie/selfdrivingcar/blob/master/TrafficSignClassifier/12.png?raw=true]


####2. Discuss the model's predictions on these new traffic signs and compare the results to predicting on the test set. At a minimum, discuss what the predictions were, the accuracy on these new predictions, and compare the accuracy to the accuracy on the test set (OPTIONAL: Discuss the results in more detail as described in the "Stand Out Suggestions" part of the rubric).

Here are the results of the prediction:

| Image			        |     Prediction	        					| 
|:---------------------:|:---------------------------------------------:| 
| Stop Sign      		| Stop sign   									| 
| U-turn     			| U-turn 										|
| Yield					| Yield											|
| 100 km/h	      		| Bumpy Road					 				|
| Slippery Road			| Slippery Road      							|


The model was able to correctly guess 5 of the 5 traffic signs, which gives an accuracy of 100%. This compares favorably to the accuracy on the test set of 91.6%

####3. Describe how certain the model is when predicting on each of the five new images by looking at the softmax probabilities for each prediction. Provide the top 5 softmax probabilities for each image along with the sign type of each probability. (OPTIONAL: as described in the "Stand Out Suggestions" part of the rubric, visualizations can also be provided such as bar charts)

The code for making predictions on my final model is located in the 11th cell of the Ipython notebook.

For the first image, the model is relatively sure that this is a 'Vehicles over 3.5 metric tons prohibited', and the image does contain a stop sign. The top five soft max probabilities were

| Probability         	|     Prediction	        					| 
|:---------------------:|:---------------------------------------------:| 
| 52%         			| Vehicles over 3.5 metric tons prohibited| 
| 17%     				| No passing 										|
| 12%					| Roundabout mandatory											|
| 11%	      			| Speed limit (100km/h)					 				|
| 8%				    | Speed limit (120km/h)     							|

etc
