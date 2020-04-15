//
// Created by stipo on 15. 04. 2020..
//

#ifndef BREAK_OUT_SCENES_SCENE_HPP_
#define BREAK_OUT_SCENES_SCENE_HPP_

#include <string>
#include <cstdint>

class Screen;
class Scene
{
 public:
	virtual ~Scene()
	{
	}

	virtual void Init() = 0;
	virtual void Update(uint32_t dt) = 0;
	virtual void Draw(Screen& theScreen) = 0;
	virtual std::string GetSceneName() const = 0;
};

#endif //BREAK_OUT_SCENES_SCENE_HPP_
