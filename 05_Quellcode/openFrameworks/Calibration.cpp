/*
 *  Calibration.cpp
 *  emptyExample
 *
 *  Created by Armin Voit on 29.06.12.
 *  Copyright 2012 __MyCompanyName__. All rights reserved.
 *
 */

#include "Calibration.h"

//================================================================================================================
//Initialize Iteration counter (= number of images to be compared)
//================================================================================================================

int counter = 8;
//	int counter = 3;

//================================================================================================================
// FILTER FOR OUR MARKERS
// ------------------------
//
// YELLOW +-------+ BLUE
//        |       |
// GREEN  +-------+ RED
//
// FIRST: CONVERT RGB IMAGES INTO HSV
// SECOND: SEARCH FOR THE NEED COLOUR 
// THIRD: ERODE THE IMGTHRESHED TO REDUCE COLOORSPOTS WITH ONLY SINGLEPIXEL-SIZE TO AVOID DISTORTION
// FOURTH: DILATE THE THE FOUND PIXELS TO GET A BETTER RESULT
//================================================================================================================


//================================================================================================================
// TO FILTER FOR YELLOW MARKER
//================================================================================================================
IplImage* Calibration::GetThresholdedImageYellow(IplImage* img)
{
    
    //------------------------------------------------------------------------------------------------------------	
	// CONVERT THE IMAGE INTO HSV IMAGE 
    //------------------------------------------------------------------------------------------------------------	
    IplImage* imgHSV = cvCreateImage(cvGetSize(img), 8, 3);
    cvCvtColor(img, imgHSV, CV_BGR2HSV);
	
	IplImage* imgThreshed = cvCreateImage(cvGetSize(img), 8, 1);
	
	//cvInRangeS(imgHSV, cvScalar(20, 60, 110), cvScalar(65, 180, 200), imgThreshed); //Farbwerte ohne DesImg
	cvInRangeS(imgHSV, cvScalar(20, 90, 70), cvScalar(55, 180, 200), imgThreshed); //Ohne PS
	//cvInRangeS(imgHSV, cvScalar(0, 20, 230), cvScalar(35, 380, 300), imgThreshed);

    //------------------------------------------------------------------------------------------------------------	
    // ERODE AND DILATE IMGTHRESHED
    //------------------------------------------------------------------------------------------------------------	
	cvErode(imgThreshed , imgThreshed, NULL, 3);
	cvDilate(imgThreshed, imgThreshed, NULL, 1);
	
    cvReleaseImage(&imgHSV);
    return imgThreshed;
}


//================================================================================================================
// TO FILTER FOR GREEN MARKER
//================================================================================================================
IplImage* Calibration::GetThresholdedImageGreen(IplImage* img)
{
    //------------------------------------------------------------------------------------------------------------	
	// CONVERT THE IMAGE INTO HSV IMAGE 
    //------------------------------------------------------------------------------------------------------------	
    IplImage* imgHSV = cvCreateImage(cvGetSize(img), 8, 3);
    cvCvtColor(img, imgHSV, CV_BGR2HSV);
	
	IplImage* imgThreshed = cvCreateImage(cvGetSize(img), 8, 1);
	
	//cvInRangeS(imgHSV, cvScalar(60, 170, 70), cvScalar(100, 270, 270), imgThreshed); //Farbwerte ohne DesImg
	//cvInRangeS(imgHSV, cvScalar(60, 130, 70), cvScalar(100, 290, 270), imgThreshed); // Ohne PS
	//cvInRangeS(imgHSV, cvScalar(60, 130, 70), cvScalar(100, 290, 370), imgThreshed);
	cvInRangeS(imgHSV, cvScalar(50, 30, 30), cvScalar(90, 290, 370), imgThreshed);
	
    //------------------------------------------------------------------------------------------------------------	
    // ERODE AND DILATE IMGTHRESHED
    //------------------------------------------------------------------------------------------------------------	
	cvErode(imgThreshed , imgThreshed, NULL, 3);
	cvDilate(imgThreshed, imgThreshed, NULL, 1);
	
    cvReleaseImage(&imgHSV);
    return imgThreshed;
}



