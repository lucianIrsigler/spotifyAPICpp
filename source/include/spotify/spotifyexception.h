#pragma once
#include <exception>
#include <iostream>

/*
	Spotify exception
*/
class spotifyException : public std::exception
{
	std::string _msg;
public:
	spotifyException(const std::string& message): _msg(message){}

	virtual const char* what() const noexcept override
	{
		return _msg.c_str();
	}
};