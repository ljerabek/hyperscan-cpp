/*
 * @file Scanner.h
 * @brief Scanner class currently provides static functions but may become an object in the future. Provides the hs_scan and hs_scan_vector functionality.
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

#ifndef _HYPERSCAN_SCANNER_H
#define _HYPERSCAN_SCANNER_H

#include <hs/hs.h>
#include <string>
#include <vector>
#include "IScanner.h"

namespace HyperScan {
    class BlockDatabase;
    class VectoredDatabase;
    class Scratch;
    class Scanner : public IScanner {
    public:
        static hs_error_t Scan(BlockDatabase &db, Scratch &scratch, IMatcher &match, const std::vector<char>& data);
        static hs_error_t Scan(BlockDatabase &db, Scratch &scratch, IMatcher &match, const std::string& data);
        static hs_error_t Scan(BlockDatabase &db, Scratch &scratch, IMatcher &match, const char* buffer , unsigned int length);
        static hs_error_t Scan(VectoredDatabase &db, Scratch &scratch, IMatcher &match, const std::vector<std::vector<char>>& blocks);
        static hs_error_t Scan(VectoredDatabase &db, Scratch &scratch, IMatcher &match, const std::vector<std::string>& blocks);
    };
}
#endif //_HYPERSCAN_SCANNER_H
