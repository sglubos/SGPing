#include "Ball.h"
#include "Game.h"
#include <iostream>

namespace sgping {

	Ball::Ball(GLfloat *ball_matrix, rectangle collision_box) {
		this->matrix = ball_matrix;
		this->collision_box = collision_box;
	}

	void Ball::update() {
		//vertical movement
		bool daw = false;

		collision_box.y -= velocity_y;

		if (collides_rectangle(&collision_box, &(Game::bottom.collision_box))) {
			collision_box.y += velocity_y;

			collision_box.y = Game::bottom.collision_box.y - (Game::bottom.collision_box.h_height + collision_box.h_height);

			velocity_y = -velocity_y;
			daw = true;
		}
		else if (collides_rectangle(&collision_box, &Game::top.collision_box)) {
			collision_box.y += velocity_y;

			collision_box.y = Game::top.collision_box.y + (Game::top.collision_box.h_height + collision_box.h_height);

			velocity_y = -velocity_y;
			daw = true;
		}

		if (out_of_area(&collision_box)) {
			collision_box.y = physics_height / 2;
		}

		//horizontal movement
		collision_box.x += velocity_x;
		if (collides_edge(&collision_box)) {
			collision_box.x -= velocity_x;
			if (velocity_x > 0) {
				collision_box.x = physics_width - collision_box.h_width;
			}
			else if (velocity_x < 0) {
				collision_box.x = collision_box.h_width;
			}

			velocity_x = -velocity_x;
		}

		matrix[12] = toOpenglCoords(collision_box.x, true);
		matrix[13] = toOpenglCoords(collision_box.y, false);
	}
}