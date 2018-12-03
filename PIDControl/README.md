# CarND-Controls-PID
Self-Driving Car Engineer Nanodegree Program

---

## Implementation 

The implementation is very straightforward like this,
```
double steer = -Kp * cte - Kd * diff_cte - Ki * total_cte;
```
However, the parameter tuning is challenging. Due to the environment setup, it is a bit hard to apply method such as twiddle so I simply use manual tuning.

## Reflection

1. Jp: too small will make the car osillate too slowly and it will cause problem on curves. Too large will cause the car to overshoot and shaking around the center and sometimes the car may drive out of the way.
2. Jd: help to smooth the overshoot problem. Too small will not help enough with the overshoot and too large will make the car less sensitive to curves.
3. Ji: this should help with system bias but for the simulator it didn't seem to matter much.

The final parameter I chose is Jp=0.17, Jd=5, Ji=0. I started with an arbitrary initial value and increased it by small values, then I checked video to see how it goes (I sometimes use error value as a reference).
1. The car should not overshoot too obviouly.
2. The car should steer reasonably while on the curve.
The video is like this:
[video](https://github.com/baihongjie/selfdrivingcar/blob/master/PIDControl/result.mp4).
 
