# Object Tracking By Color With Distance Measurement By Polynomial Regression

> Name: Yuke Brilliant Hestiavin <br>
> Departement: Computer Engineering <br>
> Nrp: 5024241016

This project is related to the task as an intern software engineer in the Robotics UKM Research Team (IRIS) week 2, Computer Vision chapter.

- [Object Tracking By Color With Distance Measurement By Polynomial Regression](#object-tracking-by-color-with-distance-measurement-by-polynomial-regression)
  - [Demo](#demo)
  - [TO-DO: Implementing Polynomial Regression for Distance Calculation](#to-do-implementing-polynomial-regression-for-distance-calculation)
    - [Step 1: Data Collection](#step-1-data-collection)
    - [Step 2: Regression Analysis](#step-2-regression-analysis)
    - [Step 3: Code Implementation](#step-3-code-implementation)
    - [Step 4: Testing and Calibration](#step-4-testing-and-calibration)
  - [Current Progress](#current-progress)
  - [Next Steps](#next-steps)
  - [Dependencies](#dependencies)
  - [How to Use](#how-to-use)
    - [1. Installation](#1-installation)
    - [2. Usage](#2-usage)
  - [Calibration Data](#calibration-data)

## Demo

https://github.com/user-attachments/assets/e4524a0b-ffca-4f21-9e84-1798322f5573



## TO-DO: Implementing Polynomial Regression for Distance Calculation

### Step 1: Data Collection
- [x] Set up the camera in a fixed position
- [x] Prepare an object with known dimensions (preferably the same color as your tracking target)
- [x] Mark several distances on the floor (e.g., every 10cm from 10cm to 100cm)
- [x] Collect radius measurements at each distance point
- [x] Record at least 4 data pairs of radius (pixels) and actual distance (cm)

### Step 2: Regression Analysis
- [x] Use regression calculator (<a href="https://arachnoid.com/polysolve/">arachnoid.com</a>)
- [x] Input the collected data pairs
- [x] Set polynomial degree 

### Step 3: Code Implementation
- [x] Create calculateDistance() function using polynomial coefficients
- [x] Implement quadratic equation solver
- [ ] Add error handling for invalid radius values
- [ ] Add boundary checking for calculated distances
- [x] Integrate the function with the main tracking loop

### Step 4: Testing and Calibration
- [x] Test the system at known distances
- [ ] Calculate error margins
- [ ] Adjust coefficients if necessary
- [x] Document the accuracy at different distances

## Current Progress
- [x] Basic color tracking implemented
- [x] Contour detection working
- [x] Minimum enclosing circle calculation added

## Next Steps
- [x] Complete the polynomial regression implementation
- [x] Add detailed documentation
- [ ] Optimize for better accuracy

## Dependencies
- OpenCV 4.x
- C++ 11 or higher

## How to Use
### 1. Installation
Clone this repo
```bash
git clone https://github.com/yukebrillianth/opencv-object-tracking-with-distance-measurement.git distance-measuring

cd distance-measuring
```

Make a build directory
```bash
mkdir build
cd build
```

run cmake
```bash
cmake ..
```

### 2. Usage
compile before run the program
*(run in build directory)*
```bash
make
```
run the program
```bash
./DistanceMeasurement
```

## Calibration Data
```
Radius (pixels) | Distance (cm)
----------------|---------------
254             | 10
142             | 20
105             | 30
78              | 40
65              | 50
46              | 70

Mode: normal x,y analysis
Polynomial degree 3, 8 x,y data pairs.
Correlation coefficient = 0.9943957141940097
Standard error = 2.64455698786371

Output form: simple list (ordered x^0 to x^n):

 1.7015679224939916e+002
-2.8134763868498247e+000
 1.7367481282684945e-002
-3.4546683821398511e-005
```
