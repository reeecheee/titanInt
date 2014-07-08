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
 *  Input: Large numbers are entered into main.cc by the user.
 * 
 *  Output:  Using FLTK, the results of the various arithmetic computations on
 *  titanInts are displayed graphically.
 *
 *  Limitations: The maximum number of digits in a titanInt is limited by the 
 *  range of int.  Some leading zeros that weren't visible in terminal usage have
 *  slipped through to the GUI usage.
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

titanInt helper(const titanInt& x, const titanInt& y);

int main(int argc, char **argv)
{
	string strX = "510941098372987";
	string strY = "510943751090987";

	titanInt x = titanInt(strX);
	titanInt y = titanInt(strY);
	titanInt z = x+y;

	cout << "x = " << x << '\n';
	cout << "y = " << y << '\n';
	cout << "z = " << z << '\n';

	//main window
	Fl_Window *window = new Fl_Window(1024,768);

	//x field
	Fl_Text_Buffer *buff1 = new Fl_Text_Buffer();
	buff1->text(x.toConstChar());
	Fl_Text_Display *disp1 = new Fl_Text_Display(10,20,1000,150,"x");
	disp1->buffer(buff1);

	//operator box
	Fl_Box *box1 = new Fl_Box(FL_UP_BOX,10,180,1000,40,"PLUS");

	//y field
	Fl_Text_Buffer *buff2 = new Fl_Text_Buffer();
	buff2->text(y.toConstChar());
	Fl_Text_Display *disp2 = new Fl_Text_Display(10,245,1000,150,"y");
	disp2->buffer(buff2);

	//equals box
	Fl_Box *box2 = new Fl_Box(FL_UP_BOX,10,410,1000,40,"EQUALS");

	//result field
	Fl_Text_Buffer *buff3 = new Fl_Text_Buffer();
	buff3->text(z.toConstChar());
	Fl_Text_Display *disp3 = new Fl_Text_Display(10,470,1000,230);
	disp3->buffer(buff3);
	
	window->end();
	window->show(argc, argv);
	return Fl::run();
}

