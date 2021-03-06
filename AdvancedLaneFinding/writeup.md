## Advanced Lane Finding 

**Advanced Lane Finding Project**

The goals / steps of this project are the following:

* Compute the camera calibration matrix and distortion coefficients given a set of chessboard images.
* Apply a distortion correction to raw images.
* Use color transforms, gradients, etc., to create a thresholded binary image.
* Apply a perspective transform to rectify binary image ("birds-eye view").
* Detect lane pixels and fit to find the lane boundary.
* Determine the curvature of the lane and vehicle position with respect to center.
* Warp the detected lane boundaries back onto the original image.
* Output visual display of the lane boundaries and numerical estimation of lane curvature and vehicle position.

### Writeup / README

My code includes seven parts
1. Use the chess board images to calibration images
2. Undistort the image
3. Threshold the image using HLS and Magnitude/Direction of gradient  to find lanes.
4. Warp the image
5. Plot the lane
6. Measure the curvature
7. Use the video to test

#### 1. Camera Calibration

I use the chess images provided and findChessboardCorners function to detect corners. Then I am able to collect a number of corner points which will be used to do undistortion.
![Example1](https://github.com/baihongjie/selfdrivingcar/blob/master/AdvancedLaneFinding/writeup/chess1.png)
![Example2](https://github.com/baihongjie/selfdrivingcar/blob/master/AdvancedLaneFinding/writeup/chess2.png)

#### 2. Undistort images
Given a number of objpoints/imgpoints, it is straightforward to use cv2.calibrateCamera to calibrate the images. The output are camera matrix and distortant coefficients. By using them, we could easily undistort a real image.
![Example1](https://github.com/baihongjie/selfdrivingcar/blob/master/AdvancedLaneFinding/writeup/undistort1.png)
![Example2](https://github.com/baihongjie/selfdrivingcar/blob/master/AdvancedLaneFinding/writeup/undistort2.png)

#### 3. Threshold the image
There are many ways to threshold the image. I finally used HLS's S channel and sobelx+magnitude+direction on L channel. By only using S channel, it already works pretty well.  
![Example1](https://github.com/baihongjie/selfdrivingcar/blob/master/AdvancedLaneFinding/writeup/threshold1.png)
![Example2](https://github.com/baihongjie/selfdrivingcar/blob/master/AdvancedLaneFinding/writeup/threshold2.png)

#### 4. Warp the image
By using some heuristic src/dst points, we are able to warp the image into bird view. 
![Example1](https://github.com/baihongjie/selfdrivingcar/blob/master/AdvancedLaneFinding/writeup/warp1.png)
![Example2](https://github.com/baihongjie/selfdrivingcar/blob/master/AdvancedLaneFinding/writeup/warp2.png)


#### 5. Plot the lane and fit a polynomial
By using histogram peak algorithm, we could find the hot pixels along the lanes.
Then we use a polynomial to fit the lanes and then we usually could successfully find the two lanes.

![Example1](https://github.com/baihongjie/selfdrivingcar/blob/master/AdvancedLaneFinding/writeup/curve1.png)
![Example2](https://github.com/baihongjie/selfdrivingcar/blob/master/AdvancedLaneFinding/writeup/curve2.png)

#### 6. Measure the curvature
After fitting a polynomial, we could use simple formula to know the radius of the curvature and also we could easily know the distance between the center and the car.

![Example1](https://github.com/baihongjie/selfdrivingcar/blob/master/AdvancedLaneFinding/writeup/radius1.png)
![Example2](https://github.com/baihongjie/selfdrivingcar/blob/master/AdvancedLaneFinding/writeup/radius2.png)

#### 7. Sanity check
To make sure we don't cause accidents, I use a simple method to sanity check by comparing curvature of the two lanes. If their difference is higher than 60%, we reject this detection and reuse result of previous frame.

#### 8. Video

By putting these all together on a video
Here's a [result](output.mp4)

### Discussion
The biggest problem I have found is on the thresholding step. By simply using S channel, I could get very good result. However, to solve some other corner cases, I need to use other approaches. Without very good understanding on the theory, I have difficulty knowing which to choose and I could only rely on trying. After applying L of Luv and b of Lab, the thresholding step is much more stable for the base video.

The sanity check step is also very helpful because it is hard to guarantee we could always do a good job on every frame. Even if implementing a perfect sanity check is not easy, by using simple method with higher recall but lower precision, it works reasonably well.

Even if I have tuned a very good threshold for the base video, many thresholds failed on new videos such as "challenge_video". The failure is caused by more shadows, different sunshine, lighter color of lanes, etc. I will need to re-tune most of the parameters again. Also the refinished road sometimes have two colors and the separation part sometimes got detected as lanes. So I also need to make sure the detected lane are on appropriate position. I haven't been able to finish this part but I have clear picture on what changes I need to make.

