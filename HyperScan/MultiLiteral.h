/*
 * @file MultiLiteral.cpp
 * @brief MultiLiteral class is used to define sets of literals and to crate the associated database for scanning.
 * @author Ludvik Jerabek
 * @version 1.0 04/08/2021
 *
 * MIT License
 *
 * Copyright (c) 2021 Ludvik Jerabek
 *
 * Permission is hereby granted, free of charge, to any person obtaining a copy of this software and associated
 * documentation files (the "Software"), to deal in the Software without restriction, including without limitation
 * the rights to use, copy, modify, merge, publish, distribute, sublicense, and/or sell copies of the Software, and to
 * permit persons to whom the Software is furnished to do so, subject to the following conditions:
 *
 * The above copyright notice and this permission notice shall be included in all copies or substantial portions of the Software.
 *
 * THE SOFTWARE IS PROVIDED "AS IS", WITHOUT WARRANTY OF ANY KIND, EXPRESS OR IMPLIED, INCLUDING BUT NOT LIMITED TO THE
 * WARRANTIES OF MERCHANTABILITY, FITNESS FOR A PARTICULAR PURPOSE AND NONINFRINGEMENT. IN NO EVENT SHALL THE AUTHORS OR
 * COPYRIGHT HOLDERS BE LIABLE FOR ANY CLAIM, DAMAGES OR OTHER LIABILITY, WHETHER IN AN ACTION OF CONTRACT, TORT OR
 * OTHERWISE, ARISING FROM, OUT OF OR IN CONNECTION WITH THE SOFTWARE OR THE USE OR OTHER DEALINGS IN THE SOFTWARE.
 */

#ifndef _HYPERSCAN_MULTI_LITERAL_H
#define _HYPERSCAN_MULTI_LITERAL_H

#include <vector>
#include <memory>

namespace HyperScan {
    class BlockDatabase;
    class VectoredDatabase;
    class StreamDatabase;
    class PlatformInfo;
    class MultiLiteral {
        friend class Database;
    public:
        MultiLiteral() = default;
        ~MultiLiteral() = default;
    public:
        void AddLiteral(const std::vector<char> &literal, unsigned flags, unsigned identifier);
        void Clear();
        [[nodiscard]] BlockDatabase GetBlockDatabase();
        [[nodiscard]] VectoredDatabase GetVectoredDatabase();
        [[nodiscard]] StreamDatabase GetStreamDatabase();
        [[nodiscard]] BlockDatabase GetBlockDatabase(const PlatformInfo& pi);
        [[nodiscard]] VectoredDatabase GetVectoredDatabase(const PlatformInfo& pi);
        [[nodiscard]] StreamDatabase GetStreamDatabase(const PlatformInfo& pi);
    private:
        std::vector<std::vector<char>> _literals;
        std::vector<unsigned int> _flags;
        std::vector<unsigned int> _ids;
    };
}

#endif //_HYPERSCAN_MULTI_LITERAL_H
