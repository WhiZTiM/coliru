class Test {
    class Inner {
		private:
			int i;
		public:
			Inner(int i) {
				this->i = i;
			}
	};

	class AnotherInner {
		private:
			Inner inner;
		public:
			AnotherInner(const Inner& inner) {
				this->inner = inner;
			}
	};
};

int main()
{
    
}