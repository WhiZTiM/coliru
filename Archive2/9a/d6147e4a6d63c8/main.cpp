char staticData[4][3] = {{1,2,3},{3,3,2},{8,3,4},{2,2,1}};

int main() {
    char** xyz = new char*[2];
    xyz[0] = staticData[0]; // DOES NOT COMPILE
    xyz[1] = staticData[2]; // DOES NOT COMPILE
}