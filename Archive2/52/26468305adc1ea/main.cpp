#include <SFML/Graphics.hpp>
#include <SFML\Window.hpp>
#include <iostream>
#include <string>
#include <Windows.h>

using namespace sf;
using namespace std;

char letter1 = '_';
char letter2 = '_';
char letter3 = '_';
char letter4 = '_';
Text letterbank;
int bodyParts = 7;

void handleInputs(sf::Keyboard::Key key, bool isPressed)
{
    if (key == sf::Keyboard::W && isPressed == true)
	{
		letter1 = 'W';
		letterbank.setString(" \t" + String(letter1) + " " + letter2 + " " + letter3 + " " + letter4);
	}
	else if (key == sf::Keyboard::O && isPressed == true)
	{
		letter2 = 'o';
		letterbank.setString(" \t" + String(letter1) + " " + letter2 + " " + letter3 + " " + letter4);
	}
	else if (key == Keyboard::R && isPressed == true)
	{
		letter3 = 'r';
		letterbank.setString(" \t" + String(letter1) + " " + letter2 + " " + letter3 + " " + letter4);
	}
	else if (key == Keyboard::D && isPressed == true)
	{
		letter4 = 'd';
		letterbank.setString(" \t" + String(letter1) + " " + letter2 + " " + letter3 + " " + letter4);
	}
	else {
		bodyParts -= 1;
	}
}

int main()
{
	static String WORD = "word";



	bool drawHead		= false;
	bool drawBody		= false;
	bool drawRightArm	= false;
	bool drawLeftArm	= false;
	bool drawRightLeg	= false;
	bool drawLeftLeg	= false;

	int xoffset = 150;
	int yoffset = 50;

	bool playing = true;
	//bool inputLetter = false;

	RenderWindow window(VideoMode(400, 400), "Hangman - through the might of SFML");

	// Word Bank
	sf::Font font;
	if (!font.loadFromFile("arial.ttf"))
	{
		// error...
	}

	Text letterbankText;
	letterbankText.setFont(font);
	letterbankText.setString("---LETTER BANK---");
	letterbankText.setCharacterSize(14);
	letterbankText.setColor(Color::White);
	letterbankText.setPosition(0, 50);


	letterbank.setFont(font);
	letterbank.setString(" \t _ _ _ _ ");
	letterbank.setCharacterSize(14);
	letterbank.setColor(Color::White);
	letterbank.setPosition(0, 75);


	// Hangman character
	CircleShape head(50.f);
	head.setFillColor(Color::Green);
	head.setPosition(xoffset, yoffset + 0);

	RectangleShape body(Vector2f(10, 90));
	body.setPosition(xoffset + 45, yoffset + 100);
	body.setFillColor(Color::Blue);

	RectangleShape rightArm(Vector2f(60, 10));
	rightArm.setPosition(xoffset + 55, yoffset + 120);
	rightArm.setFillColor(Color::Magenta);

	RectangleShape leftArm(Vector2f(60, 10));
	leftArm.setPosition(xoffset - 15, yoffset + 120);
	leftArm.setFillColor(Color::Yellow);

	RectangleShape leftLeg(Vector2f(60, 10));
	leftLeg.setPosition(xoffset - 15 + 65, yoffset + 190);
	leftLeg.setFillColor(Color::White);
	leftLeg.rotate(135);

	RectangleShape rightLeg(Vector2f(60, 10));
	rightLeg.setPosition(xoffset - 15 + 75, yoffset + 182.5);
	rightLeg.setFillColor(Color::Cyan);
	rightLeg.rotate(45);


	while (window.isOpen())
	{
		window.clear();
		Event event;
		while (window.pollEvent(event))
		{
			if (event.type == Event::Closed)
				window.close();
			if (event.type == Event::KeyPressed)
				handleInputs(event.key.code, true);
		}


		switch (bodyParts){
		case 6:
			drawHead = true;
			break;
		case 5:
			drawBody = true;
			break;
		case 4:
			drawLeftArm = true;
			break;
		case 3:
			drawRightArm = true;
			break;
		case 2:
			drawLeftLeg = true;
			break;
		case 1:
			drawRightLeg = true;
			break;
		default:
			;//cout << bodyParts;
		}


		window.draw(letterbankText);
		window.draw(letterbank);
		if (drawHead) window.draw(head);
		if (drawBody) window.draw(body);
		if (drawRightArm) window.draw(rightArm);
		if (drawLeftArm) window.draw(leftArm);
		if (drawRightLeg) window.draw(rightLeg);
		if (drawLeftLeg) window.draw(leftLeg);

		window.display();
	}


	return 0;
}