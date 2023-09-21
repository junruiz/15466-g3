#include "PlayMode.hpp"

#include "LitColorTextureProgram.hpp"

#include "DrawLines.hpp"
#include "Mesh.hpp"
#include "Load.hpp"
#include "gl_errors.hpp"
#include "data_path.hpp"

#include <glm/gtc/type_ptr.hpp>

#include <random>
#include <iostream>

void drop(Scene::Transform *note, Scene::Transform *r_do, Scene::Transform *r_re, Scene::Transform *r_mi,
          Scene::Transform *r_fa, Scene::Transform *r_sol, Scene::Transform *r_la, Scene::Transform *r_si,
		  Scene::Transform *r_piano) {
	if (r_do->position.x - 5.7f < note->position.x && r_do->position.x + 4.7f > note->position.x &&
	    r_do->position.y - 4.7f < note->position.y && r_do->position.y + 4.7f > note->position.y) {
			if (note->position.z > r_do->position.z + 7.0f + 0.2f) {
				note->position.z -= 0.2f;
			}
			else if (note->position.z > r_do->position.z + 5.0f){
				note->position.z = r_do->position.z + 7.0f;
			}
			return;
		}
	if (r_re->position.x - 5.7f < note->position.x && r_re->position.x + 4.7f > note->position.x &&
	    r_re->position.y - 4.7f < note->position.y && r_re->position.y + 4.7f > note->position.y) {
			if (note->position.z > r_re->position.z + 7.0f + 0.2f) {
				note->position.z -= 0.2f;
			}
			else if (note->position.z > r_re->position.z + 5.0f){
				note->position.z = r_re->position.z + 7.0f;
			}
			return;
		}

	if (r_mi->position.x - 5.7f < note->position.x && r_mi->position.x + 4.7f > note->position.x &&
	    r_mi->position.y - 4.7f < note->position.y && r_mi->position.y + 4.7f > note->position.y) {
			if (note->position.z > r_mi->position.z + 7.0f + 0.2f) {
				note->position.z -= 0.2f;
			}
			else if (note->position.z > r_mi->position.z + 5.0f){
				note->position.z = r_mi->position.z + 7.0f;
			}
			return;
		}
	
	if (r_fa->position.x - 10.0f < note->position.x && r_fa->position.x + 10.0f > note->position.x &&
	    r_fa->position.y - 10.0f < note->position.y && r_fa->position.y + 10.0f > note->position.y) {
			if (note->position.z > r_fa->position.z + 7.0f + 0.2f) {
				note->position.z -= 0.2f;
			}
			else if (note->position.z > r_fa->position.z + 5.0f) {
				note->position.z = r_fa->position.z + 7.0f;
			}
			return;
		}

	if (r_sol->position.x - 5.7f < note->position.x && r_sol->position.x + 4.7f > note->position.x &&
	    r_sol->position.y - 4.7f < note->position.y && r_sol->position.y + 4.7f > note->position.y) {
			if (note->position.z > r_sol->position.z + 7.0f + 0.2f) {
				note->position.z -= 0.2f;
			}
			else if (note->position.z > r_sol->position.z + 5.0f) {
				note->position.z = r_sol->position.z + 7.0f;
			}
			return;
		}

	if (r_la->position.x - 5.7f < note->position.x && r_la->position.x + 4.7f > note->position.x &&
	    r_la->position.y - 4.7f < note->position.y && r_la->position.y + 4.7f > note->position.y) {
			if (note->position.z > r_la->position.z + 7.0f + 0.2f) {
				note->position.z -= 0.2f;
			}
			else if (note->position.z > r_la->position.z + 5.0f) {
				note->position.z = r_la->position.z + 7.0f;
			}
			return;
		}

	if (r_si->position.x - 5.7f < note->position.x && r_si->position.x + 4.7f > note->position.x &&
	    r_si->position.y - 4.7f < note->position.y && r_si->position.y + 4.7f > note->position.y) {
			if (note->position.z > r_si->position.z + 7.0f + 0.2f) {
				note->position.z -= 0.2f;
			}
			else if (note->position.z > r_si->position.z + 5.0f){
				note->position.z = r_si->position.z + 7.0f;
			}
			return;
		}
	if (r_piano->position.x - 19.0f < note->position.x && r_piano->position.x + 11.0f > note->position.x &&
	    r_piano->position.y - 7.0f < note->position.y && r_piano->position.y + 15.0f > note->position.y) {
			if (note->position.z > r_piano->position.z + 9.0f + 0.2f) {
				note->position.z -= 0.2f;
			}
			else if (note->position.z > r_piano->position.z + 7.0f){
				note->position.z = r_piano->position.z + 9.0f;
			}
			return;
		}
	else {
		if (note->position.z > -48.0f) {
			note->position.z -= 0.2f;
		}
	}
	return;
}

