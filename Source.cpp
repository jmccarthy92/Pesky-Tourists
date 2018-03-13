#include "graphics.h" 
#include <stdio.h>
#include <iostream>
using namespace std;

bool clicked = false;
void draw_Buttons();
void top_Button_Clicked();
void bottom_Buttom_Clicked();
void write_Text();
void loadImage(int imageNumber);
void sortingAlgorithm(int pictureArray[], int n);
void loadPixelArray(int pictureArray[9][200][225] , int imageAmmount, int x, int y);
void putPixelsOnNewImage(int pictureArray[9][200][225], int redColor[], int blueColor[], int greenColor[], int imageAmmount, int xVal, int yVal);
void negativeImageLoad(int pictureArray[200][225], int xVal, int yVal);
void createNegativeImage(int pictureArray[200][225], int xVal, int yVal);
int main()
{
	// All my lovely variables
	int xMouse, yMouse, xMouse2, yMouse2 = 0;
	int count = 0;
	int const xVal = 200;
	int const yVal = 225;
	int const numImages = 9;
	int uiChoice;
	bool loopBreaker = true;
	int redArray[numImages];
	int blueArray[numImages];
	int greenArray[numImages];
	int negArray[xVal][yVal];
	int picArray[numImages][xVal][yVal];
	int firstWindow = initwindow(xVal, yVal, "picture 1");
	int finalWindow = initwindow(xVal, yVal, "final picture");
	const int LIMIT = 10;
	// text interface prompt for the user

	int interfaceWindow = initwindow(800, 600, "interface window");
	setcurrentwindow(interfaceWindow);
	
	
	draw_Buttons();
	write_Text();

	while(count < LIMIT)
	{
		// Made it so you can only click a limit of 10 times !
		getmouseclick(WM_LBUTTONDOWN, xMouse, yMouse);
		if ((xMouse > 200 && xMouse < 400) && (yMouse > 60 && yMouse < 150))
		{
			top_Button_Clicked();
			clearmouseclick(WM_LBUTTONDOWN);
			loadPixelArray(picArray, numImages, xVal, yVal);
			putPixelsOnNewImage(picArray, redArray, blueArray, greenArray, numImages, xVal, yVal);
			setcurrentwindow(firstWindow);
			count++;
		}
	
		if ((xMouse > 200 && xMouse < 400) && (yMouse > 250 && yMouse < 350))
		{
			bottom_Buttom_Clicked();
			clearmouseclick(WM_LBUTTONDOWN);
			negativeImageLoad(negArray, xVal, yVal);
			createNegativeImage(negArray, xVal, yVal);
			setcurrentwindow(finalWindow);
			//cout << "cliecked";
			count++;
		}
		setcurrentwindow(interfaceWindow);
		delay(800);
		draw_Buttons();
	}

	cout << "Choose a Option to use on the Images" << endl;
	cout << " 1) Remove that Pesky Tourist" << endl;
	cout << " 2) Make a negative image " << endl;
	cout << " 3) Exit the program " << endl;
	cin >> uiChoice;

	while (loopBreaker == true)
	{

		switch (uiChoice)
		{
			case 1:   // the option that rmoves the pesky tourist
			
				loadPixelArray(picArray, numImages, xVal, yVal);
				putPixelsOnNewImage(picArray, redArray, blueArray, greenArray, numImages, xVal, yVal);
				setcurrentwindow(firstWindow);
				break;
			case 2:    // the option to make the negative image.
				bottom_Buttom_Clicked();
				negativeImageLoad(negArray, xVal, yVal);
				createNegativeImage(negArray, xVal, yVal);
				setcurrentwindow(finalWindow);
				break;
			case 3:   // closes the program
				cout << " Thank you for using the pesky tourist program, GOODBYE ! :) " << endl;
				loopBreaker = false;
				break;
			default: // default option
				cout << " Please enter a valid UI Choice !!! " << endl;
		}
		//outtextxy(0, 0, "Press any key");
		if (loopBreaker == true)
		{
			cout << "Choose a Option to use on the Images" << endl;
			cout << " 1) Remove that Pesky Tourist" << endl;
			cout << " 2) Make a negative image " << endl;
			cout << " 3) Exit the program " << endl;
			cin >> uiChoice;
		}
		//getch(); //pauses the program
	}
	int x;
	cin >> x;

}

