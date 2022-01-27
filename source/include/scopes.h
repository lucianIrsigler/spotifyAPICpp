#pragma once

#include <vector>
#include <string>

/*
	A vector containing all valid spotify scopes
	@returns vector containing scopes
*/
std::vector<std::string> spotifyScopes();

/*
	Checks if a scope is valid
	@scope->scope to check
	@returns whether scope is valid
*/
bool isValidScopes(std::string scope);

/*
	Checks if several scopes is valid(space seperated)
	@scope->scopes to check(Example: "scope1 scope2 scope3"
	@returns whether scope string is valid
*/
bool isValidScopes(std::string userScopes);