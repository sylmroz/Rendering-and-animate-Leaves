#include "interpolations.h"
#include <iostream>

std::vector<float> Interpolations::GetX(){ return x; }
std::vector<float> Interpolations::GetY(){ return y; }
std::vector<float> Interpolations::GetCalculateY(){ return calculatey; }
void Interpolations::SetX(const std::vector<float>& x){ this->x = x; }
void Interpolations::SetY(const std::vector<float>& y){ this->y = y; }
float hermite_and_langrage_interpolation::CalcuateL(int j,float x)
{
	float temp{ 1.0f };
	for (unsigned int i = 0; i < this->x.size(); ++i)
	{
		if (i != j)
			temp *= (x - this->x[i]) / (this->x[j] - this->x[i]);
	}
	return temp;
}

float Langrage::Calculate(float X)
{
	float temp{ 0.0f };
	if (this->x.size() == this->y.size())
	{
		for (unsigned int j = 0; j < this->y.size(); ++j)
			temp += CalcuateL(j, X)*y[j];
	}
	return temp;
}

float Hermite::CalculateLprim(int j)
{
	float temp{ 0.0f };
	for (unsigned int i = 0; i < this->x.size(); ++i)
	{
		if (i!=j)
			temp += 1 / (this->x[j] - this->x[i]);
	}
	return temp;
}

float Hermite::CalculateH(int j,float X)
{
	return (1 - 2 * (X - x[j])*CalculateLprim(j))*CalcuateL(j, X)*CalcuateL(j, X);
}

float Hermite::CalculateHprim(int j, float X)
{
	return (X - x[j])*CalcuateL(j, X)*CalcuateL(j, X);
}

float Hermite::Calculate(float X)
{
	float temp1{ 0.0f }, temp2{ 0.0f };
	if ((y.size() == x.size()))
	{
		for (unsigned int i = 0; i < this->x.size(); ++i)
		{
			temp1 += CalculateH(i, X)*y[i];
			temp2 += CalculateHprim(i, X)*yprim[i];
		}
	}
	return temp1 + temp2;
}
void Hermite::SetYprim(const std::vector<float> Yprim)
{
	yprim = Yprim;
}

float DeCasteliau::Calculate(float X)
{
	std::vector<float> ptemp = y;
	for (int j = 1; j < y.size(); ++j)
		for (int i = 0; i < y.size() - j; ++i)
			ptemp[i] = (1 - X)*ptemp[i] + X*ptemp[i + 1];
	return ptemp[0];
}