#include "DebugDisplay.h"

DebugDisplay* DebugDisplay::pInstance = nullptr;

DebugDisplay::DebugDisplay()
	: player(nullptr)
	, camera(nullptr)
	, input(nullptr)
{
		
}

void DebugDisplay::CreateInstance() {
	pInstance = new DebugDisplay();
}

DebugDisplay* DebugDisplay::GetInstance() {
	if (pInstance == nullptr) {
		CreateInstance();
	}
	return pInstance;
}

void DebugDisplay::DestroyInstance() {

}

void DebugDisplay::Update()
{
}

void DebugDisplay::Render()
{	
	if(input != nullptr){
		DrawFormatString(0, 20, red, L"LeftStickAxisX:%d", input->GetXinput().ThumbLX);
		DrawFormatString(0, 40, red, L"LeftStickAxisY:%d", input->GetXinput().ThumbLY);
		DrawFormatString(0, 60, red, L"RightStickAxisX:%d", input->GetXinput().ThumbRX);
		DrawFormatString(0, 80, red, L"RihgtStickAxisY:%d", input->GetXinput().ThumbRY);
		DrawFormatString(0, 100, red, L"LeftTrigger:%d", input->GetXinput().LeftTrigger);
		DrawFormatString(0, 120, red, L"RightTrigger:%d", input->GetXinput().RightTrigger);
	}

	if(player != nullptr){
		DrawFormatString(100, 0, red, L"X:%f, Y:%f, Z:%f", player->GetPosition().x, player->GetPosition().y, player->GetPosition().z);
	}

	if(camera != nullptr){
		DrawFormatString(0, 200, red, L"Camera.position : %.2f, %.2f, %.2f,", camera->GetPosition().x, camera->GetPosition().y, camera->GetPosition().z);
		DrawFormatString(0, 220, red, L"Camera.rotation : %.2f, %.2f, %.2f,", camera->GetRotation().x, camera->GetRotation().y, camera->GetRotation().z);
	}
}
