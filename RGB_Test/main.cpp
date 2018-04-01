#include<stdio.h>
#include<conio.h>
#include<stdlib.h>
#include <windows.h>
#define WIDTHBYTES(i)((i+31)/32*4)

int main()
{
	errno_t err;
	FILE    *fp = NULL;
	char* lpszFileName = "D:\\test.bmp";//生成的临时文件的位置和名称

	int temp_R=0, temp_G=0, temp_B=0;
	printf("此为JXL制的RGB颜色显示程序，请依次输入RGB的值(范围0-255):\n");

    m:;

	printf("R=");
	scanf_s("%d", &temp_R,200);
	printf("G=");
	scanf_s("%d", &temp_G,200);
	printf("B=");
	scanf_s("%d", &temp_B,200);

	if (!(temp_R >= 0 && temp_R <= 255 && temp_G >= 0 && temp_G <= 255 && temp_B >= 0 && temp_B <= 255))
	{
		printf("输入的RGB的值的范围有误，请重新输入\n");
		goto m;//输入的数据范围有误，返回重新输入数据
	}



	int Width = 640, Height = 640;//生成的临时文件图片大小(像素)为640*640的
	
	BITMAPFILEHEADER   bf;
	BITMAPINFOHEADER   bi;
	int             lineBytes = 0;
	int             i=0;

	char   lpBitmap[640];

	for (i = 0; i<640; i++)
	{
		lpBitmap[i] = 0;//写入每一行640个像素所对应的调色盘代码
	}

	lineBytes = (int)WIDTHBYTES(Width * 8);

	//构造bmp文件头信息
	bf.bfType = 19778;
	bf.bfSize = lineBytes*Height + 1078;
	bf.bfReserved1 = 0;
	bf.bfReserved2 = 0;
	bf.bfOffBits = 1078;
	bi.biSize = 40;
	bi.biWidth = Width;
	bi.biHeight = Height;
	bi.biPlanes = 1;
	bi.biBitCount = 8;
	bi.biCompression = 0;
	bi.biSizeImage = lineBytes*Height;
	bi.biXPelsPerMeter = 0;
	bi.biYPelsPerMeter = 0;
	bi.biClrUsed = 256;

	bi.biClrImportant = 0;
	tagRGBQUAD *RGBQUAD = new tagRGBQUAD;
	//构造调色板数据
	//RGBQUAD:自定义
	RGBQUAD->rgbBlue = temp_B;
	RGBQUAD->rgbGreen = temp_G;
	RGBQUAD->rgbRed = temp_R;
	

	err = fopen_s(&fp, lpszFileName, "wb");//打开临时文件，准备写入文件信息

	if (err !=0)
	{
		printf("D:\\test.bmp此文件被意外删除或无法创建，按任意键退出此程序\n");
		_getch();
		return -1;//临时文件未成功生成
	}

	// 写文件头
	fwrite((char *)&bf, sizeof(BITMAPFILEHEADER), 1, fp);

	// 写BMP图像信息头
	fwrite((char *)&bi, sizeof(BITMAPINFOHEADER), 1, fp);

	// 写调色板
	for (i = 0; i<256; i++)
	{
		fwrite((char *)(RGBQUAD), sizeof(RGBQUAD), 1, fp);//将256个调色盘的颜色信息的RGB均写为RGBQUAD中所存的信息

	}

	for (i = 0; i < Height; i++)
	{
		fwrite((char *)(lpBitmap), 640, 1, fp);//将高度方向上的640个像素，每一行都写成与最低下一行一样的信息
	}
	
	delete(RGBQUAD);

	fclose(fp);//关闭此临时文件

	system("D:\\test.bmp");//利用系统默认的图片显示软件打开此临时图片文件"D:\test.bmp"
	printf("选择的RGB颜色的图片已打开，按任意键继续\n");
	_getch();
	system("cls");//清屏函数
	system("taskkill /f /im dllhost.exe");//强制结束系统默认看图片的进程
	system("cls");//清屏函数
	system("del /f /q D:\\test.bmp");//强制静默删除生成的临时文件"D:\test.bmp"
	system("cls");//清屏函数
	printf("继续输入下一组RGB的待测试值(范围0-255):\n");
	goto m;//使程序循环执行
	return 0;
}
