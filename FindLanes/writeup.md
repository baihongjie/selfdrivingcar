# **Finding Lane Lines on the Road** 

### 1. Steps
My pipeline has one function which made slight modification of the class code.
Firstly, I converted the images to grey and used some library to blur it and find edges.
Secondly, I used a hand-tuned formula to find edges that are within interesting region.
Thirdly, I use HoughLines to find line segments. These line segments are almost the lanes. I slightly checked the slope of the line to make sure it is not horizonal or vertical to reduce noise.
Last, I merge the lanes with original image and output the video

### 2. Identify potential shortcomings with your current pipeline

The interesting region are very hard to define. The current manual tuned formula is super flaky.
There are a large number of noisy line segments which are not lanes. However, I could not find a better way to know which line segment is lane, I tried length but the dotted lane could be short. 


### 3. Suggest possible improvements to your pipeline

Extend the line segments and see if they connect to each other, if so, the longer line is most likely to be the lane.
