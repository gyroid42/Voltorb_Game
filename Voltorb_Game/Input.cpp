#include "pch.h"
#include "Input.h"


Input::Input()
{
}


Input::~Input()
{
}



void Input::Update() {


	std::memcpy(prev_, keys_, 256 * sizeof(bool));
}


void Input::SetKeyDown(unsigned char key) {

	keys_[key] = true;
}

void Input::SetKeyUp(unsigned char key) {

	keys_[key] = false;
}

bool Input::IsKeyDown(int key) {

	return keys_[key];
}

bool Input::OnKeyPressed(int key) {

	return (keys_[key] && !prev_[key]);
}

bool Input::OnKeyReleased(int key) {

	return (!keys_[key] && prev_[key]);
}



