#pragma once
#ifndef COMMAND_H
#define COMMAND_H

#include "AnimTime.h"

using namespace Azul;

class Command
{
public:
	Command() = default;
	virtual ~Command() = default;
	Command(const Command&) = delete;
	Command& operator=(const Command&) = delete;


	virtual void Execute(AnimTime delta) = 0;

};
#endif // !COMMAND_H
