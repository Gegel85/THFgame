/*
** EPITECH PROJECT, 2020
** glmTest
** File description:
** helper.hpp
*/

#ifndef GLMTEST_PRETTY_PRINT_HPP
#define GLMTEST_PRETTY_PRINT_HPP

#include <iomanip>
#include <glm/glm.hpp>
#include <glm/gtx/string_cast.hpp>

typedef glm::vec3 point3;
typedef glm::vec3 color;

//Enable using * with all number type
template<glm::length_t L, typename T, glm::qualifier Q = glm::defaultp, typename T2>
glm::vec<L, T, Q> operator*(const glm::vec<L, T, Q> &vec, T2 val)
{
	return vec * static_cast<T>(val);
}

template<glm::length_t L, typename T, glm::qualifier Q = glm::defaultp>
std::ostream &operator<<(std::ostream &stream, const glm::vec<L, T, Q> &vec)
{
	size_t biggest = 0;
	std::stringstream s;

	for (unsigned i = 0; i < L; i++) {
		s << vec[i];
		biggest = std::max(biggest, s.str().size());
		s.str("");
	}

	for (unsigned i = 0; i < L; i++)
		stream << "|" << std::setfill(' ') << std::setw(biggest) << vec[i] << "|" << std::endl;

	return stream;
}

template<glm::length_t C, glm::length_t R, typename T, glm::qualifier Q = glm::defaultp>
std::ostream &operator<<(std::ostream &stream, const glm::mat<C, R, T, Q> &mat)
{
	std::array<size_t, R> biggest;
	std::stringstream s;

	biggest.fill(0);
	for (unsigned i = 0; i < C; i++) {
		for (unsigned j = 0; j < R; j++) {
			s << mat[j][i];
			biggest[j] = std::max(biggest[j], s.str().size());
			s.str("");
		}
	}

	for (unsigned i = 0; i < C; i++) {
		stream << "|";
		for (unsigned j = 0; j < R; j++) {
			if (j)
				stream << ", ";
			stream << std::setfill(' ') << std::setw(biggest[j]) << mat[j][i];
		}
		stream << "|" << std::endl;
	}
	return stream;
}

glm::vec3 computeNormal(glm::vec3 p1, glm::vec3 p2, glm::vec3 p3);

#endif //GLMTEST_PRETTY_PRINT_HPP
