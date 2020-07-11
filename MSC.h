#include <iostream>
#include <vector>
#include <cstdlib>
#include <SFML/Graphics.hpp>
#include <SFML/Audio.hpp>

namespace MSC {
	sf::RenderWindow *window;
	sf::Event event;
	sf::Clock internalClock;
	sf::Time internalTime;
	sf::Color _background = sf::Color::Black;
	
	std::map<std::string, sf::Texture*> resources;
	std::map<std::string, sf::Texture*>::iterator it;
	typedef sf::Keyboard::Key Key;
	typedef sf::Mouse::Button Mouse;
	typedef sf::Vector2i Point;
	typedef sf::Event Event;
	typedef sf::Uint32 Color;
	
	sf::Font font;
	
	void MSCinit() {
		font.loadFromFile("simhei.ttf");
	}
	
	void (*gameFrame)(int ms);
	void (*handleEvent)(Event event) = NULL;
	
	class DrawItem {
		private:
			int z_index;
		public:
			void setZIndex(int z_index) {
				this->z_index = z_index;
			}
			int getZIndex() {
				return this->z_index;
			}
			
			virtual void put(float x = 0, float y = 0) {}
			virtual void remove() {}
			virtual sf::Drawable* getDrawable() {
				return 0;
			}
			
 	};
	bool comp(DrawItem* item1, DrawItem* item2) {
		return (item1->getZIndex()) < (item2->getZIndex());
	}
	

	class DrawAble {
		public:
			std::vector<DrawItem *> drawList;

			DrawAble() {
				
			}
			
			void flush() {
				sort(drawList.begin(), drawList.end(), comp);
			}
			void addDraw(DrawItem *item) {
				drawList.push_back(item);
				flush();
			}
			
			void removeDraw(DrawItem *item) {
				for (int i = 0; i < drawList.size(); i++) {
					if (drawList[i] == item) {
						drawList.erase(drawList.begin()+i);
						break;
					}
				}
				flush();
			}
			
	}drawable;
	
	class Timer {
		private:
			sf::Clock clock;
			int time;
			bool valid;
		public:
			Timer() {
				valid = false;
			}
			void setTime(int t) {
				time = t;
			}
			
			void start() {
				valid = true;
				clock.restart();
			}
			
			int getMs() {
				int pass;
				if (!valid) {
					return -1;
				}
				if((pass = clock.getElapsedTime().asMilliseconds()) > time) {
					valid = false;
					return -1;
				} else {
					return pass;	
				}				
			}
			
			int getS() {
				int pass;
				if (!valid) {
					return -1;
				}
				if ((pass = clock.getElapsedTime().asSeconds()) * 1000 > time) {
					valid = false;
					return -1;
				} else {
					return pass;
				}
			}
 	};
 	
 
	class Image :public DrawItem{
		private:
			sf::Sprite sprite;
			
		public:
			Image() {
				
			}
			Image(char url[]) {
				setImage(url);
			}
			
			void setImage(char url[]) {
				std::string strurl(url);
				it = resources.find(strurl);
				if(it == resources.end()) {
					sf::Texture *texture = new sf::Texture;
					if(!texture->loadFromFile(url)) {
						std::cout << "无法加载图片： " << url << " ，请检查图片是否存在于目录中" << std::endl;
						exit(-1);
					}
					texture->setSmooth(true);
					resources.insert(std::pair<std::string, sf::Texture*>(strurl, texture));
					sprite.setTexture(*texture);
				}else {
					sprite.setTexture(*(it->second));
				}
			}
			
			void put(float x = 0, float y = 0) {
				sprite.setPosition(sf::Vector2f(x, y));
				drawable.addDraw(this);
			}
			
			void remove() {
				drawable.removeDraw(this);
			}
			
			void setPosition(float x, float y) {
				sprite.setPosition(sf::Vector2f(x, y));
			}
			
			float getX() {
				return sprite.getPosition().x;
			}
			
			float getY() {
				return sprite.getPosition().y;
			}
			
