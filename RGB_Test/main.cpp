#include<stdio.h>
#include<conio.h>
#include<stdlib.h>
#include <windows.h>
#define WIDTHBYTES(i)((i+31)/32*4)

int main()
{
	errno_t err;
	FILE    *fp = NULL;
	char* lpszFileName = "D:\\test.bmp";//���ɵ���ʱ�ļ���λ�ú�����

	int temp_R=0, temp_G=0, temp_B=0;
	printf("��ΪJXL�Ƶ�RGB��ɫ��ʾ��������������RGB��ֵ(��Χ0-255):\n");

    m:;

	printf("R=");
	scanf_s("%d", &temp_R,200);
	printf("G=");
	scanf_s("%d", &temp_G,200);
	printf("B=");
	scanf_s("%d", &temp_B,200);

	if (!(temp_R >= 0 && temp_R <= 255 && temp_G >= 0 && temp_G <= 255 && temp_B >= 0 && temp_B <= 255))
	{
		printf("�����RGB��ֵ�ķ�Χ��������������\n");
		goto m;//��������ݷ�Χ���󣬷���������������
	}



	int Width = 640, Height = 640;//���ɵ���ʱ�ļ�ͼƬ��С(����)Ϊ640*640��
	
	BITMAPFILEHEADER   bf;
	BITMAPINFOHEADER   bi;
	int             lineBytes = 0;
	int             i=0;

	char   lpBitmap[640];

	for (i = 0; i<640; i++)
	{
		lpBitmap[i] = 0;//д��ÿһ��640����������Ӧ�ĵ�ɫ�̴���
	}

	lineBytes = (int)WIDTHBYTES(Width * 8);

	//����bmp�ļ�ͷ��Ϣ
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
	//�����ɫ������
	//RGBQUAD:�Զ���
	RGBQUAD->rgbBlue = temp_B;
	RGBQUAD->rgbGreen = temp_G;
	RGBQUAD->rgbRed = temp_R;
	

	err = fopen_s(&fp, lpszFileName, "wb");//����ʱ�ļ���׼��д���ļ���Ϣ

	if (err !=0)
	{
		printf("D:\\test.bmp���ļ�������ɾ�����޷���������������˳��˳���\n");
		_getch();
		return -1;//��ʱ�ļ�δ�ɹ�����
	}

	// д�ļ�ͷ
	fwrite((char *)&bf, sizeof(BITMAPFILEHEADER), 1, fp);

	// дBMPͼ����Ϣͷ
	fwrite((char *)&bi, sizeof(BITMAPINFOHEADER), 1, fp);

	// д��ɫ��
	for (i = 0; i<256; i++)
	{
		fwrite((char *)(RGBQUAD), sizeof(RGBQUAD), 1, fp);//��256����ɫ�̵���ɫ��Ϣ��RGB��дΪRGBQUAD���������Ϣ

	}

	for (i = 0; i < Height; i++)
	{
		fwrite((char *)(lpBitmap), 640, 1, fp);//���߶ȷ����ϵ�640�����أ�ÿһ�ж�д���������һ��һ������Ϣ
	}
	
	delete(RGBQUAD);

	fclose(fp);//�رմ���ʱ�ļ�

	system("D:\\test.bmp");//����ϵͳĬ�ϵ�ͼƬ��ʾ����򿪴���ʱͼƬ�ļ�"D:\test.bmp"
	printf("ѡ���RGB��ɫ��ͼƬ�Ѵ򿪣������������\n");
	_getch();
	system("cls");//��������
	system("taskkill /f /im dllhost.exe");//ǿ�ƽ���ϵͳĬ�Ͽ�ͼƬ�Ľ���
	system("cls");//��������
	system("del /f /q D:\\test.bmp");//ǿ�ƾ�Ĭɾ�����ɵ���ʱ�ļ�"D:\test.bmp"
	system("cls");//��������
	printf("����������һ��RGB�Ĵ�����ֵ(��Χ0-255):\n");
	goto m;//ʹ����ѭ��ִ��
	return 0;
}