//================================================================================================================
// TO FILTER FOR BLUE MARKER
//================================================================================================================
IplImage* Calibration::GetThresholdedImageBlue(IplImage* img)
{
    //------------------------------------------------------------------------------------------------------------	
	// CONVERT THE IMAGE INTO HSV IMAGE 
    //------------------------------------------------------------------------------------------------------------	
    IplImage* imgHSV = cvCreateImage(cvGetSize(img), 8, 3);
    cvCvtColor(img, imgHSV, CV_BGR2HSV);
	
	IplImage* imgThreshed = cvCreateImage(cvGetSize(img), 8, 1);
	
	cvInRangeS(imgHSV, cvScalar(100, 130, 90), cvScalar(125, 255, 165), imgThreshed); //Ohne PS
	//cvInRangeS(imgHSV, cvScalar(100, 250, 150), cvScalar(225, 270, 170), imgThreshed);

	
    //------------------------------------------------------------------------------------------------------------	
    // ERODE AND DILATE IMGTHRESHED
    //------------------------------------------------------------------------------------------------------------	
	//cvDilate(imgThreshed, imgThreshed, NULL, 1);
	cvErode(imgThreshed , imgThreshed, NULL, 1);
	cvDilate(imgThreshed, imgThreshed, NULL, 1);
	
	
    cvReleaseImage(&imgHSV);
    return imgThreshed;
}


//================================================================================================================
// TO FILTER FOR RED MARKER 
//================================================================================================================
IplImage* Calibration::GetThresholdedImageRed(IplImage* img)
{
    //------------------------------------------------------------------------------------------------------------	
	// CONVERT THE IMAGE INTO HSV IMAGE 
    //------------------------------------------------------------------------------------------------------------	
    IplImage* imgHSV = cvCreateImage(cvGetSize(img), 8, 3);
    cvCvtColor(img, imgHSV, CV_BGR2HSV);
	
	IplImage* imgThreshed = cvCreateImage(cvGetSize(img), 8, 1);
	
	cvInRangeS(imgHSV, cvScalar(150, 100, 0), cvScalar(290, 290, 290), imgThreshed); //Ohne PS
	//cvInRangeS(imgHSV, cvScalar(60, 130, 50), cvScalar(100, 290, 290), imgThreshed);
	
    //------------------------------------------------------------------------------------------------------------	
    // ERODE AND DILATE IMGTHRESHED
    //------------------------------------------------------------------------------------------------------------	
	cvErode(imgThreshed , imgThreshed, NULL, 1);
	cvDilate(imgThreshed, imgThreshed, NULL, 1);
	
    cvReleaseImage(&imgHSV);
    return imgThreshed;
}

//================================================================================================================
// OUR MAIN FUNCTION 
//--------------------------
// THIS IS WHAT WE CALL FROM OUT OF OPENFRAMEWORKS
//================================================================================================================


