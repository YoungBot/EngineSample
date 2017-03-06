#include <Windows.h>

#include "TextHelper.hpp"

bool IsWhitespace(char c)
{
	switch (c) {
	case '\n':
	case '\r':
	case ' ':
	case '\t':
		return true;

	default:
		return false;
	};
}

char* Trim(char *s)
{
	while (IsWhitespace(*s)) {
		++s;
	}

	char *end = s;
	while (*end != NULL) {
		++end;
	}

	if (end > s) {
		--end;
		while ((end > s) && IsWhitespace(*end)) {
			--end;
		}

		++end;
		*end = NULL;
	}

	return s;
}