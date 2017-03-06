//==========================================================
//SignPostAllocator.hpp
//==========================================================
#pragma once
#ifndef _SIGNPOSTALLOCATOR_HPP_
#define _SIGNPOSTALLOCATOR_HPP_
#include <malloc.h>
#include "Engine/Utility/Utility.hpp"

struct sign_post
{
	sign_post *next, *prev;
	size_t size;
	bool free;
};

class SignPostAllocator
{
public:
	void* buffer;
	sign_post *posts;

	void Init(size_t initial_size);
	void Deinit();
	void* Alloc(size_t size);
	void Free(void* ptr);	
};
#endif