/*
this will be the general header file that includes all libraries and using declarations.
#include "Header.hpp"
*/
#pragma once
#ifndef HEADER_HPP
#define HEADER_HPP

const unsigned windowWidth = 400;
const unsigned windowHeight = 800;
const unsigned frameLimit = 60;

#include <SFML/Graphics.hpp>
#include <SFML/Audio.hpp>
#include <iostream>

using namespace sf;
using std::cin;
using std::cout;
using std::optional;

#endif