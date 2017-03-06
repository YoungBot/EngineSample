//==========================================================
//Time.hpp
//==========================================================
#pragma once

#ifndef _TIME_HPP_
#define _TIME_HPP_
#include <stdint.h>


	void InitializeTimer();
	double GetCurrentSeconds();
	uint64_t __fastcall TimeGetOpCount();
	uint64_t __fastcall TimeOpCountTo_us(uint64_t op_count);
	uint64_t __fastcall TimeOpCountTo_ms(uint64_t op_count);
#endif	