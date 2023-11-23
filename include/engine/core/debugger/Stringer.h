/**************************************************************************************************
 * @file   Stringer.h
 * @author Valentin Dumitru
 * @date   2023-11-22
 * @brief  Add description of this file if needed @TODO 
 *
 * Copyright (c) 2023 Valentin Dumitru. Licensed under the MIT License.
 * See LICENSE.txt in the project root for license information.
 **************************************************************************************************/
#pragma once

#include <string>
#include <sstream>
#include <type_traits>
#include <iterator>
#include <cstring>
#include <iomanip>
#include <list>
#include <deque>

namespace GLESC {
    template <typename T>
    struct isIterable {
        static const bool value = false;
    };
    template <typename T,typename Alloc>
    struct isIterable<std::vector<T,Alloc> > {
        static const bool value = true;
    };
    template <typename T,typename Alloc>
    struct isIterable<std::list<T,Alloc> > {
        static const bool value = true;
    };
    template <typename T,typename Alloc>
    struct isIterable<std::deque<T,Alloc> > {
        static const bool value = true;
    };
    template <typename T>
    struct isIterable<std::initializer_list<T>> {
        static const bool value = true;
    };
    template<typename T>
    constexpr bool isIterable_v = isIterable<T>::value;
    
    template<typename Type>
    std::string nonIterableToString(const Type &value) {
        std::ostringstream oss;
        
        if constexpr (std::is_enum_v<Type>) {
            // Handle enums by casting to their underlying type
            oss << static_cast<std::underlying_type_t<Type>>(value);
        } else if constexpr (std::is_same_v<Type, std::string> || std::is_same_v<Type, const char *>
                             || std::is_same_v<Type, char *>
                             || std::is_same_v<Type, const char *const>
                             || std::is_same_v<Type, char *const &>) {
            oss << value;
        } else if constexpr (std::is_same_v<Type, void *> || std::is_same_v<Type, const void *>) {
            // Format void* pointers as hexadecimal memory addresses
            oss << "void*: 0x" << std::hex << std::setw(sizeof(void *) * 2) << std::setfill('0')
                << reinterpret_cast<uintptr_t>(value);
        }else{
            // Attempt to use std::to_string for other types
            oss << std::to_string(value);
        }
        
        return oss.str();
    }
    
    template<typename Iterable>
    std::string iterableToString(const Iterable &iterable) {
        std::ostringstream oss;
        oss << "{";
        for (auto it = iterable.begin(); it != iterable.end(); ++it) {
            if (it != iterable.begin()) {
                oss << ", ";
            }
            
            oss << nonIterableToString(*it);
        }
        oss << "}";
        return oss.str();
    }
    
    template<typename Type>
    std::string toString(const Type &value) {
        if constexpr (isIterable_v<Type>) {
            return iterableToString(value);
        } else {
            return nonIterableToString(value);
        }
    }
    
}