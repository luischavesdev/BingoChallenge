#pragma once

// Proper state machine would be the way to go, but this works for now.
enum State
{
	S_Down = 0, S_Shuffle, S_Draw, S_Extra
};