//
//   NVIDIA Development Tools Team
//       C++ Programming Test
//
// ---------------------------------
// 
// This test should be self-explanatory.  All places where you are expected to
// write code are marked with TODO:  Each question is assigned a score.  Please
// see the SCORING comment below.  You are welcome to implement the questions
// in any order.
//
// This project should compile and run as-is, but all the tests will fail.
// Please implement all the TODOs as described below to get all the tests to
// succeed.
//
// You may use whatever other #includes you need.  You may use the C++ STL
// unless otherwise specified.  If you need help with STL (e.g. using fstream
// to read/write files), use the Josuttis book or read through the exercises
// and their tests, which have some file I/O already implemented.
//
// You're welcome to use stdio.h and C-style programming instead, but you'll
// have to convince us either way that your memory management is safe, even
// when ridiculous input values are passed to your functions.
//
// SCORING
// Total : 100 points
// 1. TestStringRotation                20 points
//   a. RotateString                       10 points
//   b. RotateStringOptimal                 5 points
//   c. Test vectors                        5 points
// 2. TestRgbConversions                20 points
//   a. CreateRGBA8888                      2 points
//   b. CreateRGB565                        3 points
//   c. ConvertRGBA8888ToRGB565             5 points
//   d. ConvertRGB565ToRGBA8888             5 points
//   e. Test vectors                        5 points
// 3. TestHierarchy                     45 points
//   a. Parser & data structure            15 points
//   b. Test vectors                       10 points
//   c. PrintHierarchyDepthFirst            5 points
//   d. PrintHierarchyDepthFirstSorted      5 points
//   e. PrintHierarchyBreadthFirst         10 points
// 4. TestClock                         15 points
//   a. AngleBetweenClockHands              3 points
//   b. GetMinuteHandFromHourHand           7 points
//   c. Test vectors                        5 points

#include <iostream>
#include <fstream>
#include <string>
#include <sstream>
#include <algorithm>
#include <cassert>
#include <vector>
#include <stdexcept>
#include <queue>

// Append data filenames to this string to read/write files in the data folder.
const std::string data_location("../Data/");

#define CHECK(cond, errstream, oss) \
    if (!(cond)) \
    { \
        (oss) << errstream << std::endl; \
        return; \
    }

// -----------------------------------------------------------------------------
// Problem:
// RotateString rotates S by R positions.  If R is positive rotate to the right.
// If R is negative rotate to the left.  "Rotating" means that characters
// shifted off one end roll back around to the other end.
//
// Explain how much time and memory your solution takes based on R and the
// length of S.  Note:  Please start out with a simple algorithm, and only come
// back and optimize it if you have time left after doing the other exercises.
//

void RotateString(std::string& S, int R)
{
    if (S.empty())
    {
        return; // avoid running the algo for nothing + we have a % size
    }

    R = R % static_cast<int>(S.size()); // make sure R is ion [-S.size()+1, S.size()-1]
    // in the following we reverse the notion of left and right for convinience (to much what I have on paper) and we ensure R is positive
    R = -R;
    if (R < 0)
    {
        R = static_cast<int>(S.size()) + R;
    }
    assert(static_cast<unsigned>(R) < S.size());

    // I remember encoutering the following algorithm in The art of computer programming (I may be wrong)
    std::reverse(std::begin(S), std::begin(S) + R);
    std::reverse(std::begin(S) + R, std::end(S));
    std::reverse(std::begin(S), std::end(S));
}

void RotateStringOptimal(std::string& S, int R)
{
    RotateString(S, R);
}

