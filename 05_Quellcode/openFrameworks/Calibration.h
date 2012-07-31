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
	void showPreview();
	void setSrcPoints(float posXyellowSrc, float posYyellowSrc, float posXblueSrc, float posYblueSrc, float posXredSrc, float posYredSrc, float posXgreenSrc, float posYgreenSrc);
	void setDesPoints(float posXyellowDes, float posYyellowDes, float posXblueDes, float posYblueDes, float posXredDes, float posYredDes, float posXgreenDes, float posYgreenDes);

	
	IplImage* GetThresholdedImageYellow(IplImage* img);
	IplImage* GetThresholdedImageRed(IplImage* img);
	IplImage* GetThresholdedImageBlue(IplImage* img);
	IplImage* GetThresholdedImageGreen(IplImage* img);

	// initialize images for thresholded images (Marker = white, rest = black)
	IplImage* imgYellowThreshDes;
	IplImage* imgBlueThreshDes; 
	IplImage* imgRedThreshDes; 
	IplImage* imgGreenThreshDes; 
	
	IplImage* imgYellowThreshSrc;
	IplImage* imgBlueThreshSrc; 
	IplImage* imgRedThreshSrc; 
	IplImage* imgGreenThreshSrc; 
	
	//initialize moments for calculating moments of threshImages
	CvMoments *momentsyellowdes;
	CvMoments *momentsbluedes; 
	CvMoments *momentsreddes; 
	CvMoments *momentsgreendes; 
	
	CvMoments *momentsyellowsrc; 
	CvMoments *momentsbluesrc; 
	CvMoments *momentsredsrc; 
	CvMoments *momentsgreensrc; 
	
	IplImage* images[10];
	IplImage* markerImages[10];
	IplImage* previewImages[10];
	
	CvMat* map_matrix1;//[7];
	CvMat* map_matrix;

	//define Points-arrays
	CvPoint2D32f desPoints[4];
	CvPoint2D32f srcPoints[4];

	IplImage* desimage;
	IplImage* srcimage;
	IplImage* previewimage;
	
	// The actual moment values
	double moment10yellowdes;
	double moment10bluedes;
	double moment10reddes;
	double moment10greendes;

	double moment10yellowsrc;
	double moment10bluesrc;
	double moment10redsrc;
	double moment10greensrc;

	
	double moment01yellowdes;
	double moment01bluedes;
	double moment01reddes;
	double moment01greendes;
	
	double moment01yellowsrc;
	double moment01bluesrc;
	double moment01redsrc;
	double moment01greensrc;

	double areayellowdes;
	double areabluedes;
	double areareddes;
	double areagreendes;
	
	double areayellowsrc;
	double areabluesrc;
	double arearedsrc;
	double areagreensrc;
	
	// Holding the last and current marker positions and placing them into a CvPoint Vector
	float posXyellowDes;
	float posYyellowDes;
	
	float posXblueDes;
	float posYblueDes;
	
	float posXredDes;
	float posYredDes;
	
	float posXgreenDes;
	float posYgreenDes;
	
	
	float posXyellowSrc;
	float posYyellowSrc;
	
	float posXblueSrc;
	float posYblueSrc;
	
	float posXredSrc;
	float posYredSrc;
	
	float posXgreenSrc;
	float posYgreenSrc;
	
};