![Doggo](https://github.com/shant1235/QuadDoggo/blob/main/photos/version2.JPG)
# QuadDoggo Project
 
QuadDoggo is a ongoing project where the main goal is to learn how to develop and design quadruped robots. QuadDoggo is a quadruped robot with enhanced mobility such as walking, squatting, and running. This project is currently in progress and designs are subject to change.
 
## Current Design 

The current design will use 8 DC motors in total (2 per leg) where each motor has a maximum torque of 4 Nm. I am currently building a single leg for testing to make sure that the robot can hold itself up. From there, I can calculate the maximum weight of my Doggo and design around that. Below is the current design of the leg that is being produced. 
### Current Progress (Programming and Reiteration) 
Currently, I'm having trouble programming in precise movement with Inverse Kinematics. Here is a quick display of my current progress with a Kp(High), Ki(Low), and Kd(Med).


https://user-images.githubusercontent.com/43391228/113493333-5bc73600-94ac-11eb-97a0-0ef73c14320b.mp4



As you can see, the movement is very imprecise, yet it still manages to make fluent movements due to the built in PID. To try and isolate the error, I have created another robot arm which is more mechanically reliable. Now I can focus solely on programming without worrying about belt tensioning, motor shaft play and space restrictions.  

![IMG_20210114_162804](https://user-images.githubusercontent.com/43391228/113493143-d7c07e80-94aa-11eb-819d-afaf7307742c.jpg)
![IMG_20210114_162743](https://user-images.githubusercontent.com/43391228/113493141-d68f5180-94aa-11eb-85fb-f96343788277.jpg)


### Wiring Diagram
![LegDiagram](https://github.com/shant1235/QuadDoggo/blob/main/photos/Leg%20diagram.png)

### Top view of Leg
![LegTop](https://github.com/shant1235/QuadDoggo/blob/main/photos/topViewLeg.JPG)

### Side view of Leg
![Leg](https://github.com/shant1235/QuadDoggo/blob/main/photos/sideViewLeg.JPG)
It uses belt pully system with a 1:1 teeth ratio to transfer motion throughout the Doggo's leg. The motors have already been geared down to 32 rpm which is why no additional speed reduction is needed.


### Prototype (Updated 10/13/2020)

Version 1 Test | Version 2 Test
:-------------:|:--------------:
![Servo Movement](https://github.com/shant1235/QuadDoggo/blob/main/photos/ServoTest.gif)  | ![DC Motor Movement](https://github.com/shant1235/QuadDoggo/blob/main/photos/V2Test.gif)

Notice how version 1 requires more torque since most of the motor weight is contained within the leg(I added the blue bag as more weight to keep the leg in place).
Now, notice how version 2 has less contained mass and requires less torque to manipulate. 

## Version 1 (Servo)

![Servo](https://github.com/shant1235/QuadDoggo/blob/main/photos/version1.JPG)

The first design of the QuadDoggo was created with servo-based joints. These joints proved to be too weak for the Doggo and therefore, the Doggo was redesigned to fit requirements.

### Prototype (Servo)

![Servo First Test](https://github.com/shant1235/QuadDoggo/blob/main/photos/ServoMovingTest.gif)

First time testing the leg with a Arduino. As you can see, I used a ton of tape to keep the assembly together.

## Support
If you have any question or concerns regards this project, please feel free to email me at prashant.mistry@ryerson.ca