void TestStringRotation(std::ostream& error_output)
{
    const std::string failure_msg("String rotation failed!");

    std::string s1("sprint");
    RotateString(s1, 5);
    CHECK(s1 == "prints", failure_msg, error_output);

    std::string s2("StringRotated");
    RotateString(s2, 7);
    CHECK(s2 == "RotatedString", failure_msg, error_output);

    std::string s3("");
    RotateString(s3, 7);
    CHECK(s3 == "", failure_msg, error_output);

    std::string s4("sprint");
    RotateString(s4, 6);
    CHECK(s4 == "sprint", failure_msg, error_output);

    RotateString(s4, -6);
    CHECK(s4 == "sprint", failure_msg, error_output);

    RotateString(s4, 0);
    CHECK(s4 == "sprint", failure_msg, error_output);

    RotateString(s4, 6 * 51);
    CHECK(s4 == "sprint", failure_msg, error_output);

    RotateString(s4, -6 * 51);
    CHECK(s4 == "sprint", failure_msg, error_output);

    // TODO: Add more tests that demonstrate how you handle edge cases.
}


// -----------------------------------------------------------------------------
// Problem:
// In computer graphics color is often represented in the RGB color space using
// a packed 16-bit or 32-bit integer data type.
//
// This exercise converts between two of the common formats.
//
// RGBA8888 is a 32-bit pixel format which contains the Red, Green, and Blue
// color channel as well as an alpha which represents the pixels translucency.
//
//    [rrrrrrrr|gggggggg|bbbbbbbb|aaaaaaaa]  <-- Least significant bits
//
// RGB565 is a 16-bit pixel format which contains the Red, Green, and Blue
// color channel, but does not have an alpha channel.
//
//    [rrrrrggg|gggbbbbb] <-- Least significant bits
//

typedef unsigned char u8;
typedef unsigned int rgba8888;
typedef unsigned short rgb565;

// r, g, b, a have range 0-255
rgba8888 CreateRGBA8888( u8 r, u8 g, u8 b, u8 a )
{
    return (static_cast<rgba8888>(r) << 24u)
        | (static_cast<rgba8888>(g) << 16u)
        | (static_cast<rgba8888>(b) << 8u)
        | static_cast<rgba8888>(a);
}

// r, g, b have range 0-255
rgb565 CreateRGB565( u8 r, u8 g, u8 b )
{
    return ((static_cast<rgba8888>(r) >> 3u) << 11u)
        | ((static_cast<rgba8888>(g) >> 2u) << 5u)
        | (static_cast<rgba8888>(b) >> 3u);
}

// Discard alpha component
rgb565 ConvertRGBA8888ToRGB565( rgba8888 src )
{
    return CreateRGB565(static_cast<u8>(src >> 24u), static_cast<u8>((src >> 16u) & 0xffu), static_cast<u8>((src >> 8u) & 0xffu));
}

// Set alpha to FF (opaque)
rgba8888 ConvertRGB565ToRGBA8888( rgb565 src )
{
    // TODO: Implement this function
    // Add a comment detailing your algorithm decision
    // in terms of precision, round tripping, and performance.

    // we're exapanding so precision shouldn't be an issue
    // the compiler should inline and optimize : no need for pessimization unless we check that the compiler can't optimize or after profiling
    // it's clear that we can manually compute constants (src >> 11 << 3) would become (src >> 8) or replacing the mask 0x3fu and do a single shift

    return CreateRGBA8888(static_cast<u8>((src >> 11u) << 3u), static_cast<u8>(((src >> 5u) & 0x3fu) << 2u), static_cast<u8>((src & 0x1fu) << 3u), 0xffu);
}