GLuint piano_meshes_for_lit_color_texture_program = 0;
Load< MeshBuffer > piano_meshes(LoadTagDefault, []() -> MeshBuffer const * {
	MeshBuffer const *ret = new MeshBuffer(data_path("piano.pnct"));
	piano_meshes_for_lit_color_texture_program = ret->make_vao_for_program(lit_color_texture_program->program);
	return ret;
});

Load< Scene > piano_scene(LoadTagDefault, []() -> Scene const * {
	return new Scene(data_path("piano.scene"), [&](Scene &scene, Scene::Transform *transform, std::string const &mesh_name){
		Mesh const &mesh = piano_meshes->lookup(mesh_name);

		scene.drawables.emplace_back(transform);
		Scene::Drawable &drawable = scene.drawables.back();

		drawable.pipeline = lit_color_texture_program_pipeline;

		drawable.pipeline.vao = piano_meshes_for_lit_color_texture_program;
		drawable.pipeline.type = mesh.type;
		drawable.pipeline.start = mesh.start;
		drawable.pipeline.count = mesh.count;

	});
});

Load< Sound::Sample > star_sample(LoadTagDefault, []() -> Sound::Sample const * {
	return new Sound::Sample(data_path("star.wav"));
});

Load< Sound::Sample > do_sample(LoadTagEarly, []() -> Sound::Sample const * {
	return new Sound::Sample(data_path("do.wav"));
});

Load< Sound::Sample > re_sample(LoadTagEarly, []() -> Sound::Sample const * {
	return new Sound::Sample(data_path("re.wav"));
});

Load< Sound::Sample > mi_sample(LoadTagEarly, []() -> Sound::Sample const * {
	return new Sound::Sample(data_path("mi.wav"));
});

Load< Sound::Sample > fa_sample(LoadTagEarly, []() -> Sound::Sample const * {
	return new Sound::Sample(data_path("fa.wav"));
});

Load< Sound::Sample > sol_sample(LoadTagEarly, []() -> Sound::Sample const * {
	return new Sound::Sample(data_path("sol.wav"));
});

Load< Sound::Sample > la_sample(LoadTagEarly, []() -> Sound::Sample const * {
	return new Sound::Sample(data_path("la.wav"));
});

Load< Sound::Sample > si_sample(LoadTagEarly, []() -> Sound::Sample const * {
	return new Sound::Sample(data_path("si.wav"));
});

PlayMode::PlayMode() : scene(*piano_scene) {
	//get pointers to leg for convenience:
	for (auto &transform : scene.transforms) {
		// std::cout << transform.name;
		if (transform.name == "Sphere.001") note = &transform;
		else if (transform.name == "do") r_do = &transform;
		else if (transform.name == "re") r_re = &transform;
		else if (transform.name == "mi") r_mi = &transform;
		else if (transform.name == "fa") r_fa = &transform;
		else if (transform.name == "sol") r_sol = &transform;
		else if (transform.name == "la") r_la = &transform;
		else if (transform.name == "si") r_si = &transform;
		else if (transform.name == "black1") r_piano = &transform;
	}
	// 	if (transform.name == "Hip.FL") hip = &transform;
	// 	else if (transform.name == "UpperLeg.FL") upper_leg = &transform;
	// 	else if (transform.name == "LowerLeg.FL") lower_leg = &transform;
	// }
	if (note == nullptr) throw std::runtime_error("Character not found.");
	if (r_do == nullptr || r_re == nullptr || r_mi == nullptr || r_fa == nullptr
	    || r_sol == nullptr || r_la == nullptr || r_si == nullptr) {
			throw std::runtime_error("key not found.");
		}
	

	note_org_position = note->position;
	// hip_base_rotation = hip->rotation;
	// upper_leg_base_rotation = upper_leg->rotation;
	// lower_leg_base_rotation = lower_leg->rotation;

	// //get pointer to camera for convenience:
	if (scene.cameras.size() != 1) throw std::runtime_error("Expecting scene to have exactly one camera, but it has " + std::to_string(scene.cameras.size()));
	camera = &scene.cameras.front();

	// //start music loop playing:
	// star_loop = Sound::play(*star_sample, 1.0f, 0.0f);
}

