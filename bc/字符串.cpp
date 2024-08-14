void manacher(const string& s, tp palindrome[]) {
	string ss = "";
	ss += "$#";
	for (int i = 0; i < s.length(); i++) {
		ss += s[i];
		ss += '#';
	}
	ss += '@';
	tp start = 1, maxto = 1;
	tp tmp = 0;
	for (int i = 1; i < ss.length() - 1; i++) {
		tmp = 0;
		if (i <= maxto) {
			tmp = min(maxto - i + 1, palindrome[2 * start - i]);
		}
		while (ss[i + tmp] == ss[i - tmp]) {
			++tmp;
		}
		palindrome[i] = tmp;
		if (i + palindrome[i] - 1 > maxto) {
			maxto = i + palindrome[i] - 1;
			start = i;
		}
	}
}
