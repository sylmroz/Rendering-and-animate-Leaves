#ifndef INETERPOLATIONS_H
#define INETERPOLATIONS_H
#include <vector>
#include "glm\glm.hpp"

class Interpolations
{
public:
	virtual float Calculate(float X) = 0;
	virtual void SetX(const std::vector<float>& x);
	virtual void SetY(const std::vector<float>& y);
	virtual std::vector<float> GetX();
	virtual std::vector<float> GetY();
	virtual std::vector<float> GetCalculateY();
protected:
	std::vector<float> x;
	std::vector<float> y;
	std::vector<float> calculatey;
private:
};

class hermite_and_langrage_interpolation :public Interpolations
{
public:
protected:
	float CalcuateL(int j, float x);
private:
};

class Hermite :public hermite_and_langrage_interpolation
{
public:
	float Calculate(float X) override;
	void SetYprim(const std::vector<float> Yprim);
protected:
	float CalculateH(int j, float X);
	float CalculateHprim(int j, float X);
	float CalculateLprim(int j);
private:
	std::vector<float> yprim;
};

class Langrage :public hermite_and_langrage_interpolation
{
public:
	float Calculate(float X) override;
protected:
private:
};

class DeCasteliau :public Interpolations
{
public:
	float Calculate(float X) override;
protected:
private:
};
#endif