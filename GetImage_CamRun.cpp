//-----------------------------------------------------------------//
// Name        | GetImage_CamRun.cpp         | Type: (*) source    //
//-------------------------------------------|       ( ) header    //
// Project     | pco.camera simple examples  |       ( ) others    //
//-----------------------------------------------------------------//
// Platform    | WINDOWS                                           //
//-----------------------------------------------------------------//
// Environment | Microsoft VisualStudio                            //
//             |                                                   //
//-----------------------------------------------------------------//
// Purpose     | Source for showing simple image grabbing          //
//-----------------------------------------------------------------//
// Author      | MBL, PCO AG                                       //
//-----------------------------------------------------------------//
// Revision    | rev. 1.0 rel. 1.00                                //
//-----------------------------------------------------------------//
// Notes       | error handling must be added                      //
//             |                                                   //
//             | some images will be lost, when working with       //
//             | higher framerates                                 //
//             |                                                   //
//-----------------------------------------------------------------//
// (c) 2016 PCO AG * Donaupark 11 *                                //
// D-93309  Kelheim / Germany * Phone: +49 (0)9441 / 2005-0 *      //
// Fax: +49 (0)9441 / 2005-20 * Email: info@pco.de                 //
//-----------------------------------------------------------------//

#include "stdafx.h"

#include "pco_err.h"
#include "sc2_SDKStructures.h"
#include "SC2_SDKAddendum.h"
#include "SC2_CamExport.h"
#include "SC2_Defs.h"

// my
// #include <iostream>
// #include <fstream>
#include <string.h>
// end my


#define _FILEFUNCTION_

#ifdef _FILEFUNCTION_
char file_name[50];
#include "../file12.h"
#include "../file12.cpp"
#endif

void print_transferpar(HANDLE cam);


// my
bool cmp_charr(char * ch, char * s, int le) {
	if (le != strlen(ch))
		return false;
	for (int i = 0; i < le; i++) {
		if (ch[i] != s[i])
			return false;
	}
	return true;
}
// end my


