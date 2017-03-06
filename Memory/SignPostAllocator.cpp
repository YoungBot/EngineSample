//==========================================================
//SignPostAllocator.cpp
//==========================================================
#include "SignPostAllocator.hpp"

void SignPostAllocator::Init(size_t initial_size)
{
	buffer = malloc(initial_size);
	posts = (sign_post*)buffer;
	posts->size = initial_size - sizeof(sign_post);
	posts->next = nullptr;
	posts->prev = nullptr;
	posts->free = true;
	posts->free = true;
}

void SignPostAllocator::Deinit()
{
	FATAL_ASSERTION((posts->next == nullptr) && (posts->prev == nullptr) && (posts->free), "Deinit failed");
	free(buffer);
}

void* SignPostAllocator::Alloc(size_t size)
{
	size_t alloc_size = size + sizeof(sign_post);
	sign_post *iter = posts;

	while (iter != nullptr)
	{
		if (iter->free && iter->size >= alloc_size)
			break;

		iter = iter->next;
	}	
	FATAL_ASSERTION(iter != nullptr, "Alloc Failed.");
	

	iter->free = false;

	char* iter_buffer = (char*)iter + sizeof(sign_post);
	sign_post* next_signpost = (sign_post*)(iter_buffer + size);
	next_signpost->free = true;
	next_signpost->prev = iter;
	next_signpost->next = iter->next;
	next_signpost->size = iter->size - alloc_size;

	iter->size = size;
	iter->next = next_signpost;

	return iter_buffer;
}

void SignPostAllocator::Free(void* ptr)
{
	char *iter_buffer = (char*)ptr;
	sign_post *post = (sign_post*)(iter_buffer - sizeof(sign_post));

	FATAL_ASSERTION(post->free == false, "Free Failed");

	// check previous or next, see if they're free, or both are free
	if ((post->prev != nullptr) && (post->prev->free)
		&& (post->next != nullptr) && (post->next->free))
	{
		size_t size = post->prev->size + post->size + post->next->size + 2 * sizeof(sign_post);// 2 this post and next post, previous is staying
		sign_post* prev = post->prev;
		prev->size = size;
		if (post->next->next!=nullptr)
		{
			post->next->next->prev = prev;
		}	
		prev->next = post->next->next;
		
	}
	else if ((post->prev != nullptr) && (post->prev->free))
	{
		size_t size = post->prev->size + post->size + sizeof(sign_post);
		sign_post *prev = post->prev;
		prev->size = size;
		if (post->next!=nullptr)
		{
			post->next->prev = prev;
		}		
		prev->next = post->next;		
	}
	else if ((post->next != nullptr) && (post->next->free))
	{
		post->size = post->next->size + post->size + sizeof(sign_post);
		if (post->next->next!=nullptr)
		{
			post->next->next->prev = post;
		}		
		post->next = post->next->next;
		post->free = true;
	}
	else
		post->free = true;
}