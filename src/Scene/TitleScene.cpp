#include "TitleScene.h"
#include "../Manager/InputManager.h"
#include "../Manager/SceneManager.h"

#include "../Manager/FadeManager.h"
#include "../Manager/AudioManager.h"

TitleScene::TitleScene()
	:BaseScene()
	, changed(false)
{
	Start();
}

TitleScene::~TitleScene()
{
}

void TitleScene::Start()
{
	// ‰¹‚Ì“Ç‚Ýž‚Ý
	AudioManager::GetInstance()->Load("Res/Audio/SE/maou_se_system49.wav", "OK", false);
}

void TitleScene::Update()
{
	if (InputManager::GetInstance()->IsKeyDown(KEY_INPUT_SPACE)) {
		changed = true;
		// AudioManager::GetInstance()->PlayOneShot("OK");
		FadeManager::GetInstance()->FadeOut();
	}

	if (changed && FadeManager::GetInstance()->GetFadeState() == FadeState::FadeEnd) {
		SceneManager::GetInstance()->SetNext(SceneType::Game);
		FadeManager::GetInstance()->FadeIn();
	}

}

void TitleScene::Render()
{
	DrawString(0, 0, "TitleScene", red);
}