PlayMode::~PlayMode() {
}

bool PlayMode::handle_event(SDL_Event const &evt, glm::uvec2 const &window_size) {

	if (evt.type == SDL_KEYDOWN) {
		if (evt.key.keysym.sym == SDLK_ESCAPE) {
			SDL_SetRelativeMouseMode(SDL_FALSE);
			return true;
		} else if (evt.key.keysym.sym == SDLK_a) {
			keya.downs += 1;
			keya.pressed = true;
			return true;
		} else if (evt.key.keysym.sym == SDLK_d) {
			keyd.downs += 1;
			keyd.pressed = true;
			return true;
		} else if (evt.key.keysym.sym == SDLK_w) {
			keyw.downs += 1;
			keyw.pressed = true;
			return true;
		} else if (evt.key.keysym.sym == SDLK_s) {
			keys.downs += 1;
			keys.pressed = true;
			return true;
		} else if (evt.key.keysym.sym == SDLK_p) {
			next.downs += 1;
			next.pressed = true;
			return true;
		} else if (evt.key.keysym.sym == SDLK_UP) {
			up.downs += 1;
			up.pressed = true;
			return true;
		} else if (evt.key.keysym.sym == SDLK_DOWN) {
			down.downs += 1;
			down.pressed = true;
			return true;
		} else if (evt.key.keysym.sym == SDLK_LEFT) {
			left.downs += 1;
			left.pressed = true;
			return true;
		} else if (evt.key.keysym.sym == SDLK_RIGHT) {
			right.downs += 1;
			right.pressed = true;
			return true;
		}
	} else if (evt.type == SDL_KEYUP) {
		if (evt.key.keysym.sym == SDLK_a) {
			keya.pressed = false;
			return true;
		} else if (evt.key.keysym.sym == SDLK_d) {
			keyd.pressed = false;
			return true;
		} else if (evt.key.keysym.sym == SDLK_w) {
			keyw.pressed = false;
			return true;
		} else if (evt.key.keysym.sym == SDLK_s) {
			keys.pressed = false;
			return true;
		} else if (evt.key.keysym.sym == SDLK_p) {
			next.pressed = false;
			return true;
		} else if (evt.key.keysym.sym == SDLK_UP) {
			up.pressed = false;
			return true;
		} else if (evt.key.keysym.sym == SDLK_DOWN) {
			down.pressed = false;
			return true;
		} else if (evt.key.keysym.sym == SDLK_LEFT) {
			left.pressed = false;
			return true;
		} else if (evt.key.keysym.sym == SDLK_RIGHT) {
			right.pressed = false;
			return true;
		}
	} else if (evt.type == SDL_MOUSEBUTTONDOWN) {
		if (SDL_GetRelativeMouseMode() == SDL_FALSE) {
			SDL_SetRelativeMouseMode(SDL_TRUE);
			return true;
		}
	} else if (evt.type == SDL_MOUSEMOTION) {
		if (SDL_GetRelativeMouseMode() == SDL_TRUE) {
			glm::vec2 motion = glm::vec2(
				evt.motion.xrel / float(window_size.y),
				-evt.motion.yrel / float(window_size.y)
			);
			camera->transform->rotation = glm::normalize(
				camera->transform->rotation
				* glm::angleAxis(-motion.x * camera->fovy, glm::vec3(0.0f, 1.0f, 0.0f))
				* glm::angleAxis(motion.y * camera->fovy, glm::vec3(1.0f, 0.0f, 0.0f))
			);
			return true;
		}
	}

	return false;
}

