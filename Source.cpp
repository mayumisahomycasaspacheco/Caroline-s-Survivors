#include <iostream>
#include <conio.h>
#include <Windows.h>
using namespace std;
using namespace System;

void casita(int x, int y)
{
	string lineas[28] = {

"                            [[[|]]]    ",
"                    !!!!!!!!|--_--|!!!!!",
"                    [[[[[[[[\\_(X)_/]]]]]",
"            .-.     /-_--__-/_--_-\\-_--\\ ",
"            |=|    /-_---__/__-__-_\\__-_\\ ",
"        . . |=| ._/-__-__\\===========/-__\\_",
"        !!!!!!!!!\\========[ /]]|[[\\ ]=====/",
"       /-_--_-_-_[[[[[[[[[||==  == ||]]]]]]",
"      /-_--_--_--_|=  === ||=/^|^\\ ||== =|",
"     /-_-/^|^\\-_--| /^|^\\=|| | | | ||^\\= |",
"    /_-_-| | |-_--|=| | | ||=|_|_|=|| |==|",
"   /-__--|_|_|_-_-| |_|_|=||______=||_| =|",
"  /_-__--_-__-___-|_=__=_.`---------'._=_|__",
" /-----------------------\\===========/-----/",
"^^^\\^^^^^^^^^^^^^^^^^^^^^^[[|]]|[[|]]=====/",
"    |.' ..==::' '::==.. '.[/ ~~~~~\\]] ] ] ]",
"    | .'=[[[|]]|[[|]]]=`._||==  =  || =\\ ]",
"    ||== =|/ _____ \\|== = ||=/^|^\\=||^\\ ||",
"    || == `||-----||' = ==|| | | |=|| |=||",
"    ||= == ||:^M^:|| = == ||=| | | || |=||",
"    || = = ||:___:||= == =|| |_|_| ||_|=||",
"   _||_ = =||o---.|| = ==_||_= == =||==_||_",
"   \\__/= = ||:   :||= == \\__/[][][][][]\\__/",
"   [||]= ==||:___:|| = = [||]\\\\//\\\\//\\\\[||]",
"   }  {---' '-----' '- --}  {//\\\\//\\\\//}  {",
" __[==]__________________[==]\\\\//\\\\//\\\\[==]_",
"|`|~~~~|================|~~~~|~~~~~~~~|~~~~||",
"| |    |================|    |        |    ||"
	};

	Console::SetCursorPosition(x, y);
	cout << lineas[0];
	Console::SetCursorPosition(x, y + 1);
	cout << lineas[1];
	Console::SetCursorPosition(x, y + 2);
	cout << lineas[2];
	Console::SetCursorPosition(x, y + 3);
	cout << lineas[3];
	Console::SetCursorPosition(x, y + 4);
	cout << lineas[4];
	Console::SetCursorPosition(x, y + 5);
	cout << lineas[5];
	Console::SetCursorPosition(x, y + 6);
	cout << lineas[6];
	Console::SetCursorPosition(x, y + 7);
	cout << lineas[7];
	Console::SetCursorPosition(x, y + 8);
	cout << lineas[8];
	Console::SetCursorPosition(x, y + 9);
	cout << lineas[9];
	Console::SetCursorPosition(x, y + 10);
	cout << lineas[10];
	Console::SetCursorPosition(x, y + 11);
	cout << lineas[11];
	Console::SetCursorPosition(x, y + 12);
	cout << lineas[12];
	Console::SetCursorPosition(x, y + 13);
	cout << lineas[13];
	Console::SetCursorPosition(x, y + 14);
	cout << lineas[14];
	Console::SetCursorPosition(x, y + 15);
	cout << lineas[15];
	Console::SetCursorPosition(x, y + 16);
	cout << lineas[16];
	Console::SetCursorPosition(x, y + 17);
	cout << lineas[17];
	Console::SetCursorPosition(x, y + 18);
	cout << lineas[18];
	Console::SetCursorPosition(x, y + 19);
	cout << lineas[19];
	Console::SetCursorPosition(x, y + 20);
	cout << lineas[20];
	Console::SetCursorPosition(x, y + 21);
	cout << lineas[21];
	Console::SetCursorPosition(x, y + 22);
	cout << lineas[22];
	Console::SetCursorPosition(x, y + 23);
	cout << lineas[23];
	Console::SetCursorPosition(x, y + 24);
	cout << lineas[24];
	Console::SetCursorPosition(x, y + 25);
	cout << lineas[25];
	Console::SetCursorPosition(x, y + 26);
	cout << lineas[26];
	Console::SetCursorPosition(x, y + 27);
	cout << lineas[27];
}

int main()
{

	casita(20, 1);

	_getch();
	return 0;
}
