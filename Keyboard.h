/*Copyright (C) 2010 BOILARD Sylvain & PIERRE Cyrille

This file is part of PlayBoard.

PlayBoard is free software: you can redistribute it and/or modify
it under the terms of the GNU General Public License as published by
the Free Software Foundation, either version 3 of the License, or
(at your option) any later version.

PlayBoard is distributed in the hope that it will be useful,
but WITHOUT ANY WARRANTY; without even the implied warranty of
MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
GNU General Public License for more details.

You should have received a copy of the GNU General Public License
along with this program.  If not, see <http://www.gnu.org/licenses/>.*/

//Defining KEYBOARD_HPP_INCLUDE to forbid recursive inclusion.
#ifndef KEYBOARD_HPP_INCLUDE
#define KEYBOARD_HPP_INCLUDE

/*----Preprocessor commands----*/
#include <SFML/Graphics.hpp>
#include <SFML/Window.hpp>
#include <SFML/System.hpp>

//Declaring general namespace.
namespace pb
{

//Declaring class Keyboard.
class Keyboard
{
	//Declaring public methods.
	public:

	//Declaring private attributes.
	private:
	sf::Event m_Event;
};
}

#endif