void Calibration::doCalibration(){
    //------------------------------------------------------------------------------------------------------------	
    // DEFINITIONS
	//------------------------------------------------------------------------------------------------------------
    
    //-----DEFINE CVMOMENTS--------------------------------------------------------------------------------------- 
	momentsyellowdes = (CvMoments*)malloc(sizeof(CvMoments));
	momentsbluedes = (CvMoments*)malloc(sizeof(CvMoments));
	momentsreddes = (CvMoments*)malloc(sizeof(CvMoments));
	momentsgreendes = (CvMoments*)malloc(sizeof(CvMoments));
	
	momentsyellowsrc = (CvMoments*)malloc(sizeof(CvMoments));
	momentsbluesrc = (CvMoments*)malloc(sizeof(CvMoments));
	momentsredsrc = (CvMoments*)malloc(sizeof(CvMoments));
	momentsgreensrc = (CvMoments*)malloc(sizeof(CvMoments));
	
    //-----DEFINE MAP_MATRICES TO USE AS TRANSFORMATION MATRIX----------------------------------------------------

    //map_matrix1 = cvCreateMat(3,3, CV_32FC1);
	map_matrix1 = cvCreateMat(2,3, CV_32FC1);
	
	//-----DEFINE IMAGEARRAY AND LOAD CALIBRATION IMAGES
	
//		markerImages[0] = cvLoadImage("/Users/arminvoit/Documents/openframeworks/apps/test/Matrigx/bin/MarkerPics/dess.jpg");

	
	for (int i=1, j=1; i<=counter; i++, j++) {
		
		char buffer_mrk[33];
		
		sprintf(buffer_mrk, "/Users/arminvoit/Documents/openframeworks/apps/Stand_22.07_spät/Matrigx/bin/MarkerPics/src%d.jpg", j);
				
		markerImages[i-1] = cvLoadImage(buffer_mrk);
		
	}
	
	for (int i=1, j=1; i<=counter; i++, j++){
		
		char buffer_src[33];
		
		sprintf(buffer_src, "/Users/arminvoit/Documents/openframeworks/apps/Stand_22.07_spät/Matrigx/bin/Pics/%ds.jpg", j);
		
		images[i-1]= cvLoadImage(buffer_src);

	}
	
	
	//-----SET THE FIRST ELEMENT IN PREVIEWIMAGES WHICH IS USED AS OUR FIRST DESTINATION IMAGE--------------------	
	previewImages[0]= images[0];
	
	//------------------------------------------------------------------------------------------------------------
	// CALCULATE THE TRANSFORMATION MATRIX AND TRANSFORM THE IMAGES FOR OUR PREVIEW   
    //------------------------------------------------------------------------------------------------------------
	for (int i=1; i< counter; i++){
	
        //-------------------------------------------------------------------------
		// THE WINDOWS THAT WE USE TO GIVE US A VISUAL FEEDBACK
        // CREATE WINDOWS AND MOVE THEM
        // UNCOMMENT IF YOU NEED SPECIAL VIEWS 
        //-------------------------------------------------------------------------
		
		cvNamedWindow("yellowMarker");
		cvMoveWindow("yellowMarker", 0, 0);
		cvNamedWindow("blueMarker");
		cvMoveWindow("blueMarker", 600, 0);
		cvNamedWindow("redMarker");
		cvMoveWindow("redMarker", 0, 400);
		cvNamedWindow("greenMarker");
		cvMoveWindow("greenMarker", 600, 400);
		
        //-------------------------------------------------------------------------
		// LOAD DESTINATION IMAGE
        //---------------------------
        // We use the element in markerImages that is the one right before the one we use as srcimage. 
        // With that we want to minimize the diferences between the two images.  
        //-------------------------------------------------------------------------
        
        //-----UNCOMMENT IF YOU WANT TO USE A SINGLE GIVEN DESTINATION IMAGE-------
		desimage = markerImages[i-1];	
        //desimage = cvLoadImage("/Users/arminvoit/Documents/openframeworks/apps/test/Matrigx/bin/MarkerPics/dess.jpg");

        //-------------------------------------------------------------------------
		// LOAD IMAGES FOR MAPPING
        //---------------------------
        // srcimage: The image that holds the marker for our previewimage 
        // previewimage: The image that will be transformed
        //-------------------------------------------------------------------------
		srcimage = markerImages[i];
        //srcimage = markerImages[i+1];

		previewimage = images[i-1];
		

        //-------------------------------------------------------------------------
		// Check for srcimage and desimage. Couldn't get an image? --> Throw an error and quit
        //-------------------------------------------------------------------------
		if(!desimage)
		{
			printf("Could not initialize desimage...\n");
		}
        if(!srcimage)
		{
			printf("Could not initialize srcimage...\n");
		}
	
        //-------------------------------------------------------------------------
		// IPlIMAGES THAT HOLD THE THRESHHOLDED IMAGES
        //---------------------------------------------
        // Marker = white
        // rest = black
        // Here we use the CvMoments defined at the beginning of the function
        //-------------------------------------------------------------------------
		imgYellowThreshDes = GetThresholdedImageYellow(desimage);
		imgBlueThreshDes = GetThresholdedImageBlue(desimage);
		imgRedThreshDes = GetThresholdedImageRed(desimage);
		imgGreenThreshDes = GetThresholdedImageGreen(desimage);
	
		imgYellowThreshSrc = GetThresholdedImageYellow(srcimage);
		imgBlueThreshSrc = GetThresholdedImageBlue(srcimage);
		imgRedThreshSrc = GetThresholdedImageRed(srcimage);
		imgGreenThreshSrc = GetThresholdedImageGreen(srcimage);
	
		cvMoments(imgYellowThreshDes, momentsyellowdes, 1);
		cvMoments(imgBlueThreshDes, momentsbluedes, 1);
		cvMoments(imgRedThreshDes, momentsreddes, 1);
		cvMoments(imgGreenThreshDes, momentsgreendes, 1);
	
		cvMoments(imgYellowThreshSrc, momentsyellowsrc, 1);
		cvMoments(imgBlueThreshSrc, momentsbluesrc, 1);
		cvMoments(imgRedThreshSrc, momentsredsrc, 1);
		cvMoments(imgGreenThreshSrc, momentsgreensrc, 1);
		
		
	
        //-------------------------------------------------------------------------
		// THE ACTUAL MOMENT VALUES 
        //-------------------------------------------------------------------------
		moment10yellowdes = cvGetSpatialMoment(momentsyellowdes, 1, 0);
		moment01yellowdes = cvGetSpatialMoment(momentsyellowdes, 0, 1);
		areayellowdes = cvGetCentralMoment(momentsyellowdes, 0, 0);
	
		moment10bluedes = cvGetSpatialMoment(momentsbluedes, 1, 0);
		moment01bluedes = cvGetSpatialMoment(momentsbluedes, 0, 1);
		areabluedes = cvGetCentralMoment(momentsbluedes, 0, 0);
	
		moment10reddes = cvGetSpatialMoment(momentsreddes, 1, 0);
		moment01reddes = cvGetSpatialMoment(momentsreddes, 0, 1);
		areareddes = cvGetCentralMoment(momentsreddes, 0, 0);
	
		moment10greendes = cvGetSpatialMoment(momentsgreendes, 1, 0);
		moment01greendes = cvGetSpatialMoment(momentsgreendes, 0, 1);
		areagreendes = cvGetCentralMoment(momentsgreendes, 0, 0);
	
		moment10yellowsrc = cvGetSpatialMoment(momentsyellowsrc, 1, 0);
		moment01yellowsrc = cvGetSpatialMoment(momentsyellowsrc, 0, 1);
		areayellowsrc = cvGetCentralMoment(momentsyellowsrc, 0, 0);
	
		moment10bluesrc = cvGetSpatialMoment(momentsbluesrc, 1, 0);
		moment01bluesrc = cvGetSpatialMoment(momentsbluesrc, 0, 1);
		areabluesrc = cvGetCentralMoment(momentsbluesrc, 0, 0);
	
		moment10redsrc = cvGetSpatialMoment(momentsredsrc, 1, 0);
		moment01redsrc = cvGetSpatialMoment(momentsredsrc, 0, 1);
		arearedsrc = cvGetCentralMoment(momentsredsrc, 0, 0);
	
		moment10greensrc = cvGetSpatialMoment(momentsgreensrc, 1, 0);
		moment01greensrc = cvGetSpatialMoment(momentsgreensrc, 0, 1);
		areagreensrc = cvGetCentralMoment(momentsgreensrc, 0, 0);
	
        //-------------------------------------------------------------------------
		// HOLDING THE LAST AND CURRENT MARKER POSITIONS AND PLACING THEM INTO A CVPOINT VECTOR
        //-------------------------------------------------------------------------
		posXyellowDes = moment10yellowdes/areayellowdes;
		posYyellowDes = moment01yellowdes/areayellowdes;
	
		posXblueDes = moment10bluedes/areabluedes;
		posYblueDes = moment01bluedes/areabluedes;
	
		posXredDes = moment10reddes/areareddes;
		posYredDes = moment01reddes/areareddes;
	
		posXgreenDes = moment10greendes/areagreendes;
		posYgreenDes = moment01greendes/areagreendes;
	
		posXyellowSrc = moment10yellowsrc/areayellowsrc;
		posYyellowSrc = moment01yellowsrc/areayellowsrc;
	
		posXblueSrc = moment10bluesrc/areabluesrc;
		posYblueSrc = moment01bluesrc/areabluesrc;
	
		posXredSrc = moment10redsrc/arearedsrc;
		posYredSrc = moment01redsrc/arearedsrc;	
	
		posXgreenSrc = moment10greensrc/areagreensrc;
		posYgreenSrc = moment01greensrc/areagreensrc;	
	
        //-------------------------------------------------------------------------
		// FILL DES-POINTS WITH FIX VALUES 
        //-------------------------------
        // To check for errors with the Markers
        // Uncomment for using fixvalues 
        //-------------------------------------------------------------------------
		//	setDesPoints(333.2426, 240.5768, 490.3245, 260.2477, 470.9836, 350.2426, 325.4245, 350.1416);
		
        //-------------------------------------------------------------------------
		//  FILL DES-POINTS WITH MARKER-VALUES 
        //----------------------------------------
        //  Uncomment for using markers 
        //-------------------------------------------------------------------------
		setDesPoints(posXyellowDes, posYyellowDes, posXblueDes, posYblueDes, posXredDes, posYredDes,  posXgreenDes, posYgreenDes);
		
        //-------------------------------------------------------------------------
		// FILL SRC-POINTS WITH FIX VALUES 
        //-----------------------------------------
        //  To check for errors with the Markers 
        //  Uncomment for using fixvalues 
        //-------------------------------------------------------------------------
		// setSrcPoints(200, 150, 600, 150, 200, 450, 600, 450);
		
        //-------------------------------------------------------------------------
		//  FILL SRC-POINTS WITH MARKER-VALUES
        //----------------------------------------
		//  Uncomment for using markers 
        //-------------------------------------------------------------------------
		  setSrcPoints(posXyellowSrc, posYyellowSrc, posXblueSrc, posYblueSrc, posXredSrc, posYredSrc, posXgreenSrc, posYgreenSrc);
		
        //-------------------------------------------------------------------------
		// GENERATE MAP_MATRIX
        //---------------------
        // We use an affine transformation for our calibration because we don´t need
        // we don´t need a perspective transform. Here we create the Matrix for this. 
        //-------------------------------------------------------------------------

        cvGetAffineTransform(desPoints, srcPoints, map_matrix1);
        //cvGetPerspectiveTransform(srcPoints, desPoints, map_matrix1);        //<-- USE FOR PERSPECTIVE TRANSFORM        

	
        //-------------------------------------------------------------------------
		// PRINT FOR DEBUGGING PURPOSE
        //-------------------------------
        // We print the positionvalues of each marker to the console
        //-------------------------------------------------------------------------
		printf("position yellow Destination (%f,%f)\n", posXyellowDes, posYyellowDes);
		printf("position blue Destination (%f,%f)\n", posXblueDes, posYblueDes);
		printf("position red Destination (%f,%f)\n", posXredDes, posYredDes);
		printf("position green Destination (%f,%f)\n", posXgreenDes, posYgreenDes);
	
		printf("position yellow Source (%f,%f)\n", posXyellowSrc, posYyellowSrc);
		printf("position blue Source (%f,%f)\n", posXblueSrc, posYblueSrc);
		printf("position red Source (%f,%f)\n", posXredSrc, posYredSrc);
		printf("position green Source (%f,%f)\n", posXgreenSrc, posYgreenSrc);
	
	
        //-------------------------------------------------------------------------
		// View Image and Threshs - MULTIWINDOWVIEW
        //-------------------------------------------------------------------------
		cvShowImage("yellowMarker", imgYellowThreshDes);
		cvShowImage("blueMarker", imgBlueThreshDes);
		cvShowImage("redMarker", imgRedThreshDes);
		cvShowImage("greenMarker", imgGreenThreshDes);
		//cvShowImage("DesImage", desimage);
		//cvShowImage("SrcImage", srcimage);

	
        //-------------------------------------------------------------------------	
		// MAP SOURCE TO DESTINATION PIC
        //-------------------------------
        // This is where the actual calibration is done
        // We use to affine warps to transform preview and calimage
        //-------------------------------------------------------------------------
		
        //cvWarpPerspective(previewimage, previewimage, map_matrix1, CV_INTER_LINEAR + CV_WARP_FILL_OUTLIERS);
        //<-- USE FOR PERSPECTIVE TRANSFORM        

		cvWarpAffine(previewimage, previewimage, map_matrix1, CV_WARP_FILL_OUTLIERS);

        //-------------------------------------------------------------------------
		// Check for the previewimage and calimage. Couldn't get an image? --> Throw an error and quit
        //-------------------------------------------------------------------------

		if(!previewimage)
		{
			printf("Could not initialize srcimage...\n");
		}
		
        //-------------------------------------------------------------------------
        // WRITE THE RESULTS OF THE TRANSFORMATION IN ITS SPECIFIC ARRAY 
        //-------------------------------------------------------------------------

		previewImages[i]=previewimage;
		
        //-------------------------------------------------------------------------
		// STEP-BY-STEP MARKER CHECK
        //----------------------------
        // Wait for a keypress to exit application
        //-------------------------------------------------------------------------

        while( 1 ) {
		if( cvWaitKey( 100 ) == 27 ) break;
		}		
		
	} // <--- END OF ITERATION

	
    //-------------------------------------------------------------------------
	// START THE PREVIEW
    //-------------------------------------------------------------------------
	showPreview();

    //-------------------------------------------------------------------------
	// RELEASEBLOCK TO PREVENT MEMORY LEAKS
    //-------------------------------------------------------------------------
    
    //-----DESTROY ALL WINDOWS THAT WHERE OPEND 
    cvDestroyAllWindows();
    
    //-----RELEASE IMAGES-----
    cvReleaseImage(&imgYellowThreshDes);
	cvReleaseImage(&imgBlueThreshDes); 
	cvReleaseImage(&imgRedThreshDes); 
	cvReleaseImage(&imgGreenThreshDes); 
	cvReleaseImage(&imgYellowThreshSrc);
	cvReleaseImage(&imgBlueThreshSrc); 
	cvReleaseImage(&imgRedThreshSrc); 
	cvReleaseImage(&imgGreenThreshSrc); 
    
    cvReleaseImage(&desimage);
	cvReleaseImage(&srcimage);
	cvReleaseImage(&previewimage);
    cvReleaseImage(&calimage);
    
    cvReleaseImage(&srcYellow);
    cvReleaseImage(&srcBlue);
    cvReleaseImage(&srcGreen);
    cvReleaseImage(&srcRed);
	
	cvReleaseImage(&images[10]);
	cvReleaseImage(&markerImages[10]);
	cvReleaseImage(&previewImages[10]);
    cvReleaseImage(&calibratedImages[10]);
	
    //-----RELEASE MATRICES-----
	cvReleaseMat(&map_matrix1);
    
    //-----RELEASE CVMOMENTS-----
    delete &momentsyellowdes;
	delete &momentsbluedes; 
	delete &momentsreddes; 
	delete &momentsgreendes; 
	
	delete &momentsyellowsrc; 
	delete &momentsbluesrc; 
	delete &momentsredsrc; 
	delete &momentsgreensrc; 
    
}

