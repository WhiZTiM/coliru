class SystemObject {
public:
    SystemObject() { }
    ~SystemObject() { }

    string getZone() { return currentZone; }
    void setZone(string zone) { currentZone = zone; }

    void setBuffer(TextBuffer* buffer) { currentBuffer = buffer; }

    void printToBuffer(string s) { currentBuffer->printToBuffer(s); }
private:
    const string gameTitle = "ASCII Text RPG";
    const int screenWidth = 100;
    string currentZone = "NULL";
    TextBuffer* currentBuffer = NULL;
};
