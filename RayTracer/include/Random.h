#pragma once
//\====================================================================
//\ Class that implements a random number generator (linear congruential generator)
//\ that uses the following rule:
//\					seed = (a*seed + c) & m;
//\					randomInt = seed & L;
//\====================================================================
namespace Random
{
	// Set current seed
	int			GetSeed();
	// Set current seed
	void		SetSeed(const int& iSeed);
	// Get maximum allowed int
	int			RandMax();
	// Random int generator
	int			RandInt();
	int			RandRange(const int& iMin, const int& iMax);
	// Random float generator from 0.0f -> 1.0f
	float		RandFloat();
	// Random float generator from interval [x0, x1]
	float		RandRange(const float& fX0, const float& fX1);
};