
/*******************************************************************************
 *
 * Copyright (c) 2023 Valentin Dumitru.
 * Licensed under the MIT License.
 * See LICENSE.txt in the project root for license information.
 ******************************************************************************/
#include "engine/core/math/Vector.h"

namespace GLESC {
    struct Face {
        bool operator==(const Face &other) const;
        /**
         * @brief The normal (perpendicular vector that comes out of the face) of the face
         */
        Vector3F normal;
    };
    
}