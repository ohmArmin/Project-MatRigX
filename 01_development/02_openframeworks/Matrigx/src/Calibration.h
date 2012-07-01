/*
 *  Calibration.h
 *  emptyExample
 *
 *  Created by Armin Voit on 29.06.12.
 *  Copyright 2012 __MyCompanyName__. All rights reserved.
 *
 */

#include "opencv2/highgui/highgui_c.h"
#include "opencv2/opencv.hpp"

#include "math.h"
#include <stdlib.h>
#include <stdio.h>
#include <string.h>

class Calibration{

public:
	void doCalibration();
	
	
private:
	IplImage* GetThresholdedImageYellow(IplImage* img);
	IplImage* GetThresholdedImageRed(IplImage* img);
	IplImage* GetThresholdedImageBlue(IplImage* img);
	IplImage* GetThresholdedImageGreen(IplImage* img);



};