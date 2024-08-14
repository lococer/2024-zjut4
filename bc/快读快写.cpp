namespace Fread {
	const int SIZE = 1 << 21; char buf[SIZE], * S, * T;
	inline char getchar() { if (S == T) { T = (S = buf) + fread(buf, 1, SIZE, stdin); if (S == T)return '\n'; }return *S++; }
}
namespace Fwrite {
	const int SIZE = 1 << 21;
	char buf[SIZE], * S = buf, * T = buf + SIZE;
	inline void flush() { fwrite(buf, 1, S - buf, stdout); S = buf; }
	inline void putchar(char c) { *S++ = c; if (S == T)flush(); }
	struct POPOSSIBLE { ~POPOSSIBLE() { flush(); } }ztr;
}
#define getchar Fread :: getchar
#define putchar Fwrite :: putchar
namespace Fastio {
	struct Reader {
		template<typename T>
		Reader& operator >> (T& x) {
			char c = getchar(); T f = 1;
			while (c < '0' || c>'9') { if (c == '-')f = -1; c = getchar(); }x = 0;
			while (c >= '0' && c <= '9') { x = x * 10 + (c - '0'); c = getchar(); }x *= f;
			return *this;
		}
		Reader() {}
	}cin;
	struct Writer {
		template<typename T>
		Writer& operator << (T x) {
			if (x == 0) { putchar('0'); return *this; }
			if (x < 0) { putchar('-'); x = -x; }
			static int sta[45]; int top = 0;
			while (x) { sta[++top] = x % 10; x /= 10; }
			while (top) { putchar(sta[top] + '0'); --top; }
			return *this;
		}
		Writer& operator << (char c) { putchar(c); return *this; }
		Writer() {}
	}cout;
}
#define endl '\n' 
#define cin Fastio::cin
#define cout Fastio::cout
