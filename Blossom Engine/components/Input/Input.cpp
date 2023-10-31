#include "Input.h"
#include <cassert>
#define XINPUT_GAMEPAD_LEFT_THUMB_DEADZONE  7849
#define XINPUT_GAMEPAD_RIGHT_THUMB_DEADZONE 8689

Input* Input::GetInstance() {
	static Input instance;

	return &instance;
}

void Input::Initialize() {
	// DirectInputの初期化
	HRESULT result;
	result = DirectInput8Create(WinApp::GetInstance()->GetWc(), DIRECTINPUT_VERSION, IID_IDirectInput8,
		(void**)&directInput_, nullptr);
	assert(SUCCEEDED(result));

	// キーボードデバイスの生成
	result = directInput_->CreateDevice(GUID_SysKeyboard, &keyboard_, NULL);
	assert(SUCCEEDED(result));

	// 入力データ形式のセット
	result = keyboard_->SetDataFormat(&c_dfDIKeyboard); // 標準形式
	assert(SUCCEEDED(result));

	// 排他制御レベルのセット
	result = keyboard_->SetCooperativeLevel(
		WinApp::GetInstance()->GetHwnd(), DISCL_FOREGROUND | DISCL_NONEXCLUSIVE | DISCL_NOWINKEY
	);
}

void Input::Update() {
	preKey_ = key_;
	// キーボード情報の取得開始
	keyboard_->Acquire();

	// 全キーの入力状態を取得
	keyboard_->GetDeviceState(sizeof(key_), &key_);
}

bool Input::TriggerKey(BYTE keyNumber) const {
	if (!preKey_[keyNumber] && key_[keyNumber]) {
		return true;
	}
	else {
		return false;
	}
}

bool Input::PressKey(BYTE keyNumber)const {
	if (key_[keyNumber]) {
		return true;
	}
	else {
		return false;
	}
}

bool Input::ReleaseKey(BYTE keyNumber)const {
	if (preKey_[keyNumber] && !key_[keyNumber]) {
		return true;
	}
	else {
		return false;
	}
}

bool Input::GetJoystickState(int32_t stickNo, XINPUT_STATE& state) {
	DWORD result = XInputGetState(stickNo, &state);

	return result == ERROR_SUCCESS;
}

// デッドゾーンを適用する関数
SHORT Input::ApplyDeadzone(SHORT inputValue) {
	if (abs(inputValue) < DEADZONE_THRESHOLD) {
		return 0; // デッドゾーン内の入力は無視
	}
	// デッドゾーン外の入力はそのまま返す
	return inputValue;
}