// loads the array for the creation of the negative image in the function after
void write_Text()
{
	outtextxy(400, 75, "Press to get rid of that Pesky Tourist (PeskaTouris)");
	outtextxy(400, 320, "Press to create a negative image :");
}
void top_Button_Clicked()
{
	setfillstyle(SOLID_FILL, GREEN);
	fillellipse(275, 100, 100, 50);
}
void bottom_Buttom_Clicked()
{
	setfillstyle(SOLID_FILL, GREEN);
	fillellipse(275, 300, 100, 50);
}
void draw_Buttons()
{
	/*int points[] = { 320,150,440,340,230,340,320,150 };
	fillpoly(4, points);*/
	setfillstyle(SOLID_FILL, RED);
	fillellipse(275, 100, 100, 50);


	fillellipse(275, 300, 100, 50);

	
}
void negativeImageLoad(int pictureArray[200][225], int xVal, int yVal)
{
	loadImage(3);
	for (int x = 0; x < xVal; x++)
	{
		for (int y = 0; y < yVal; y++)
		{
			pictureArray[x][y] = getpixel(x, y);
		}
	}
}
// creates the negative image from the 2-d array you just loaded into
void createNegativeImage(int pictureArray[200][225], int xVal, int yVal)
{
	for (int x = 0; x < xVal; x++)
	{
		for (int y = 0; y < yVal; y++)
		{
			putpixel(x, y, COLOR((255 - RED_VALUE(pictureArray[x][y])),(255 - GREEN_VALUE(pictureArray[x][y])), (255 - BLUE_VALUE(pictureArray[x][y])) )  );
		}
	}
}
// loads the 3 individual arrays with the rgb values seperately,
// sorts them with the shell sort than sorts them and puts the median value
// in the new image.
// the inner most loop loads the individual arrays with the rgb colors from the 3-d array
// the inner loop sorts them and puts them on the new image. for each x y value.
void putPixelsOnNewImage(int pictureArray[9][200][225], int redColor[], int blueColor[], int greenColor[], int imageAmmount, int xVal, int yVal)
{
	for (int x = 0; x < xVal; x++)
	{
		for (int y = 0; y < yVal; y++)
		{
			for (int p = 0; p < imageAmmount; p++)
			{
				redColor[p] = RED_VALUE(pictureArray[p][x][y]);
				blueColor[p] = BLUE_VALUE(pictureArray[p][x][y]);
				greenColor[p] = GREEN_VALUE(pictureArray[p][x][y]);
			}
			sortingAlgorithm(redColor, imageAmmount);
			sortingAlgorithm(blueColor, imageAmmount);
			sortingAlgorithm(greenColor, imageAmmount);

			putpixel(x, y, COLOR(redColor[4], greenColor[4], blueColor[4]));
		}
	}
}
// loads the 3-d array for the removal of the pesky tourists
// fomr the image uses a nested for loop for each of the 9 images
// the inner for the x values, and the innest most for the y values
void loadPixelArray(int pictureArray[9][200][225] , int imageAmmount, int xVal, int yVal)
{
	for (int p = 0; p < imageAmmount; p++)
	{
		loadImage(p);
		for (int x = 0; x < xVal; x++)
		{
			for (int y = 0; y < yVal; y++)
			{
				pictureArray[p][x][y] = getpixel(x, y);
			}
		}
	}
}
// Uses the shellsort algorithm which is done in O(n*logn) time
// which is quite adequate! no o(n^2) 
void sortingAlgorithm(int pictureArray[], int n)
{
	int inner, outter;
	int temp;

	int h = 1;
	while (h <= n / 3)
		h = h * 3 + 1;
	while (h > 0)
	{
		for (outter = h; outter < n; outter++)
		{
			temp = pictureArray[outter];
			inner = outter;
			while (inner > h - 1 && pictureArray[inner - h] >= temp)
			{
				pictureArray[inner] = pictureArray[inner - h];
				inner -= h;
			}
			pictureArray[inner] = temp;
		}
	h = (h - 1) / 3;
	}
}
void loadImage(int imageNumber)
{
	char str[8];
	sprintf(str, "%i.jpg", imageNumber);
	readimagefile(str, 0, 0, 200, 225); //this is a BGI function that loads the image onto the current window
}