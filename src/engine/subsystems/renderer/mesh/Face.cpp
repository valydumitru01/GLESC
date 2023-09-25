/*******************************************************************************
 *
 * Copyright (c) 2023 Valentin Dumitru.
 * Licensed under the MIT License.
 * See LICENSE.txt in the project root for license information.
 ******************************************************************************/
#include "engine/subsystems/renderer/mesh/Face.h"
#include "engine/core/math/Math.h"
using namespace GLESC;

bool Face::operator==(const Face &other) const {
    return normal == other.normal;
}