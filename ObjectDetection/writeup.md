## Vehicle Detection Writeup 

**Vehicle Detection Project**

The goals / steps of this project are the following:

* Perform a Histogram of Oriented Gradients (HOG) feature extraction on a labeled training set of images and train a classifier Linear SVM classifier
* Optionally, you can also apply a color transform and append binned color features, as well as histograms of color, to your HOG feature vector. 
* Note: for those first two steps don't forget to normalize your features and randomize a selection for training and testing.
* Implement a sliding-window technique and use your trained classifier to search for vehicles in images.
* Run your pipeline on a video stream (start with the test_video.mp4 and later implement on full project_video.mp4) and create a heat map of recurring detections frame by frame to reject outliers and follow detected vehicles.
* Estimate a bounding box for vehicles detected.

---
### Writeup / README
My code includes the following parts
1. Extract HOG and spatial features
2. Train a SVM model using the features
3. Do Hog Sub-sampling Window Search on the images to classify
4. Use heatmap to reduce false positives
5. Repeat 1-4 on a video. Make sure the car consistently appear in multiple frames to reduce false positive. 

### Feature Extraction

I followed the udacity code to extract HOG and spartial features. The parameters are 
* color_space
* orient 
* pix_per_cell
* cell_per_block 
* hog_channel 
* spatial_size

Here is an example of extracted feature images.
![HOG feature example][https://github.com/baihongjie/selfdrivingcar/blob/master/ObjectDetection/hog_feature.png]

It is able to detect shape of the car which is essential for detection.
I didn't choose color histogram because it seems to cause some false positive in real image classification.

### SVM model

After extracting features, I randomly sample train set to 80% training and 20% testing.
It is very easy to get 97% accuracy. By tuning the parameters such as adding color histogram features, it could reach 98.5%.
However, the additional 1% accuracy doesn't always mean it will do a better job in real detection. I ended up choosing the following 
parameters which performed reasonable well in the video part.
* color_space = 'YCrCb'
* orient = 9
* pix_per_cell = 8
* cell_per_block = 2
* hog_channel = 'ALL'

Here is the output of the SVM training.
```
102.1 Seconds to extract HOG features...
Using: 9 orientations 8 pixels per cell and 2 cells per block
Feature vector length: 6060
18.47 Seconds to train SVC...
Test Accuracy of SVC =  0.9794
My SVC predicts:  [ 0.  1.  0.  0.  1.  0.  0.  1.  1.  0.]
For these 10 labels:  [ 0.  1.  0.  0.  1.  0.  0.  1.  0.  0.]
0.00175 Seconds to predict 10 labels with SVC
```

### HOG sub-sampling 

To optimize prediction, I precompute HOG features and use a slice window approach to find subimages which we classify.
We choose window position to be where the cars are most likely to appear and choose a few scales because we don't know 
the car size in the image.

![Good][https://github.com/baihongjie/selfdrivingcar/blob/master/ObjectDetection/detect1.png]

![Good][https://github.com/baihongjie/selfdrivingcar/blob/master/ObjectDetection/detect2.png]

However, sometimes there are glitches as below

![False positive][https://github.com/baihongjie/selfdrivingcar/blob/master/ObjectDetection/detect3.png]

### Reduce false positive
As we could see above, there are false positive very often. We use heatmap and only accept pixels which are covered by more than one or two blocks.
This greatly reduce the noise.
![With noise reduced][https://github.com/baihongjie/selfdrivingcar/blob/master/ObjectDetection/fixed1.png]

### Video Implementation

By putting these all together on a video, one additional step is necessary to further reduce false positives, I need to keep a history of last few detected frames. I only accept cars who appear in consecutive frames above a threshold. The final video is like 

[result](output.mp4)

### Discussion

The feature extraction is a bit tricky. The accuracy of the svm training doesn't mean it will do better on real problem.
So I have to use real problem to evaluate the model in additional to test set accuracy. 

Due to limitation of training data, there are always false positives. I need to use heuristic to reduce false positives. However, it is still a bit flaky.
Especially for the video, it either failed to detect car of caused false positives. 
I have to tune heavily on thresholds on heatmap and consecutive frames which a bit overfit the video.

Overall, I have successfully completed the task but some threshold tuning needs more careful further thoughts. 