			void move(float x, float y) {
				sprite.move(sf::Vector2f(x, y));
			}
			
			void setRotation(float angle) {
				sprite.setRotation(angle);
			}
			
			void rotate(float angle) {
				sprite.rotate(angle);
			}
			
			void setScale(float x, float y) {
				sprite.setScale(sf::Vector2f(x, y));
			}
			
			void scale(float x, float y) {
				sprite.scale(sf::Vector2f(x, y));
			}
			
			void setOrigin(float x, float y) {
				sprite.setOrigin(sf::Vector2f(x, y));
			}
			
			sf::Drawable* getDrawable() {
				return &sprite;
			}
	};
	
	class Text:public DrawItem{
		private:
			sf::Text text;
		
		public:
			Text() {
				text.setFont(font);
			}
			
			Text(sf::String str) {
				text.setFont(font);
				setText(str);
			}
			
			void setText(sf::String str) {
				text.setString(str);
			}
			
			
			
			void setFontSize(int size) {
				text.setCharacterSize(size);
			}
			
			void setColor(sf::Uint32 color) {
				text.setFillColor(sf::Color(color));
			}
			
			void setBold() {
				text.setStyle(sf::Text::Bold);
			}
			
			void setNormal() {
				text.setStyle(sf::Text::Regular);
			}
			
			void put(float x, float y) {
				text.setPosition(x, y);
				drawable.addDraw(this);
			}
			
			void remove() {
				drawable.removeDraw(this);
			}
			
			void setPosition(float x, float y) {
				text.setPosition(sf::Vector2f(x, y));
			}
			
			float getX() {
				return text.getPosition().x;
			}
			
			float getY(){
				return text.getPosition().y;
			}
			 
			void move(float x, float y) {
				text.move(sf::Vector2f(x, y));
			}
			
			void setRotation(float angle) {
				text.setRotation(angle);
			}
			
			void rotate(float angle) {
				text.rotate(angle);
			}
			
			void setScale(float x, float y) {
				text.setScale(sf::Vector2f(x, y));
			}
			
			void scale(float x, float y) {
				text.scale(sf::Vector2f(x, y));
			}
			
			void setOrigin(float x, float y) {
				text.setOrigin(sf::Vector2f(x, y));
			}
			
			sf::Drawable* getDrawable() {
				return &text;
			}
	};
	
	class Circle:public DrawItem{
		private:
			sf::CircleShape shape;
		public:
			Circle(float radius = 10) {
				setRadius(radius);
			}
			
			void setRadius(float radius) {
				shape.setRadius(radius);
			}
			
			void setFill(sf::Uint32 color) {
				shape.setFillColor(sf::Color(color));
			}
			
			void setBorderColor(sf::Uint32 color) {
				shape.setOutlineColor(sf::Color(color));
			}
			
			void setBorderWidth(float width) {
				shape.setOutlineThickness(width);
			}
			
			void put(float x, float y) {
				shape.setPosition(x, y);
				drawable.addDraw(this);
			}
			
			void remove() {
				drawable.removeDraw(this);
			}
			
			void setPosition(float x, float y) {
				shape.setPosition(sf::Vector2f(x, y));
			}
			
			float getX() {
				return shape.getPosition().x;
			}
			
			float getY() {
				return shape.getPosition().y;
			}
			
			void move(float x, float y) {
				shape.move(sf::Vector2f(x, y));
			}
			
			void setRotation(float angle) {
				shape.setRotation(angle);
			}
			
			void rotate(float angle) {
				shape.rotate(angle);
			}
			
			void setScale(float x, float y) {
				shape.setScale(sf::Vector2f(x, y));
			}
			
			void scale(float x, float y) {
				shape.scale(sf::Vector2f(x, y));
			}
			
			void setOrigin(float x, float y) {
				shape.setOrigin(sf::Vector2f(x, y));
			}

			sf::Drawable* getDrawable() {
				return &shape;
			}
	};
	
