# Object Tracking By Color With Distance Measurement By Polynomial Regression

> Name: Yuke Brilliant Hestiavin <br>
> Departement: Computer Engineering <br>
> Nrp: 5024241016

This project is related to the task as an intern software engineer in the Robotics UKM Research Team (IRIS) week 2, Computer Vision chapter.

- [Object Tracking By Color With Distance Measurement By Polynomial Regression](#object-tracking-by-color-with-distance-measurement-by-polynomial-regression)
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

## TO-DO: Implementing Polynomial Regression for Distance Calculation

### Step 1: Data Collection
- [ ] Set up the camera in a fixed position
- [ ] Prepare an object with known dimensions (preferably the same color as your tracking target)
- [ ] Mark several distances on the floor (e.g., every 20cm from 20cm to 300cm)
- [ ] Collect radius measurements at each distance point
- [ ] Record at least 4 data pairs of radius (pixels) and actual distance (cm)

### Step 2: Regression Analysis
- [ ] Use regression calculator (<a href="https://arachnoid.com/polysolve/">arachnoid.com</a>)
- [ ] Input the collected data pairs
- [ ] Set polynomial degree 

### Step 3: Code Implementation
- [ ] Create calculateDistance() function using polynomial coefficients
- [ ] Implement quadratic equation solver
- [ ] Add error handling for invalid radius values
- [ ] Add boundary checking for calculated distances
- [ ] Integrate the function with the main tracking loop

### Step 4: Testing and Calibration
- [ ] Test the system at known distances
- [ ] Calculate error margins
- [ ] Adjust coefficients if necessary
- [ ] Document the accuracy at different distances

## Current Progress
- [x] Basic color tracking implemented
- [x] Contour detection working
- [x] Minimum enclosing circle calculation added

## Next Steps
- [ ] Complete the polynomial regression implementation
- [ ] Add detailed documentation
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
200             | 22
250             | 25
270             | 27
280             | 28

Polynomial Coefficients:
x^0: 3.4606265574937240e+001
x^1: -1.6201495194018822e-001
x^2: 4.9483802064790900e-004

Correlation coefficient: 0.9996948583634548
Standard error: 0.05660377358491015
```