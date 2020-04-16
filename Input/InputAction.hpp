//
// Created by stipo on 16. 04. 2020..
//

#ifndef BREAK_OUT_INPUT_INPUTACTION_HPP_
#define BREAK_OUT_INPUT_INPUTACTION_HPP_
#include <cstdint>
#include <functional>

typedef uint8_t InputKey;
typedef uint8_t InputState;

typedef std::function<void(uint32_t dt, InputState)> InputAction;

struct ButtonAction
{
	InputKey key;
	InputAction action;
};

#endif //BREAK_OUT_INPUT_INPUTACTION_HPP_
