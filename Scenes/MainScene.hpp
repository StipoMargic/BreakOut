//
// Created by stipo on 15. 04. 2020..
//

#ifndef BREAK_OUT_SCENES_MAINSCENE_HPP_
#define BREAK_OUT_SCENES_MAINSCENE_HPP_

#include "Scene.hpp"
#include <memory>
class Screen;

enum eScene {
	INTRO = 0,
	GAME,
	CREDITS
};

class MainScene : public Scene
{
 public:
	MainScene();
	virtual void Init() override;
	virtual void Update(uint32_t dt) override;
	virtual void Draw(Screen& theScreen) override;
	virtual std::string GetSceneName() const override;
 private:
	std::unique_ptr<Scene> GetScene(eScene scene);
};

#endif //BREAK_OUT_SCENES_MAINSCENE_HPP_