std::string check_playmusic(Scene::Transform *note, Scene::Transform *r_do, Scene::Transform *r_re, Scene::Transform *r_mi,
          Scene::Transform *r_fa, Scene::Transform *r_sol, Scene::Transform *r_la, Scene::Transform *r_si) {
	if (r_do->position.x - 5.7f < note->position.x && r_do->position.x + 4.7f > note->position.x &&
	    r_do->position.y - 4.7f < note->position.y && r_do->position.y + 4.7f > note->position.y &&
		note->position.z == r_do->position.z + 7.0f) {
			return "do";
		}
	if (r_re->position.x - 5.7f < note->position.x && r_re->position.x + 4.7f > note->position.x &&
	    r_re->position.y - 4.7f < note->position.y && r_re->position.y + 4.7f > note->position.y &&
		note->position.z == r_re->position.z + 7.0f) {
			return "re";
		}

	if (r_mi->position.x - 5.7f < note->position.x && r_mi->position.x + 4.7f > note->position.x &&
	    r_mi->position.y - 4.7f < note->position.y && r_mi->position.y + 4.7f > note->position.y &&
		note->position.z == r_mi->position.z + 7.0f) {
			return "mi";
		}
	
	if (r_fa->position.x - 10.0f < note->position.x && r_fa->position.x + 10.0f > note->position.x &&
	    r_fa->position.y - 10.0f < note->position.y && r_fa->position.y + 10.0f > note->position.y &&
		note->position.z == r_fa->position.z + 7.0f) {
			return "fa";
		}

	if (r_sol->position.x - 5.7f < note->position.x && r_sol->position.x + 4.7f > note->position.x &&
	    r_sol->position.y - 4.7f < note->position.y && r_sol->position.y + 4.7f > note->position.y &&
		note->position.z == r_sol->position.z + 7.0f) {
			return "sol";
		}

	if (r_la->position.x - 5.7f < note->position.x && r_la->position.x + 4.7f > note->position.x &&
	    r_la->position.y - 4.7f < note->position.y && r_la->position.y + 4.7f > note->position.y &&
		note->position.z == r_la->position.z + 7.0f) {
			return "la";
		}

	if (r_si->position.x - 5.7f < note->position.x && r_si->position.x + 4.7f > note->position.x &&
	    r_si->position.y - 4.7f < note->position.y && r_si->position.y + 4.7f > note->position.y &&
		note->position.z == r_si->position.z + 7.0f) {
			return "si";
		}
	return "nothing";
}

void PlayMode::update(float elapsed) {

	//change the note position:

	//move camera:
	{

		//combine inputs into a move:
		constexpr float PlayerSpeed = 30.0f;
		glm::vec3 move = glm::vec3(0.0f);
		glm::vec2 moveCamera = glm::vec2(0.0f);

		if (keya.pressed && !keyd.pressed) move.x = -1.0f;
		if (!keya.pressed && keyd.pressed) move.x = 1.0f;
		if (keys.pressed && !keyw.pressed) move.y = -1.0f;
		if (!keys.pressed && keyw.pressed) move.y = 1.0f;

		if (left.pressed && !right.pressed) moveCamera.x = -1.0f;
		if (!left.pressed && right.pressed) moveCamera.x = 1.0f;
		if (down.pressed && !up.pressed) moveCamera.y = -1.0f;
		if (!down.pressed && up.pressed) moveCamera.y = 1.0f;

		//make it so that moving diagonally doesn't go faster:
		if (move != glm::vec3(0.0f)) move = glm::normalize(move) * PlayerSpeed * elapsed;
		if (moveCamera != glm::vec2(0.0f)) moveCamera = glm::normalize(moveCamera) * PlayerSpeed * elapsed;

		glm::mat4x3 frame = camera->transform->make_local_to_parent();
		glm::vec3 frame_right = frame[0];
		//glm::vec3 up = frame[1];
		glm::vec3 frame_forward = -frame[2];

		camera->transform->position += moveCamera.x * frame_right + moveCamera.y * frame_forward;
		note->position.x += move.x;
		note->position.y += move.y;

		if (next.pressed) {
			note->position.z += 5.0f;
		}

		drop(note, r_do, r_re, r_mi, r_fa, r_sol, r_la, r_si, r_piano);
		std::string key_play = check_playmusic(note, r_do, r_re, r_mi, r_fa, r_sol, r_la, r_si);

		if (next.pressed) locked = false;
		if (key_play != "nothing") {
			auto key_sample = re_sample;
			if (key_play == "do") key_sample = do_sample;
			if (key_play == "re") key_sample = re_sample;
			if (key_play == "mi") key_sample = mi_sample;
			if (key_play == "fa") key_sample = fa_sample;
			if (key_play == "sol") key_sample = sol_sample;
			if (key_play == "la") key_sample = la_sample;
			if (key_play == "si") key_sample = si_sample;

			if (locked == false) {
				key_once = Sound::play(*key_sample, 1.0f, 0.0f);
				locked = true;
			}
		}
	}

	//reset button press counters:
	left.downs = 0;
	right.downs = 0;
	up.downs = 0;
	down.downs = 0;


}

