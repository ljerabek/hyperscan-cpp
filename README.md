# HyperScan C++

C++ Wrapper for Intel Hyperscan

# About Hyperscan

Hyperscan is a high-performance multiple regex matching library. It follows the regular expression syntax of the
commonly-used libpcre library, but is a standalone library with its own C API.

Hyperscan uses hybrid automata techniques to allow simultaneous matching of large numbers (up to tens of thousands) of
regular expressions and for the matching of regular expressions across streams of data.

Hyperscan is typically used in a DPI library stack.

The official homepage for Hyperscan is at [www.hyperscan.io](https://www.hyperscan.io).

# General Usage

The example provided below shows a single pattern match using a block database. Other examples can be found in
the `Examples` folder in the project repository.

```c++
#include <iostream>
#include <fstream>
#include "HyperScan.h"

using namespace std;

// Create a custom IMatcher object to deal with context and matching.
class MyMatcher : public HyperScan::IMatcher {
public:
    MyMatcher() : matches(0) {}
    ~MyMatcher()= default;
    // OnMatch is called when a match occurs
    int OnMatch(unsigned int id, unsigned long long from, unsigned long long to, unsigned int flags) override {
        // Printing output will slow down matching but it's for demonstration purposes.
        std::cout << "   ID: " << id << std::endl;
        std::cout << " From: " << from << std::endl;
        std::cout << "   To: " << to << std::endl;
        std::cout << "Flags: " << flags << std::endl;
        // Count matches
        matches++;
        return 0;
    }
    // Show number or matches for the data set
    void Dump(){
        std::cout << "Matches found: " << matches << std::endl;
    }
private:
    int matches;
};

int main() {
    // Global HyperScan functions

    // Hyperscan requires the Supplemental Streaming SIMD Extensions 3 instruction set. This function can be called
    // on any x86 platform to determine if the system provides the required instruction set.
    std::cout << "HyperScan Valid: " << HyperScan::ValidPlatform() << std::endl;

    // Get the version information. A string containing the version number of this release build and the date of the build.
    std::cout << "HyperScan Version: " << HyperScan::GetVersion() << std::endl;

    // Create a pattern object
    HyperScan::Pattern pattern("^192\\.152\\.201\\.85$", HyperScan::Pattern::CASELESS |HyperScan::Pattern::MULTILINE );

    // Create a block database from the current pattern object
    HyperScan::BlockDatabase pattern_db = pattern.GetBlockDatabase();

    // Additional data you can query from the DB no required but just for visibility
    std::cout << "DB Size: " << pattern_db.GetSize() << std::endl;
    std::cout << "DB Info: " << pattern_db.GetInfo() << std::endl;

    // Create a Scratch object from the DB
    HyperScan::Scratch scratch = pattern_db.GetScratch();

    // Create your custom matcher object
    MyMatcher matcher;

    // Read a block of data
    std::ifstream file("ips.txt", std::ios::binary | std::ios::ate);
    if( !file.is_open() ) {
        std::cout << "Failed to open ips.txt" << std::endl;
        return 1;
    }
    std::streamsize size = file.tellg();
    file.seekg(0, std::ios::beg);
    std::vector<char> block(size);
    file.read(block.data(), size);

    // Scan the block of data
    HyperScan::Scanner::Scan(pattern_db,scratch,matcher,block);

    matcher.Dump();

    return 0;
}
```

# License

Hyperscan C++ is licensed under the MIT License. See the LICENSE file in the project repository.

# Versioning

The `master` branch on Github will always contain the most recent release of Hyperscan C++. Each version released
to `master` goes through QA and testing before it is released; if you're a user, rather than a developer, this is the
version you should be using.
