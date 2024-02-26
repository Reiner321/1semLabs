#pragma once

class Fraction
{
public:
	Fraction() = default; //Сработает вторая очередь инициализации, получим дробь 0/1
	Fraction(const int numerator, const int denominator);
	~Fraction() = default;

	int getNumerator() const;
	int getDenominator() const;

	void setNumerator(const int value);
	void setDenominator(const int value);

	void print() const;

	Fraction sum(const Fraction& other) const;
	Fraction sub(const Fraction& other) const;
	Fraction mul(const Fraction& other) const;
	Fraction div(const Fraction& other) const;

	void reduce();

	void incorrect();

	void rounds(int a);

	bool operator==(const  Fraction& other) const;
	bool operator!=(const Fraction& other) const;
	bool operator>(const Fraction& other) const;
	bool operator<(const Fraction& other) const;

private:
	int m_numerator = 0;
	int m_denominator = 1;
};