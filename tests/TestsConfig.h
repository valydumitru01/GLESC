/**************************************************************************************************
 * @file   TestsConfig.h
 * @author Valentin Dumitru
 * @date   10/02/2024
 * @brief  Add description of this file if needed @TODO
 *
 * Copyright (c) 2024 Valentin Dumitru. Licensed under the MIT License.
 * See LICENSE.txt in the project root for license information.
 **************************************************************************************************/
#pragma once

/**
 * @brief This flag enables testing for vectors and matrices
 * @details This flag exists because compiling and running the tests for vectors and matrices takes a lot of time, so
 * we define it to false by default to save time.
 */



#define MATH_ALGEBRA_UNIT_TESTING true
#define MATH_GEOMETRY_UNIT_TESTING true
#define MATH_RANDOM_GENERATION_UNIT_TESTING true
#define WINDOW_TESTING true

#define ECS_BACKEND_UNIT_TESTING true
#define ECS_FRONTEND_UNIT_TESTING true

#define RENDERING_INTEGRATION_TESTING true