enum {
    m00 = 42,
};

int main() {
	throw &m00;
}