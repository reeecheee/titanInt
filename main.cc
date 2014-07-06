/*! \mainpage
 *  Object-oriented Programming in C++, Professor Doug Ferguson \n
 *  JHU EP, Summer 2014 \n
 *  20140629, Mike Ricci \n\n
 *  HW4: Huge Int \n
 *	 main.cc
 * 
 *  This program makes use of the class titanInt ("titantic integer") to add,
 *  subtract, multiply, and divide very large integer numbers.
 * 
 *  Input: Large numbers are entered into the main.cc by the user.
 * 
 *  Output:  Using FLTK, the results of the various arithmetic computations on
 *  titanInts are displayed graphically.
 *
 *  Limitations: The maximum number of digits in a titanInt is limited by the 
 *  range of int.  Integers in elements of vector digits (out of bounds of the
 *  elements used to store digits) accumulate.  They do not affect calculations 
 *  (in most cases) but it is not intended and I was unable to diagnose the 
 *  cause of or resolve the issue.
 * 
 */

#include <iostream>
#include <FL/Fl.H>
#include <FL/Fl_Window.H>
#include <FL/Fl_Text_Buffer.H>
#include <FL/Fl_Text_Display.H>
#include <FL/Fl_Light_Button.H>
#include <FL/Fl_Box.H>
#include "titanInt.h"

using namespace std;

int main(int argc, char **argv)
{
	string str = "175";
	int num = 6;

	titanInt x = titanInt(str);
	titanInt y = titanInt(num);
	titanInt z = x*y;

	cout << "x = " << x << '\n';
	cout << "y = " << y << '\n';
	cout << "x * y = " << z << '\n';
	
/*	cout << "size: " << z.getSize() << '\n';
	cout << z.getDigit(0) << ' ';
	cout << z.getDigit(1) << ' ';
	cout << z.getDigit(2) << ' ';
	cout << z.getDigit(3) << ' ';
	cout << z.getDigit(4) << ' ';
	cout << z.getDigit(5) << '\n';*/
		
/*	cout << (x<y) << '\n';
	cout << (x>y) << '\n';
	cout << (x==y) << '\n';*/

/*	cout << x.getDigit(0) << ' ';
	cout << x.getDigit(1) << ' ';
	cout << x.getDigit(2) << ' ';
	cout << x.getDigit(3) << ' ';
	cout << x.getDigit(4) << ' ';
	cout << x.getDigit(5) << ' ';
	cout << x.getDigit(6) << ' ';

	cout << '\n' << x.getSize() << '\n';

	cout << z.getDigit(0) << ' ';
	cout << z.getDigit(1) << ' ';
	cout << z.getDigit(2) << ' ';
	cout << z.getDigit(3) << ' ';
	cout << z.getDigit(4) << ' ';
	cout << z.getDigit(5) << ' ';
	cout << z.getDigit(6) << ' ';

	cout << '\n' << z.getSize() << '\n';*/

	//main window
	Fl_Window *window = new Fl_Window(1024,768);

	//x field
	Fl_Text_Buffer *buff1 = new Fl_Text_Buffer();
	buff1->text(x.toConstChar());
	Fl_Text_Display *disp1 = new Fl_Text_Display(10,20,1000,150,"titanInt1");
	disp1->buffer(buff1);

	//operator buttons
	Fl_Light_Button *butt1 = new Fl_Light_Button(190,180,150,40,"plus");
	Fl_Light_Button *butt2 = new Fl_Light_Button(350,180,150,40,"minus");
	Fl_Light_Button *butt3 = new Fl_Light_Button(510,180,150,40,"multiplied by");
	Fl_Light_Button *butt4 = new Fl_Light_Button(670,180,150,40,"divided by");

	//y field
	Fl_Text_Buffer *buff2 = new Fl_Text_Buffer();
	buff2->text(y.toConstChar());
	Fl_Text_Display *disp2 = new Fl_Text_Display(10,245,1000,150,"titanInt2");
	disp2->buffer(buff2);

	//equals box
	Fl_Box *box1 = new Fl_Box(FL_UP_BOX,10,410,1000,40,"EQUALS");

	//result field
	Fl_Text_Buffer *buff3 = new Fl_Text_Buffer();
	buff3->text(z.toConstChar());
	Fl_Text_Display *disp3 = new Fl_Text_Display(10,470,1000,230);
	disp3->buffer(buff3);
	
	window->end();
	window->show(argc, argv);
	return Fl::run();
	
	//return 0;
}

