#ifndef SHA1GENERATOR_H
#define SHA1GENERATOR_H
#pragma once

#include <iostream>
#include <fstream>
#include <vector>
#include <filesystem>
#include "openssl/sha.h"

std::string SHA1Generator(std::vector<char> contentBytes);

#endif // SHA1GENERATOR_H