	class Rectangle:public DrawItem{
		private:
			sf::RectangleShape shape;
		public:
			Rectangle(float width=10, float height=10) {
				setSize(width, height);
			}
			
			void setSize(float width, float height) {
				shape.setSize(sf::Vector2f(width, height));
			}
			
			void setFill(sf::Uint32 color) {
				shape.setFillColor(sf::Color(color));
			}
			
			void setBorderColor(sf::Uint32 color) {
				shape.setOutlineColor(sf::Color(color));
			}
			
			void setBorderWidth(float width) {
				shape.setOutlineThickness(width);
			}
			
			void put(float x, float y) {
				shape.setPosition(x, y);
				drawable.addDraw(this);
			}
			
			void remove() {
				drawable.removeDraw(this);
			}
			
			void setPosition(float x, float y) {
				shape.setPosition(sf::Vector2f(x, y));
			}
			
			float getX() {
				return shape.getPosition().x;
			}
			
			float getY() {
				return shape.getPosition().y;
			}
			
			void move(float x, float y) {
				shape.move(sf::Vector2f(x, y));
			}
			
			void setRotation(float angle) {
				shape.setRotation(angle);
			}
			
			void rotate(float angle) {
				shape.rotate(angle);
			}
			
			
			void setScale(float x, float y) {
				shape.setScale(sf::Vector2f(x, y));
			}
			
			void scale(float x, float y) {
				shape.scale(sf::Vector2f(x, y));
			}
			
			void setOrigin(float x, float y) {
				shape.setOrigin(sf::Vector2f(x, y));
			}
			
			sf::Drawable* getDrawable() {
				return &shape;
			}
	};
	
	class Sound {
		private:
			sf::Music sound;
		public:
			Sound() {
				
			}
			
			void setSound(char url[]) {
				if(!sound.openFromFile(url)) {
					std::cout << "无法打开文件：" << url << " 请检查文件是否存在与路径中！" << std::endl;
					exit(-1); 
				}
			}
			
			void play() {
				sound.play();
			}
			
			void pause() {
				sound.pause();
			}
			
			void stop() {
				sound.stop();
			}
			
			void setLoop(bool loop) {
				sound.setLoop(loop);
			}
	};

	createWindow(int width, int height, char title[]) {
		window = new sf::RenderWindow(sf::VideoMode(width, height), title);
		window->setVerticalSyncEnabled(true);
		window->setFramerateLimit(60); 
	}
	
	setWindowSize(int windth, int height) {
		window->setSize(sf::Vector2u(640, 480));
	}
	
	void hideMouse() {
		window->setMouseCursorVisible(false);
	}
	
	void showMouse() {
		window->setMouseCursorVisible(true);
	}
	
	bool isKeyPress(Key key) {
		return sf::Keyboard::isKeyPressed(key);
	}
	
	bool isMousePress(Mouse button) {
		return sf::Mouse::isButtonPressed(button);
	}
	
	float getMouseX() {
		return sf::Mouse::getPosition(*window).x;
	}
	
	float getMouseY() {
		return sf::Mouse::getPosition(*window).y;
	}
	
	void setBackground(sf::Uint32 color) {
		_background = sf::Color(color);
	}
	
	
	
	void render() {
		for(int i = 0; i < drawable.drawList.size(); i++) {
			window->draw(*(drawable.drawList[i]->getDrawable()));
		}
	}
	
	
	void gameLoop(void (*framefun)(int ms) = NULL, void (*eventfun)(Event event) = NULL) {
		gameFrame = framefun;
		handleEvent = eventfun;
		internalClock.restart();
		while (window->isOpen()) {
			
			if(gameFrame != NULL)
				gameFrame(internalTime.asMilliseconds());
			
        	while (window->pollEvent(event))
        	{
           		if (event.type == sf::Event::Closed)
                	window->close();
                if(handleEvent != NULL)
                	handleEvent(event);
      	  	}
        	window->clear(_background);
        	
        	render();
        	
        	window->display();
        	internalTime = internalClock.getElapsedTime();
        	internalClock.restart();
		}
	}
}
