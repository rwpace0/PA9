/*
this will be the general header file that includes all libraries and using declarations.
#include "Header.hpp"
*/
#pragma once
#ifndef HEADER_HPP
#define HEADER_HPP

const unsigned windowWidth = 800;
const unsigned windowHeight = 600;
const unsigned frameLimit = 60;

#include <SFML/Graphics.hpp>
#include <SFML/Audio.hpp>
#include <SFML/Window.hpp>
#include <iostream>
#include <sstream>

using namespace sf;
using std::cin;
using std::cout;
using std::optional;
using std::runtime_error;


#endif