//================================================================================================================
// SET THE SRCPOINTS FOR TRANSFORMATION MATRIX 
//================================================================================================================

void Calibration::setSrcPoints(float posXyellowSrc, float posYyellowSrc, float posXblueSrc, float posYblueSrc, float posXredSrc, float posYredSrc, float posXgreenSrc, float posYgreenSrc){
    
    srcPoints[0].x = posXyellowSrc;
    srcPoints[0].y = posYyellowSrc;
    srcPoints[1].x = posXblueSrc;
    srcPoints[1].y = posYblueSrc;
    srcPoints[2].x = posXredSrc;
    srcPoints[2].y = posYredSrc;
    srcPoints[3].x = posXgreenSrc;
    srcPoints[3].y = posYgreenSrc;
    
    
}

//================================================================================================================
// SET DESPOINTS FOR TRANSFORMATIONMATRIX 
//================================================================================================================

void Calibration::setDesPoints(float posXyellowDes, float posYyellowDes, float posXblueDes, float posYblueDes, float posXredDes, float posYredDes, float posXgreenDes, float posYgreenDes){
    
    desPoints[0].x = posXyellowDes;
    desPoints[0].y = posYyellowDes;
    desPoints[1].x = posXblueDes;
    desPoints[1].y = posYblueDes;
    desPoints[2].x = posXredDes;
    desPoints[2].y = posYredDes;
    desPoints[3].x = posXgreenDes;
    desPoints[3].y = posYgreenDes;
    
}

