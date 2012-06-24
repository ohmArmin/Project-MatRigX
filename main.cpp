#include "cv.h"
#include "highgui.h"
#include "math.h"
#include <stdlib.h>
#include <stdio.h>
#include <string.h>


// To filter for Yellow
IplImage* GetThresholdedImageYellow(IplImage* img)
{
	// Convert the image into an HSV image
    IplImage* imgHSV = cvCreateImage(cvGetSize(img), 8, 3);
    cvCvtColor(img, imgHSV, CV_BGR2HSV);

IplImage* imgThreshed = cvCreateImage(cvGetSize(img), 8, 1);

cvInRangeS(imgHSV, cvScalar(20, 100, 150), cvScalar(30, 255, 255), imgThreshed);
	
	//erode and dilate imgTreshed
	cvErode(imgThreshed , imgThreshed, NULL, 1);
	cvDilate(imgThreshed, imgThreshed, NULL, 1);

    cvReleaseImage(&imgHSV);
    return imgThreshed;
}


// To filter for Green
IplImage* GetThresholdedImageGreen(IplImage* img)
{
	// Convert the image into an HSV image
    IplImage* imgHSV = cvCreateImage(cvGetSize(img), 8, 3);
    cvCvtColor(img, imgHSV, CV_BGR2HSV);
	
	IplImage* imgThreshed = cvCreateImage(cvGetSize(img), 8, 1);
	
	cvInRangeS(imgHSV, cvScalar(40, 80, 80), cvScalar(80, 255, 255), imgThreshed);
	
	//erode and dilate imgTreshed
	cvErode(imgThreshed , imgThreshed, NULL, 1);
	cvDilate(imgThreshed, imgThreshed, NULL, 1);
	
    cvReleaseImage(&imgHSV);
    return imgThreshed;
}



// To filter for Blue
IplImage* GetThresholdedImageBlue(IplImage* img)
{
	// Convert the image into an HSV image
    IplImage* imgHSV = cvCreateImage(cvGetSize(img), 8, 3);
    cvCvtColor(img, imgHSV, CV_BGR2HSV);
	
	IplImage* imgThreshed = cvCreateImage(cvGetSize(img), 8, 1);
	
	cvInRangeS(imgHSV, cvScalar(100, 90, 90), cvScalar(125, 255, 255), imgThreshed);
	
	//erode and dilate imgTreshed
	//cvDilate(imgThreshed, imgThreshed, NULL, 1);
	cvErode(imgThreshed , imgThreshed, NULL, 1);
	cvDilate(imgThreshed, imgThreshed, NULL, 1);
	
	
    cvReleaseImage(&imgHSV);
    return imgThreshed;
}


// To filter for Red 
IplImage* GetThresholdedImageRed(IplImage* img)
{
	// Convert the image into an HSV image
    IplImage* imgHSV = cvCreateImage(cvGetSize(img), 8, 3);
    cvCvtColor(img, imgHSV, CV_BGR2HSV);
	
	IplImage* imgThreshed = cvCreateImage(cvGetSize(img), 8, 1);
	
	cvInRangeS(imgHSV, cvScalar(160, 170, 110), cvScalar(185, 255, 255), imgThreshed);
	
	//erode and dilate imgTreshed
	cvErode(imgThreshed , imgThreshed, NULL, 1);
	cvDilate(imgThreshed, imgThreshed, NULL, 1);
	
    cvReleaseImage(&imgHSV);
    return imgThreshed;
}

