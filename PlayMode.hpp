#include "Mode.hpp"

#include "Scene.hpp"
#include "Sound.hpp"

#include <glm/glm.hpp>

#include <vector>
#include <deque>

struct PlayMode : Mode {
	PlayMode();
	virtual ~PlayMode();

	//functions called by main loop:
	virtual bool handle_event(SDL_Event const &, glm::uvec2 const &window_size) override;
	virtual void update(float elapsed) override;
	virtual void draw(glm::uvec2 const &drawable_size) override;

	//----- game state -----

	//input tracking:
	struct Button {
		uint8_t downs = 0;
		uint8_t pressed = 0;
	} left, right, down, up;

	//local copy of the game scene (so code can change it during gameplay):
	Scene scene;
	
	//camera:
	Scene::Camera *camera = nullptr;

	//state:
	bool state[6][7] = {false};

	std::string rhythm[6][7] = {
        {"do", "do", "sol", "sol", "la", "la", "sol"},
        {"fa", "fa", "mi", "mi", "re", "re", "do"},
        {"sol", "sol", "fa", "fa", "mi", "mi", "re"},
        {"sol", "sol", "fa", "fa", "mi", "mi", "re"},
        {"do", "do", "sol", "sol", "la", "la", "sol"},
        {"fa", "fa", "mi", "mi", "re", "re", "do"}
    };
	//
};