void PlayMode::draw(glm::uvec2 const &drawable_size) {
	//update camera aspect ratio for drawable:
	camera->aspect = float(drawable_size.x) / float(drawable_size.y);

	//set up light type and position for lit_color_texture_program:
	// TODO: consider using the Light(s) in the scene to do this
	glUseProgram(lit_color_texture_program->program);
	glUniform1i(lit_color_texture_program->LIGHT_TYPE_int, 1);
	glUniform3fv(lit_color_texture_program->LIGHT_DIRECTION_vec3, 1, glm::value_ptr(glm::vec3(0.0f, 0.0f,-1.0f)));
	glUniform3fv(lit_color_texture_program->LIGHT_ENERGY_vec3, 1, glm::value_ptr(glm::vec3(1.0f, 1.0f, 0.95f)));
	glUseProgram(0);

	glClearColor(0.5f, 0.5f, 0.5f, 1.0f);
	glClearDepth(1.0f); //1.0 is actually the default value to clear the depth buffer to, but FYI you can change it.
	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

	glEnable(GL_DEPTH_TEST);
	glDepthFunc(GL_LESS); //this is the default depth comparison function, but FYI you can change it.

	scene.draw(*camera);

	{ //use DrawLines to overlay some text:
		glDisable(GL_DEPTH_TEST);
		float aspect = float(drawable_size.x) / float(drawable_size.y);
		DrawLines lines(glm::mat4(
			1.0f / aspect, 0.0f, 0.0f, 0.0f,
			0.0f, 1.0f, 0.0f, 0.0f,
			0.0f, 0.0f, 1.0f, 0.0f,
			0.0f, 0.0f, 0.0f, 1.0f
		));

		constexpr float H = 0.09f;
		lines.draw_text("Press Space to get the song you need to produce",
			glm::vec3(-aspect + 0.1f * H, 0.85f + 0.1f * H, 0.0),
			glm::vec3(H, 0.0f, 1.0f), glm::vec3(0.0f, H, 0.0f),
			glm::u8vec4(0x00, 0x00, 0x00, 0x00));
		lines.draw_text("Use WSAD to land the note on different places to produce sounds! Press P between each sound.",
			glm::vec3(-aspect + 0.1f * H, 0.65f + 0.1f * H, 0.0),
			glm::vec3(H, 0.0f, 0.0f), glm::vec3(0.0f, H, 0.0f),
			glm::u8vec4(0x00, 0x00, 0x00, 0x00));
		float ofs = 2.0f / drawable_size.y;
		lines.draw_text("Press Space to get the song you need to produce",
			glm::vec3(-aspect + 0.1f * H + ofs, 0.85f + + 0.1f * H + ofs, 0.0),
			glm::vec3(H, 0.0f, 0.0f), glm::vec3(0.0f, H, 0.0f),
			glm::u8vec4(0xff, 0xff, 0xff, 0x00));
		lines.draw_text("Use WSAD to land the note on different places to produce sounds! Press P between each sound",
			glm::vec3(-aspect + 0.1f * H + ofs, 0.65 + + 0.1f * H + ofs, 0.0),
			glm::vec3(H, 0.0f, 0.0f), glm::vec3(0.0f, H, 0.0f),
			glm::u8vec4(0xff, 0xff, 0xff, 0x00));
	}
	GL_ERRORS();
}