int main()
{	
	//Initialize Iteration counter (=number of images to be compared)
	int counter = 3;
	
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
	
	momentsyellowdes = (CvMoments*)malloc(sizeof(CvMoments));
	momentsbluedes = (CvMoments*)malloc(sizeof(CvMoments));
	momentsreddes = (CvMoments*)malloc(sizeof(CvMoments));
	momentsgreendes = (CvMoments*)malloc(sizeof(CvMoments));
	
	momentsyellowsrc = (CvMoments*)malloc(sizeof(CvMoments));
	momentsbluesrc = (CvMoments*)malloc(sizeof(CvMoments));
	momentsredsrc = (CvMoments*)malloc(sizeof(CvMoments));
	momentsgreensrc = (CvMoments*)malloc(sizeof(CvMoments));
	
	//define Image array and load calibration images
	
	IplImage* images[7];
	
	for (int i=1; i<=counter; i++) {
		
		char buffer[33];
		sprintf(buffer, "./MarkerPics/src%d.jpg", i);
		images[i] = cvLoadImage(buffer);
		//images[i] = cvLoadImage("./MarkerPics/src2.jpg");
	}
	
	
	
	
	//define map_Matrices to fill with Transform Matrix
	CvMat* map_matrix1[7];
	
	for (int i=1; i<=counter; i++) {
		
		map_matrix1[i] = cvCreateMat(3,3, CV_32FC1);
	}
	

	//map_matrix = cvCreateMat(2, 3, CV_32FC1);
	
	
	
	//define Points-arrays
	CvPoint2D32f desPoints[4];
	CvPoint2D32f srcPoints[4];
	
	
	
	//Load destination Image and define srcimage
	IplImage* desimage = cvLoadImage("./MarkerPics/des.jpg");
	
	IplImage* srcimage;
	
			
	
    // Couldn't get a image? Throw an error and quit
    if(!desimage)
    {
        printf("Could not initialize desimage...\n");
        return -1;
    }
		
	

	for (int i =1; i<=counter; i++) {

		// The two windows we'll be using
		/*cvNamedWindow("Image");
		cvNamedWindow("yellowMarker");
		cvNamedWindow("blueMarker");
		cvNamedWindow("redMarker");
		cvNamedWindow("greenMarker");*/
		
		//Load Images for mapping
		srcimage = images[i];
		
		// Couldn't get a image? Throw an error and quit
		if(!srcimage)
		{
			printf("Could not initialize srcimage...\n");
			return -1;
		}

		// Holds the thresholded images (Marker = white, rest = black)
        imgYellowThreshDes = GetThresholdedImageYellow(desimage);
		imgBlueThreshDes = GetThresholdedImageBlue(desimage);
		imgRedThreshDes = GetThresholdedImageRed(desimage);
		imgGreenThreshDes = GetThresholdedImageGreen(desimage);
		
		imgYellowThreshSrc = GetThresholdedImageYellow(srcimage);
		imgBlueThreshSrc = GetThresholdedImageBlue(srcimage);
		imgRedThreshSrc = GetThresholdedImageRed(srcimage);
		imgGreenThreshSrc = GetThresholdedImageGreen(srcimage); 

		// Calculate the moments to estimate the position of the markers
	
        cvMoments(imgYellowThreshDes, momentsyellowdes, 1);
		cvMoments(imgBlueThreshDes, momentsbluedes, 1);
		cvMoments(imgRedThreshDes, momentsreddes, 1);
		cvMoments(imgGreenThreshDes, momentsgreendes, 1);
	
		cvMoments(imgYellowThreshSrc, momentsyellowsrc, 1);
		cvMoments(imgBlueThreshSrc, momentsbluesrc, 1);
		cvMoments(imgRedThreshSrc, momentsredsrc, 1);
		cvMoments(imgGreenThreshSrc, momentsgreensrc, 1);
		
        // The actual moment values
        double moment10yellowdes = cvGetSpatialMoment(momentsyellowdes, 1, 0);
        double moment01yellowdes = cvGetSpatialMoment(momentsyellowdes, 0, 1);
        double areayellowdes = cvGetCentralMoment(momentsyellowdes, 0, 0);
	
		double moment10bluedes = cvGetSpatialMoment(momentsbluedes, 1, 0);
		double moment01bluedes = cvGetSpatialMoment(momentsbluedes, 0, 1);
		double areabluedes = cvGetCentralMoment(momentsbluedes, 0, 0);
	
		double moment10reddes = cvGetSpatialMoment(momentsreddes, 1, 0);
		double moment01reddes = cvGetSpatialMoment(momentsreddes, 0, 1);
		double areareddes = cvGetCentralMoment(momentsreddes, 0, 0);
	
		double moment10greendes = cvGetSpatialMoment(momentsgreendes, 1, 0);
		double moment01greendes = cvGetSpatialMoment(momentsgreendes, 0, 1);
		double areagreendes = cvGetCentralMoment(momentsgreendes, 0, 0);
	
		double moment10yellowsrc = cvGetSpatialMoment(momentsyellowsrc, 1, 0);
		double moment01yellowsrc = cvGetSpatialMoment(momentsyellowsrc, 0, 1);
		double areayellowsrc = cvGetCentralMoment(momentsyellowsrc, 0, 0);
	
		double moment10bluesrc = cvGetSpatialMoment(momentsbluesrc, 1, 0);
		double moment01bluesrc = cvGetSpatialMoment(momentsbluesrc, 0, 1);
		double areabluesrc = cvGetCentralMoment(momentsbluesrc, 0, 0);
	
		double moment10redsrc = cvGetSpatialMoment(momentsredsrc, 1, 0);
		double moment01redsrc = cvGetSpatialMoment(momentsredsrc, 0, 1);
		double arearedsrc = cvGetCentralMoment(momentsredsrc, 0, 0);
	
		double moment10greensrc = cvGetSpatialMoment(momentsgreensrc, 1, 0);
		double moment01greensrc = cvGetSpatialMoment(momentsgreensrc, 0, 1);
		double areagreensrc = cvGetCentralMoment(momentsgreensrc, 0, 0);

        // Holding the last and current marker positions and placing them into a Point Vector
		float posXyellowDes = 0;
		float posYyellowDes = 0;
	
		float posXblueDes = 0;
		float posYblueDes = 0;
	
		float posXredDes = 0;
		float posYredDes = 0;
	
		float posXgreenDes = 0;
		float posYgreenDes = 0;
		
        posXyellowDes = moment10yellowdes/areayellowdes;
        posYyellowDes = moment01yellowdes/areayellowdes;
	
		posXblueDes = moment10bluedes/areabluedes;
		posYblueDes = moment01bluedes/areabluedes;
	
		posXredDes = moment10reddes/areareddes;
		posYredDes = moment01reddes/areareddes;
	
		posXgreenDes = moment10greendes/areagreendes;
		posYgreenDes = moment01greendes/areagreendes;
	
		desPoints[0].x = posXyellowDes;
		desPoints[0].y = posYyellowDes;
		desPoints[1].x = posXblueDes;
		desPoints[1].y = posYblueDes;
		desPoints[2].x = posXredDes;
		desPoints[2].y = posYredDes;
		desPoints[3].x = posXgreenDes;
		desPoints[3].y = posYgreenDes;
	
	
		float posXyellowSrc = 0;
		float posYyellowSrc = 0;
		
		float posXblueSrc = 0;
		float posYblueSrc = 0;
	
		float posXredSrc = 0;
		float posYredSrc = 0;
		
		float posXgreenSrc = 0;
		float posYgreenSrc = 0;
	
		posXyellowSrc = moment10yellowsrc/areayellowsrc;
		posYyellowSrc = moment01yellowsrc/areayellowsrc;
	
		posXblueSrc = moment10bluesrc/areabluesrc;
		posYblueSrc = moment01bluesrc/areabluesrc;
	
		posXredSrc = moment10redsrc/arearedsrc;
		posYredSrc = moment01redsrc/arearedsrc;	
	
		posXgreenSrc = moment10greensrc/areagreensrc;
		posYgreenSrc = moment01greensrc/areagreensrc;	
		
		srcPoints[0].x = posXyellowSrc;
		srcPoints[0].y = posYyellowSrc;
		srcPoints[1].x = posXblueSrc;
		srcPoints[1].y = posYblueSrc;
		srcPoints[2].x = posXredSrc;
		srcPoints[2].y = posYredSrc;
		srcPoints[3].x = posXgreenSrc;
		srcPoints[3].y = posYgreenSrc;
	
	
	
		// generate map_Matrix
		cvGetPerspectiveTransform(srcPoints, desPoints, map_matrix1[i]);
		//cvGetAffineTransform(srcPoints, desPoints, map_matrix);
	
		// Print it out for debugging purposes
		printf("position yellow Destination (%f,%f)\n", posXyellowDes, posYyellowDes);
		printf("position blue Destination (%f,%f)\n", posXblueDes, posYblueDes);
		printf("position red Destination (%f,%f)\n", posXredDes, posYredDes);
		printf("position green Destination (%f,%f)\n", posXgreenDes, posYgreenDes);
		
		printf("position yellow Source (%f,%f)\n", posXyellowSrc, posYyellowSrc);
		printf("position blue Source (%f,%f)\n", posXblueSrc, posYblueSrc);
		printf("position red Source (%f,%f)\n", posXredSrc, posYredSrc);
		printf("position green Source (%f,%f)\n", posXgreenSrc, posYgreenSrc);
		
		printf("Iteration: %d\n",i);

	
		//Map source to destination pic
		//cvWarpAffine(srcimage, desimage, map_matrix, CV_INTER_LINEAR + CV_WARP_FILL_OUTLIERS);
		//cvWarpPerspective(srcimage, desimage, map_matrix, CV_INTER_LINEAR + CV_WARP_FILL_OUTLIERS);
		

		//View Image and Threshs
        /*cvShowImage("yellowMarker", imgYellowThreshDes);
		cvShowImage("blueMarker", imgBlueThreshDes);
		cvShowImage("redMarker", imgRedThreshDes);
		cvShowImage("greenMarker", imgGreenThreshDes);
		cvShowImage("Image", desimage);*/
	}
	
	
	// Wait for a keypress to exit application
	while( 1 ) {
		if( cvWaitKey( 100 ) == 27 ) break;
	}	// Wait for a keypress to exit application
	
	
	
	
		// Release the thresholded image+moments to prevent memory leaks
		cvReleaseImage(&imgYellowThreshDes);
		cvReleaseImage(&imgBlueThreshDes);
		cvReleaseImage(&imgRedThreshDes);
		cvReleaseImage(&imgGreenThreshDes);
		cvReleaseImage(&imgYellowThreshSrc);
		cvReleaseImage(&imgBlueThreshSrc);
		cvReleaseImage(&imgRedThreshSrc);
		cvReleaseImage(&imgGreenThreshSrc);
	
		/*cvDestroyWindow( "yellowMarker" ); 
		cvDestroyWindow( "blueMarker" ); 
		cvDestroyWindow( "redMarker" ); 
		cvDestroyWindow( "greenMarker" ); 
		cvDestroyWindow( "Image" ); */
	
		delete momentsyellowdes;
		delete momentsbluedes;
		delete momentsreddes;
		delete momentsgreendes;
		delete momentsyellowsrc;
		delete momentsbluesrc;
		delete momentsredsrc;
		delete momentsgreensrc;
	
		
		

	
	
    return 0;
}