//================================================================================================================
// OUR PREVIEW PLAYER
//-----------------------------
// WE CREATE AN ANIMATION WITH ALPHABLENDING BY USING 2 ITERATIONS. FIRST ONE TO LOAD THE NEEDED IMAGES FROM PREVIEWIMAGES
// SECOND ONE TO SLOWLY INCREASE AND DECREASE THE ALPHAVALUES OF THE TWO IMAGES.
//================================================================================================================
void Calibration::showPreview(){
	
	IplImage *src1, *src2;
	int x = 0;
	int y = 0;
	int width = 800;
	int height = 600;
	double alpha;
	double beta; 
	
    //-----CREATE THE WINDOW PREVIEW. WE CREATE IT SEPARETLY BECAUSE WE DON´T WANT IT TO BE SHOWN ALL THE TIME--- 
	cvNamedWindow("Preview");
	cvMoveWindow("Preview", 100,100);
	char c;

    //-----THE ITERATIONS WE USE TO CREATE ALPHABLENDING

    //-----LOAD THE IMAGES YOU WANT TO FADE BETWEEN 
    for (int i=0; i<=counter; i++) {
        src1= previewImages[i];
        src2= previewImages[i+1];	
        
        //-----CHANGE ALPHAVALUES. OVERBLEND IMAGES
        for (int j=1; j<10; j++) { 
		
            alpha = 1.0 - j*0.1; //ALPHA SRC1
            beta = (1-alpha);    //ALPHA SRC2
            
            // WE USE REGIONS OF INTEREST(ROI) TO BLEND THE IMAGES 
            cvSetImageROI(src1, cvRect(x,y,width,height)); 
            cvSetImageROI(src2, cvRect(0,0,width,height)); 
            cvAddWeighted(src1, alpha, src2, beta,0.0,src1);
            cvResetImageROI(src1);
            cvShowImage("Preview", src1);
            cvWaitKey(150);
        }
    }
    
	cvDestroyWindow( "Preview" ); 

}



