
#include "Fraction.h"
#include <iostream>
#include <cmath>

Fraction::Fraction(const int numerator, const int denominator)
//Первая очередь инициализации
	: m_numerator(numerator)
	/*, m_denominator(denominator) */ //Не инициализируем здесь, нужны доп. проверки.
		//Вторая очередь инициализации для тех полей, коотрых не было в первой очереди (см. .h)
{
	//Третья очередь инициализации. Сейчас m_numerator == numerator, m_denominator == 1


	if (denominator == 0) {
		std::cerr << "Fraction::Fraction: error: denominator is 0, result will be numerator/1.\n";
		//Ничего не меняем, m_denominator и так == 1
	}
	else {
		m_denominator = denominator;
	}

	if (m_denominator < 0) {
		m_numerator *= -1;
		m_denominator *= -1;
	}
}

int Fraction::getNumerator() const
{
	return m_numerator;
}

int Fraction::getDenominator() const
{
	return m_denominator;
}

void Fraction::setNumerator(const int value)
{
	m_numerator = value;
}

void Fraction::setDenominator(const int value)
{
	if (value == 0) {
		//Если знаменатель неправильный, ничего не делаем. Хотя можно было бы положить 1, как в конструкторе.
		std::cerr << "Fraction::setDenominator: error: value is 0, won't assign.\n";
		return;
	}

	m_denominator = value;
}

void Fraction::print() const
{
	std::cout << m_numerator << '/' << m_denominator << '\n';
}

Fraction Fraction::div(const Fraction& other) const
{
	//Особый случай:
	if (other.m_numerator == 0) {
		std::cerr << "Fraction::div: error: other.m_numerator is 0, result will be 0/1.\n";
		return Fraction(0, 1);
	}

	Fraction result;
	result.m_numerator = m_numerator * other.m_denominator;
	result.m_denominator = m_denominator * other.m_numerator;
	return result;
}



Fraction Fraction::sum(const Fraction& other) const
{
	Fraction result;
	result.m_numerator = m_numerator * other.m_denominator + other.m_numerator * m_denominator;
	result.m_denominator = m_denominator * other.m_denominator;
	return result;
}

Fraction Fraction::sub(const Fraction& other) const
{
	Fraction result;
	result.m_numerator = m_numerator * other.m_denominator + other.m_numerator * m_denominator;
	result.m_denominator = m_denominator * other.m_denominator;
	return result;
}

Fraction Fraction::mul(const Fraction& other) const
{
	Fraction result;
	result.m_numerator = m_numerator * other.m_numerator;
	result.m_denominator = m_denominator * other.m_denominator;
	return result;
}

void Fraction::reduce()
{
	int k = 1;
	for (int i = 2; (i < m_numerator) || (i < m_denominator); ++i)
		if ((m_numerator % i == 0) && (m_denominator % i == 0))
			k = i;
	if (k != 1)
	{
		m_numerator /= k;
		m_denominator /= k;
	}
	std::cout << m_numerator << '/' << m_denominator << '\n';
}

void Fraction::incorrect()
{
	int a = m_numerator / m_denominator;
	m_numerator = m_numerator % m_denominator;
	if (m_numerator != 0)
		std::cout << a << ' ' << m_numerator << '/' << m_denominator << '\n';
	else
		std::cout << a << '\n';
}


void Fraction::rounds(int a)
{
	double result;
	double nominator = m_numerator;
	double denominator = m_denominator;
	result = nominator / denominator;
	std::cout << round(result * pow(10, a)) / pow(10, a) << '\n';
}

bool Fraction::operator==(const Fraction& other) const
{
	return(m_numerator == other.m_numerator &&
		m_denominator == other.m_denominator);
}

bool Fraction::operator!=(const Fraction& other) const
{
	return !operator==(other);
}

bool Fraction::operator>(const Fraction& other) const
{
	return((m_numerator * other.m_denominator) > (other.m_numerator * m_denominator));
}

bool Fraction::operator<(const Fraction& other) const
{
	return(m_numerator * other.m_denominator < other.m_numerator * m_denominator);
}