// Extend the tests to identify and report any errors.
void TestRgbConversions(std::ostream& error_output)
{
    const std::string failure_msg("color conversion failed!");

    rgba8888 p32 = 0;
    rgb565 p16 = 0;

    p32 = CreateRGBA8888( 0xFF, 0x00, 0x00, 0x00 );
    CHECK(p32 == 0xFF000000, failure_msg, error_output);

    p32 = CreateRGBA8888( 0x00, 0xFF, 0x00, 0x00 );
    CHECK(p32 == 0x00FF0000, failure_msg, error_output);

    p32 = CreateRGBA8888( 0x00, 0x00, 0xFF, 0x00 );
    CHECK(p32 == 0x0000FF00, failure_msg, error_output);

    p32 = CreateRGBA8888( 0x00, 0x00, 0x00, 0xFF );
    CHECK(p32 == 0x0000FF, failure_msg, error_output);

    p16 = CreateRGB565( 0xFF, 0x00, 0x00 );
    CHECK(ConvertRGB565ToRGBA8888(p16) == 0xF80000FF, failure_msg, error_output);

    p16 = CreateRGB565( 0x00, 0xFF, 0x00 );
    CHECK(ConvertRGB565ToRGBA8888(p16) == 0x00FC00FF, failure_msg, error_output);

    p16 = CreateRGB565( 0xFF, 0x00, 0xFF );
    CHECK(ConvertRGB565ToRGBA8888(p16) == 0xF800F8FF, failure_msg, error_output);

    p16 = ConvertRGBA8888ToRGB565( 0xFFFFFFFF );
    CHECK(ConvertRGB565ToRGBA8888(p16) == 0xF8FCF8FF, failure_msg, error_output);

    p16 = ConvertRGBA8888ToRGB565( 0x00000000 );
    CHECK(ConvertRGB565ToRGBA8888(p16) == 0xFF, failure_msg, error_output);

    p16 = ConvertRGBA8888ToRGB565( 0xFF000000 );
    CHECK(ConvertRGB565ToRGBA8888(p16) == 0xF80000FF, failure_msg, error_output);

    p16 = ConvertRGBA8888ToRGB565( 0x00FF0000 );
    CHECK(ConvertRGB565ToRGBA8888(p16) == 0x00FC00FF, failure_msg, error_output);

    p16 = ConvertRGBA8888ToRGB565( 0x0000FF00 );
    CHECK(ConvertRGB565ToRGBA8888(p16) == 0x00F8FF, failure_msg, error_output);

    p16 = ConvertRGBA8888ToRGB565( 0x000000FF );
    CHECK(ConvertRGB565ToRGBA8888(p16) == 0x00FF, failure_msg, error_output);

    p16 = ConvertRGBA8888ToRGB565( 0x80808080 );
    CHECK(ConvertRGB565ToRGBA8888(p16) == 0x808080FF, failure_msg, error_output);

    p32 = ConvertRGB565ToRGBA8888( 0 );
    CHECK(p32 == 0xFF, failure_msg, error_output);

    p32 = ConvertRGB565ToRGBA8888( CreateRGB565( 0xFF, 0x00, 0x00 ) );
    CHECK(p32 == 0xF80000FF, failure_msg, error_output);

    p32 = ConvertRGB565ToRGBA8888( CreateRGB565( 0x00, 0xFF, 0x00 ) );
    CHECK(p32 == 0x00FC00FF, failure_msg, error_output);

    p32 = ConvertRGB565ToRGBA8888( CreateRGB565( 0x00, 0x00, 0xFF ) );
    CHECK(p32 == 0x0000F8FF, failure_msg, error_output);

    p32 = ConvertRGB565ToRGBA8888( 0xFFFF );
    CHECK(p32 == 0xF8FCF8FF, failure_msg, error_output);
}


// -----------------------------------------------------------------------------
// Problem:
// Create a simple data structure to represent a hierarchy.  Write a parser to
// read files in the following format and store them in your hierarchy structure.
// Then write functions that print the hierarhcy using multiple traversal
// algorithms.
// 
// Example input file format (note that leading periods specify depth):
//
// grandpa & grandma
// .mom
// ..me
// ...my son
// ...my daughter
// ..my brother
// ..my sister
// ...my nephew
// .aunt gertrude
// ..my annoying cousin
//
// Make sure that you detect nonsensical structures in the input file.  For
// example, the first line should not contain any leading periods, and a line
// with one leading period cannot be followed by a line with more than two
// leading periods.
//
// Because the printing functions are external to your class, you'll need to
// choose what type of interface to expose for those functions to be simple.
//
// The logic for the printing functions should NOT be contained within the class.

