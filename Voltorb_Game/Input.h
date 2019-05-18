#pragma once
class Input
{

	struct Mouse {

		int pos[2];
		bool button[2];
	};

public:
	Input();
	~Input();

	void Update();

	void SetKeyDown(unsigned char key);
	void SetKeyUp(unsigned char key);
	bool IsKeyDown(int key);
	bool OnKeyPressed(int key);
	bool OnKeyReleased(int key);



private:

	bool keys_[256];
	bool prev_[256];

	Mouse mouse_;
};

