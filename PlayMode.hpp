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
	} left, right, down, up, keya, keyw, keyd, keys, next, space, restart;

	//local copy of the game scene (so code can change it during gameplay):
	Scene scene;
	
	//camera:
	Scene::Camera *camera = nullptr;

	//meshes:
	Scene::Transform *note = nullptr;
	Scene::Transform *r_do = nullptr;
	Scene::Transform *r_re = nullptr;
	Scene::Transform *r_mi = nullptr;
	Scene::Transform *r_fa = nullptr;
	Scene::Transform *r_sol = nullptr;
	Scene::Transform *r_la = nullptr;
	Scene::Transform *r_si = nullptr;
	Scene::Transform *r_piano = nullptr;
	
	glm::vec3 note_org_position;

	//state:
	bool state[6][7] = {
		{false, false, false, false, false, false, false},
        {false, false, false, false, false, false, false},
        {false, false, false, false, false, false, false},
        {false, false, false, false, false, false, false},
        {false, false, false, false, false, false, false},
        {false, false, false, false, false, false, false}
	};

	std::string rhythm[6][7] = {
        {"do", "do", "sol", "sol", "la", "la", "sol"},
        {"fa", "fa", "mi", "mi", "re", "re", "do"},
        {"sol", "sol", "fa", "fa", "mi", "mi", "re"},
        {"sol", "sol", "fa", "fa", "mi", "mi", "re"},
        {"do", "do", "sol", "sol", "la", "la", "sol"},
        {"fa", "fa", "mi", "mi", "re", "re", "do"}
    };
	//
	std::shared_ptr< Sound::PlayingSample > star_loop;

	std::shared_ptr< Sound::PlayingSample > key_once;

	std::shared_ptr< Sound::PlayingSample > part_once;

	bool locked = false;
	bool playSuccessSong = false;
	bool SuccessSongPlaying = false;
	bool lose = false;

	std::string message = "";
};
