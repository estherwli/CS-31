

bool isValidDate(int y, int m, int d) {
	const int daysInMonth[12] = { 31, 28, 31, 30, 31, 30, 31, 31, 30, 31, 30, 31 };
	if (m < 1 || m > 12 || d < 1) {
		return false;
	}
	if (m != 2)
		return d <= daysInMonth[m - 1]; //m - 1 because array elements begin at 0
	//at this point, m must be 2
	//deal with leap year / non-leap year

}