class Hierarchy
{

    // TODO: Implement this class
    struct node
    {
        using node_ptr = node*;
        using node_const_ptr = node const*;
        using children_ptr = std::vector<node_ptr>;

        std::string value = "";
        node_ptr parent;
        children_ptr children;

        node(std::string const& v = "", node_ptr p = nullptr) : value(v), parent(p)
        {}

        void add_child(node_ptr p)
        {
            children.push_back(p);
        }
    };

    std::vector<node> tree; // the root is the first element. we use vector for auto deallocation

    // due to time limit we'll give the traversal functions friend privilege
    friend void PrintHierarchyDepthFirst(const Hierarchy& h, std::ostream& output);
    friend void PrintHierarchyDepthFirstSorted(const Hierarchy& h, std::ostream& output);
    friend void PrintHierarchyBreadthFirst(const Hierarchy& h, std::ostream& output);

    // we'll implement recursive treaversal for simplicity

    void PrintHierarchyDepthFirst(node::node_const_ptr p, std::ostream& output) const
    {
        if (p == nullptr)
        {
            return;
        }

        for (auto const& c : p->children)
        {
            PrintHierarchyDepthFirst(c, output);
        }

        output << p->value << std::endl;
    }

    void PrintHierarchyDepthFirstSorted(node::node_const_ptr p, std::ostream& output) const
    {
        if (p == nullptr)
        {
            return;
        }

        auto children = p->children; // make a copy so that we don't alter the tree
        std::sort(std::begin(children), std::end(children), [](node::node_ptr a, node::node_ptr b)
        {
            assert(a != nullptr && b != nullptr); // we don't have children if they don't exist
            return a->value < b->value;

        });

        for (auto const& c : children)
        {
            PrintHierarchyDepthFirstSorted(c, output);
        }

        output << p->value << std::endl;
    }

    void PrintHierarchyBreadthFirst(std::queue<node::node_const_ptr>& q, std::ostream& output) const
    {
        while (!q.empty())
        {
            assert(q.front() != nullptr);

            output << q.front()->value << std::endl;

            for (auto& c : q.front()->children)
            {
                q.push(c);
            }

            q.pop();
        }
    }

public:
    // Return false if any I/O errors occur, otherwise return true.
    // The input file should have only one root node.
    bool LoadFromFile(const std::string& infile)
    {
        // NOTE: Feel free to replace the entire implementation of
        // this function.
        std::ifstream ifs(infile.c_str());
        if (!ifs)
        {
            return false;
        }

        std::string line;
        while (std::getline(ifs, line))
        {
            // TODO: Parse input line by line.  Handle bad input data elegantly,
            // or at least describe how in comments.
            if (tree.empty())
            {
                // this should be the first line and we'll set the root
                if (line.empty() || std::find(std::begin(line), std::end(line), '.') != std::end(line))
                {
                    // I consider excpetions an elegant error handling method although it's not consistant we the rest of the code that returns failure/success
                    throw std::runtime_error{ "error parsing the root node" };
                }
                tree.push_back(node{ line });
                continue;
            }
            // else

        }

        return true;
    }

};

// TODO: Implement the following Print* functions.
// - Print each node on a separate line, with two leading spaces for each depth
//   level.
// - The depth-first output should match the input order but the prefix should be
//   different.
// - The sorted depth-first output should sort the children of each node before
//   recursing into their children.
// - The breadth-first output should print all nodes at a given depth before
//   printing any deeper nodes.
// - See the files HierarchyTest_expected_*.txt in the
// Data directory for the expected results.
//
// Feel free to use helper functions, but don't change the signatures of these
// functions.

void PrintHierarchyDepthFirst(const Hierarchy& h, std::ostream& output)
{
    if (!h.tree.empty())
    {
        h.PrintHierarchyDepthFirst(&h.tree[0], output);
    }
}

