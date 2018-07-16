/*
 * Copyright (c) 2015 Carnegie Mellon University and The Trustees of Indiana
 * University.
 * All Rights Reserved.
 *
 * THIS SOFTWARE IS PROVIDED "AS IS," WITH NO WARRANTIES WHATSOEVER. CARNEGIE
 * MELLON UNIVERSITY AND THE TRUSTEES OF INDIANA UNIVERSITY EXPRESSLY DISCLAIM
 * TO THE FULLEST EXTENT PERMITTED BY LAW ALL EXPRESS, IMPLIED, AND STATUTORY
 * WARRANTIES, INCLUDING, WITHOUT LIMITATION, THE WARRANTIES OF MERCHANTABILITY,
 * FITNESS FOR A PARTICULAR PURPOSE, AND NON-INFRINGEMENT OF PROPRIETARY RIGHTS.
 *
 * This Program is distributed under a BSD license.  Please see LICENSE file or
 * permission@sei.cmu.edu for more information.  DM-0002659
 */
/**
 * @brief Some basic typedefs.
 */

#ifndef GB_TYPES_HPP
#define GB_TYPES_HPP

#include <cstdint>
#include <exception>
#include <vector>
#include <iostream>

namespace GraphBLAS
{
    typedef uint64_t IndexType;
    typedef std::vector<IndexType> IndexArrayType;

	 struct NoAccumulate
    {
        // It doesn't really matter what the type is, it never gets executed.
        typedef bool result_type;
        inline bool operator()(bool lhs, bool rhs) { return true; }
    };

    // This is the "Matrix" class for this example
    struct matrix_tag {};

} // namespace GraphBLAS

#endif // GB_TYPES_HPP
