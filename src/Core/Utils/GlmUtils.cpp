//
// Created by Gegel85 on 18/11/2020
//

#include "GlmUtils.hpp"

glm::vec3 computeNormal(glm::vec3 p1, glm::vec3 p2, glm::vec3 p3)
{
	return glm::normalize(glm::cross(glm::normalize(p1 - p2), glm::normalize(p3 - p2)));
}