int main(int argc, char* argv[])
{
#ifdef _FILEFUNCTION_
	printf("It is defined.\n");
#endif
	int iRet;
	HANDLE cam;
	HANDLE BufEvent;
	short BufNum;
	WORD *BufAdr;

	PCO_Description strDescription;
	WORD RecordingState;

	printf("Get Handle to connected camera\n");
	iRet = PCO_OpenCamera(&cam, 0);
	if (iRet != PCO_NOERROR)
	{
		printf("No camera found\n");
		printf("Press <Enter> to end\n");
		iRet = getchar();
		return -1;
	}
	else
	{
		printf("A camera is found.\n");
	}

	strDescription.wSize = sizeof(PCO_Description);
	iRet = PCO_GetCameraDescription(cam, &strDescription);

	iRet = PCO_GetRecordingState(cam, &RecordingState);
	if (RecordingState)
	{
		iRet = PCO_SetRecordingState(cam, 0);
	}

	//set camera to default state
	iRet = PCO_ResetSettingsToDefault(cam);

#ifdef _FILEFUNCTION_
	iRet = PCO_SetTimestampMode(cam, TIMESTAMP_MODE_BINARYANDASCII);
#endif

	iRet = PCO_ArmCamera(cam);

	DWORD CameraWarning, CameraError, CameraStatus;
	iRet = PCO_GetCameraHealthStatus(cam, &CameraWarning, &CameraError, &CameraStatus);
	if (CameraError != 0)
	{
		printf("Camera has ErrorStatus\n");
		printf("Press <Enter> to end\n");
		iRet = getchar();
		iRet = PCO_CloseCamera(cam);
		return -1;
	}

	print_transferpar(cam);

	// my
	DWORD dwDelay = 0, dwExposure = 1000;
	WORD wTimeBaseDelay = 0x0002, wTimeBaseExposure = 0x0002;
	WORD wBinHorz = 1, wBinVert = 1;
	WORD wTriggerMode = 0;
    DWORD dwPixelRate = 10000000;
    WORD wADCOperation = 1;
    SHORT sCoolSet = -150;
	FILE * cfg_file;
	int NumOfPic = 1;
	char line_cfg[1000];
	int val_cfg;
	printf("argc = %d\n", argc);
	if (argc == 1) {
		cfg_file = fopen("C:\\Users\\muonbpm\\Desktop\\test_img\\cfg.txt", "r");
	}
	else {
		cfg_file = fopen(argv[1], "r");
	}
	char foutname[256];
	if (argc > 2) {
		strcpy(foutname, argv[2]);
	}
	else {
		strcpy(foutname, "C:\\Users\\muonbpm\\Desktop\\test_img\\example.txt");
	}
	printf("The output file name :  %s\n", foutname);
	int cfg_status = 1;
	while (cfg_status > 0) {
		cfg_status = fscanf(cfg_file, "%s %d", line_cfg, &val_cfg);
		printf("status = %d :  %s (len = %d) %d\n", cfg_status, line_cfg, strlen(line_cfg), val_cfg);
		if (cmp_charr(line_cfg, "Exposure", 8))
			dwExposure = DWORD(val_cfg);
		if (cmp_charr(line_cfg, "ExposureBase", 12))
			wTimeBaseExposure = DWORD(val_cfg);
		if (cmp_charr(line_cfg, "Delay", 5))
			dwDelay = DWORD(val_cfg);
		if (cmp_charr(line_cfg, "BinningX", 8))
			wBinHorz = DWORD(val_cfg);
		if (cmp_charr(line_cfg, "BinningY", 8))
			wBinVert = DWORD(val_cfg);
		if (cmp_charr(line_cfg, "NumberOfPictures", 16))
			NumOfPic = val_cfg;
		if (cmp_charr(line_cfg, "TriggerMode", 11))
			wTriggerMode = val_cfg;
		if (cmp_charr(line_cfg, "ADCOperation", 12))
			wADCOperation = val_cfg;
		if (cmp_charr(line_cfg, "PixelRate", 9))
			dwPixelRate = val_cfg;
		if (cmp_charr(line_cfg, "CoolingTemperature", 18))
			sCoolSet = val_cfg;
	}
	fclose(cfg_file);
	//
	PCO_SetDelayExposureTime(cam, dwDelay, dwExposure, wTimeBaseDelay, wTimeBaseExposure);
	// PCO_ArmCamera(cam);
	//
	PCO_SetBinning(cam, wBinHorz, wBinVert);
	WORD wRoiX0 = 1, wRoiY0 = 1, wRoiX1 = 1600 / wBinHorz, wRoiY1 = 1200 / wBinVert;
	//
	printf("Want to set ROI :  (%d, %d) -- (%d, %d)\n", wRoiX0, wRoiY0, wRoiX1, wRoiY1);
	iRet = PCO_SetROI(cam, wRoiX0, wRoiY0, wRoiX1, wRoiY1);
	if (iRet != 0)
		printf("Set ROI error :  %d\n", iRet);
	//
	iRet = PCO_SetTriggerMode(cam, wTriggerMode);
	//
    iRet = PCO_SetADCOperation(cam, wADCOperation);
	//
    iRet = PCO_SetPixelRate(cam, dwPixelRate);
	if (iRet != 0)
		printf("Set pixel rate error :  %d\n", iRet);
	//
    iRet = PCO_SetCoolingSetpointTemperature(cam, sCoolSet);
	if (iRet != 0)
		printf("Set cooling setpoint temperature error :  %d\n", iRet);
	//
	iRet = PCO_ArmCamera(cam);
	//
	PCO_GetDelayExposureTime(cam, &dwDelay, &dwExposure, &wTimeBaseDelay, &wTimeBaseExposure);
	printf("delay = %d, exposure = %d, time base delay = 0x%04x, time base exposure = 0x%04x (0x0000 = ns, 0x0001 = us, 0x0002 = ms)\n",
		dwDelay, dwExposure, wTimeBaseDelay, wTimeBaseExposure);
	PCO_GetBinning(cam, &wBinHorz, &wBinVert);
	printf("X binning = %d,  Y binning = %d.\n", wBinHorz, wBinVert);
	PCO_GetROI(cam, &wRoiX0, &wRoiY0, &wRoiX1, &wRoiY1);
	printf("ROI :  (%d, %d) -- (%d, %d)\n", wRoiX0, wRoiY0, wRoiX1, wRoiY1);
	PCO_GetTriggerMode(cam, &wTriggerMode);
	printf("Trigger Mode :  0x%04x (0x0000 --- auto sequence,  0x0001 --- software trigger, 0x0002 --- [external exposure start & software trigger)\n",
		wTriggerMode);
    PCO_GetADCOperation(cam, &wADCOperation);
    printf("ADC operation :  0x%04x.  (0x0001 --- single ADC,  0x0002 --- dual ADC)\n", wADCOperation);
    PCO_GetPixelRate(cam, &dwPixelRate);
    printf("Pixel rate :  %d.\n", dwPixelRate);
    PCO_GetCoolingSetpointTemperature(cam, &sCoolSet);
    printf("Cooling set point temperature :  %d\n", sCoolSet);


	WORD XResAct, YResAct, XResMax, YResMax;
	DWORD bufsize;

	iRet = PCO_GetSizes(cam, &XResAct, &YResAct, &XResMax, &YResMax);
	bufsize = XResAct * YResAct * sizeof(WORD);
	printf("Actual Resolution ( X = %d,  Y = %d ).\n", XResAct, YResAct);

	BufEvent = NULL;
	BufNum = -1;
	BufAdr = NULL;
	iRet = PCO_AllocateBuffer(cam, &BufNum, bufsize, &BufAdr, &BufEvent);

	iRet = PCO_SetImageParameters(cam, XResAct, YResAct, IMAGEPARAMETERS_READ_WHILE_RECORDING, NULL, 0);

	printf("Start camera\n");
	iRet = PCO_SetRecordingState(cam, 1);

	// Temperature
	SHORT sCCDTemp, sCamTemp, sPowTemp;
	PCO_GetTemperature(cam, &sCCDTemp, &sCamTemp, &sPowTemp);
	printf("CDD sensor temperature = %.1f Celsius degree\n", sCCDTemp / 10.);
	printf("Internal camera temperature = %.1f Celsius degree\n", sCamTemp / 10.);
	printf("Additional device temperature = %.1f Celsius degree\n", sPowTemp / 10.);

	FILE * myfile;
	// myfile = fopen("C:\\Users\\muonbpm\\Desktop\\test_img\\example.txt", "wb");
	myfile = fopen(foutname, "wb");
	// my end
	printf("Grab single images from running camera\n");
	for (int i = 1; i <= NumOfPic; i++)
	{
		printf("%02d. image ", i);
		iRet = PCO_GetImageEx(cam, 1, 0, 0, BufNum, XResAct, YResAct, 16);
		if (iRet != PCO_NOERROR)
		{
			printf("failed \n");
			// break;
		}
		else {
			printf("done ");

#ifdef _FILEFUNCTION_
			sprintf(file_name, "C:\\Users\\muonbpm\\Desktop\\test_img\\image_%04d.tif", i);
			store_tiff(file_name, XResAct, YResAct, 0, BufAdr);
			printf("and stored to %s", file_name);
#endif
			printf("\n");
			// my
			printf("%d x %d = %d\n", XResAct, YResAct, XResAct*YResAct);
			fwrite(BufAdr, sizeof(WORD), XResAct*YResAct, myfile);
			// end my
		}
	}
	// my
	fclose(myfile);
	// my end

	printf("Stop camera and close connection\n");
	iRet = PCO_SetRecordingState(cam, 0);
	iRet = PCO_FreeBuffer(cam, BufNum);
	iRet = PCO_CloseCamera(cam);

	// printf("Press <Enter> to end\n");
	// iRet = getchar();
	return 0;
}

void print_transferpar(HANDLE cam)
{
	PCO_CameraType strCamType;
	DWORD iRet;
	strCamType.wSize = sizeof(PCO_CameraType);
	iRet = PCO_GetCameraType(cam, &strCamType);
	if (iRet != PCO_NOERROR)
	{
		printf("PCO_GetCameraType failed with errorcode 0x%x\n", iRet);
		return;
	}

	if (strCamType.wInterfaceType == INTERFACE_CAMERALINK)
	{
		PCO_SC2_CL_TRANSFER_PARAM cl_par;

		iRet = PCO_GetTransferParameter(cam, (void*)&cl_par, sizeof(PCO_SC2_CL_TRANSFER_PARAM));
		printf("Camlink Settings:\nBaudrate:    %u\nClockfreq:   %u\n", cl_par.baudrate, cl_par.ClockFrequency);
		printf("Dataformat:  %u 0x%x\nTransmit:    %u\n", cl_par.DataFormat, cl_par.DataFormat, cl_par.Transmit);
	}
}

