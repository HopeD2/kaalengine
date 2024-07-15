#include <SFML/Graphics.hpp>
#include <iostream>

const float GRAVITY = 981.f; // Gravity in game units per second squared
const float JUMP_VELOCITY = -500.f; // Initial jump velocity (negative because up is usually negative y)
const float GROUND_LEVEL = 500.f; // Y coordinate of the ground

void customMove(sf::RectangleShape &body, sf::Vector2f velocity, float dt) 
{
	std::cout << "deltaTime: " << dt << " final: " << velocity.y * dt << "\n";
	body.move(velocity * dt);
}

int _main() {
	sf::RenderWindow window(sf::VideoMode(800, 600), "Jump Simulation");
	sf::RectangleShape body(sf::Vector2f(50, 50));
	//body.setPosition(375, GROUND_LEVEL - 50); // Start on the ground
	sf::Vector2f velocity(0.f, 0.f);
	bool isJumping = false;
	sf::Clock clock; // Starts the clock

	while (window.isOpen()) {
		sf::Event event;
		while (window.pollEvent(event)) {
			if (event.type == sf::Event::Closed) {
				window.close();
			}

			if (event.type == sf::Event::KeyPressed) {
				if (event.key.code == sf::Keyboard::Space && !isJumping) {
					// Start a jump
					velocity.y = JUMP_VELOCITY;
					isJumping = true;
				}
			}
		}

		sf::Time elapsed = clock.restart(); // Get the time elapsed since the last frame
		float deltaTime = elapsed.asSeconds();

		// Apply gravity
		if (isJumping) {
			velocity.y += GRAVITY * deltaTime;
			std::cout << "velocity.y " << velocity.y << "\n";
		}

		// Move the body according to the updated velocity
		customMove(body, sf::Vector2f(0, velocity.y), deltaTime);
		//body.move(0, velocity.y * deltaTime);

		// Check for ground collision
		if (body.getPosition().y + body.getSize().y >= GROUND_LEVEL) {
			body.setPosition(body.getPosition().x, GROUND_LEVEL - body.getSize().y);
			velocity.y = 0;
			isJumping = false;
		}

		// Other game logic and rendering
		window.clear();
		window.draw(body);
		window.display();
	}

	return 0;
}
