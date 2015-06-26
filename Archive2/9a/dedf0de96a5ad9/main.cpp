#include<string>
#include<memory>
#include<vector>
#include<iostream>
using namespace std;

class TextNode
{
    public:
    string _text;
    TextNode(const string text) : _text(text)
    TextNode(const char* text) : _text(text)
};

class PlainTextNode: TextNode;
{
    public:
    using TextNode::TextNode;
};
class BoldTextNode: TextNode;
{
    public:
    using TextNode::TextNode;
};
class ItalicTextNode: TextNode;
{
    public:
    using TextNode::TextNode;
};

class Reader
{
    public:
    void Read()
    {
        /*
        PlainTextNode pt("AAA");
        BoldTextNode bt("BBB");
        ItalicTextNode it("CCC");
        
        vector<TextNode*> v{&pt, &bt,&it);
        v.emplace_back(&pt);
        v.emplace_back(&bt);
        v.emplace_back(&it);
        */
        
        
    }
}

int main()
{
    Reader r;
    r.Read();