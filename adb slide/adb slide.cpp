// adb slide.cpp : 此文件包含 "main" 函数。程序执行将在此处开始并结束。
//
#define _CRT_SECURE_NO_WARNINGS

#include <iostream>
#include <Windows.h>
#include <conio.h>
#include <cstring>
#include <ctime>
#include "stdtostring.h"

#define _ADB_PATH "C:\\adb\\adb.exe"
#define _SCRCPY_PATH "C:\\adb\\scrcpy.exe"

std::time_t result;

string delEndChar(string STR) {
	return STR.substr(0, strlen(STR.c_str())-1);
}

class axis {
public:
	int x, y;
};

class ADBSession {

private:
	int connectMode;//1 for usb and 2 for wlan

	int linkADBwithWLAN(string ADB_PATH, string DEVICE_IP) {
		std::string str1 = ADB_PATH, str2 = " connect ";
		std::string str = str1 + str2 + DEVICE_IP.c_str();
		return system(str.c_str());
	}
	int linkADBwithUSB(string ADB_PATH) {
		std::string str1 = ADB_PATH, str2 = " devices";
		std::string str = str1 + str2;
		return system(str.c_str());
	}

	int slide(axis FROM_PT, axis TO_PT) {
		std::string str1 = _ADB_PATH, str2 = " shell input swipe ", str3 = std::to_string(FROM_PT.x), str4 = std::to_string(FROM_PT.y), str5 = std::to_string(TO_PT.x), str6 = std::to_string(TO_PT.y);
		std::string str = str1 + str2 + str3 + " " + str4 + " " + str5 + " " + str6;
		cout << "[ADB]\t" << str << std::endl;
		return system(str.c_str());
		return 0;
	}
	//the implement for the interactions with ADB server.

public:
	std::string ADB_PATH;
	int tryLinkADBwithWLAN(std::string ADB_PATH, string DEVICE_IP) {
		while (true)
		{
			if (int err = linkADBwithWLAN(ADB_PATH, DEVICE_IP)) {
				printf("[FAIL]\tFailed to Initiate the bridge.");
				std::cout << err << std::endl;
				exit(1);
				return 1;
			}
			else {
				printf("[INFO]\tAndroid device linked successfully?(Y/N)\n");
				char ch = _getch();
				if ((ch == 'y') || (ch == 'Y')) break;
			}
		}
		return 0;
	}
	int tryLinkADBwithUSB(std::string ADB_PATH) {
		while (true)
		{
			if (int err = linkADBwithUSB(ADB_PATH)) {
				printf("[FAIL]\tFailed to Initiate the bridge.");
				std::cout << err << std::endl;
				exit(1);
				return 1;
			}
			else {
				printf("[INFO]\tAndroid device linked successfully?(Y/N)\n");
				char ch = _getch();
				if ((ch == 'y') || (ch == 'Y')) break;
			}
		}
		return 0;
	}
	int trySlideUp() {
		axis fromPt, toPt;
		int delayBetweenOperation;
		printf("[INFO] Start to Slide...\nPlease insert the start and stop coordination:");
		cin >> fromPt.x >> fromPt.y >> toPt.x >> toPt.y;
		printf("[INFO]\t Please insert delay between operations (ms):");
		cin >> delayBetweenOperation;
		for (int i=0;true;++i)
		{
			result = std::time(nullptr);
			cout << "[" << delEndChar(std::asctime(std::localtime(&result))) << "]" << "\tPerforming slide for " << i << " time(s).\n";
			slide(fromPt, toPt);
			Sleep(delayBetweenOperation);
		}
		return 0;
	}
	int startScrcpy(string SCRCPY_PATH) {
		std::string str1 = "START ", str2 = SCRCPY_PATH;
		std::string str = str1 + str2;
		Sleep(1000);
		return system(str.c_str());;
	}
	int selectConnectMode() {
		printf("Please choose whether use USB or WLAN mode.(1/2):");
		this->connectMode = _getch() - '1' + 1;
		printf("\n");
		return 0;
	}
	int tryLinkADB(string ADB_PATH) {
		if (this->connectMode == 1) {
			this->tryLinkADBwithUSB(ADB_PATH);
		}
		else {
			string deviceIP;
			printf("Please insert device IP:");
			cin >> deviceIP;
			this->tryLinkADBwithWLAN(ADB_PATH, deviceIP);
		}
		return this->startScrcpy(_SCRCPY_PATH);
	}
	//the implement of program logic
};

int main()
{
	ADBSession theADB;
	printf("ADB Slide Started.\n");
	theADB.selectConnectMode();
	theADB.tryLinkADB(_ADB_PATH);
	theADB.trySlideUp();
	return 0;
}

// 运行程序: Ctrl + F5 或调试 >“开始执行(不调试)”菜单
// 调试程序: F5 或调试 >“开始调试”菜单

// 入门使用技巧: 
//   1. 使用解决方案资源管理器窗口添加/管理文件
//   2. 使用团队资源管理器窗口连接到源代码管理
//   3. 使用输出窗口查看生成输出和其他消息
//   4. 使用错误列表窗口查看错误
//   5. 转到“项目”>“添加新项”以创建新的代码文件，或转到“项目”>“添加现有项”以将现有代码文件添加到项目
//   6. 将来，若要再次打开此项目，请转到“文件”>“打开”>“项目”并选择 .sln 文件