void PrintHierarchyDepthFirstSorted(const Hierarchy& h, std::ostream& output)
{
    if (!h.tree.empty())
    {
        h.PrintHierarchyDepthFirstSorted(&h.tree[0], output);
    }
}

void PrintHierarchyBreadthFirst(const Hierarchy& h, std::ostream& output)
{
    std::queue<Hierarchy::node::node_const_ptr> q;
    if (!h.tree.empty())
    {
        q.push(&h.tree[0]);
        h.PrintHierarchyBreadthFirst(q, output);
    }
}

// TODO: Improve this test method.
// How could you verify your outputs are correct?
// How could you refactor this function to be less repetitive?
void TestHierarchy(std::ostream& error_output)
{
    const std::string failure_msg("Hierarchy tests failed!");

    bool success = false;

    Hierarchy h;
    std::string infile(data_location + "HierarchyTest.txt");
    success = h.LoadFromFile(infile);
    CHECK(success, failure_msg << "  I/O error.", error_output);

    std::string outfile;
    std::string testfile;
    // bool identical(false);

    outfile = data_location + "HierarchyTest_output_DFS.txt";
    {
        std::ofstream ofs(outfile.c_str());
        // If this fails, manually verify that outfile is not read-only on disk
        CHECK(ofs, failure_msg << "  I/O error.", error_output);

        PrintHierarchyDepthFirst(h, ofs);
    }

    outfile = data_location + "HierarchyTest_output_DFS_sorted.txt";
    {
        std::ofstream ofs(outfile.c_str());
        // If this fails, manually verify that outfile is not read-only on disk
        CHECK(ofs, failure_msg << "  I/O error.", error_output);

        PrintHierarchyDepthFirstSorted(h, ofs);
    }

    outfile = data_location + "HierarchyTest_output_BFS.txt";
    {
        std::ofstream ofs(outfile.c_str());
        // If this fails, manually verify that outfile is not read-only on disk
        CHECK(ofs, failure_msg << "  I/O error.", error_output);

        PrintHierarchyBreadthFirst(h, ofs);
    }
}

// -----------------------------------------------------------------------------
// Problem:
// Given a time of day (an integer for the hour, an integer for the minute),
// compute the angle between the clock hands in degrees.  The answer should
// always be between 0 and 180, inclusively.

float AngleBetweenClockHands(int hour, int minute)
{
    // convert hour to degree
    float h = 360.f * static_cast<float>(hour) / 12.f;
    // convert min to radians
    float m = 360.f * static_cast<float>(minute) / 60.f;
    return 0.f;
}

// Given a pair of 2D points (C, the center of a clock, and H, the tip of the
// hour hand), you can figure out exactly what time it is.  We are assuming that
// at 12:00, the hour hand is pointing along the positive Y axis, and at 3:00,
// the hour hand is pointing along the positive X axis.  Compute the location of
// a third point M, the tip of the minute hand.  The minute hand is 20% longer
// than the hour hand.
struct float2
{
    float x;
    float y;
};
float2 GetMinuteHandFromHourHand(float2 C, float2 H)
{
    float2 M;

    // TODO: Implement this function
    M.x = 0.f;
    M.y = 0.f;

    return M;
}

void TestClock(std::ostream& error_output)
{
    // TODO: Add tests for AngleBetweenClockHands and GetMinuteHandFromHourHand.
    error_output << "Clock tests not yet implemented!" << std::endl;
}

// -----------------------------------------------------------------------------

int main()
{
    std::ostringstream oss;

    TestStringRotation(oss);
    TestRgbConversions(oss);
    TestHierarchy(oss);
    TestClock(oss);

    // Print output to console
    std::cout << oss.str();
    
    // Pause...
    std::cout << std::endl
        << std::endl
        << "Press enter to quit..." << std::endl;
    char c;
    std::cin >> std::noskipws >> c;

    return 0;
}
