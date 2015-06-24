//Conversion between types (Such as ints to strings)

#ifndef _CONVERSIONS_C
#define _CONVERSIONS_C

//Converts a single-digit integer into a string character
char inttochar(int in) {
	char out;
	out = '0' + in;
	return out;
}

//Converts a single digit character to an integer
int chartoint(char in) {
	int out;
	out = in - '0';
	return out;
}

//Converts a large integer into a string
void inttostr(int in, char *out) {
	int one, ten, hundred, thousand, tenthousand, hundredthousand, million = 0;
	char onec, tenc, hundredc, thousandc, tenthousandc, hundredthousandc, millionc;
	one = in % 10 / 1;
	ten = (in - one) % 100 / 10;
	hundred = (in - one - ten) % 1000 / 100;
	thousand = (in - one - ten - hundred) % 10000 / 1000;
	tenthousand = (in - one - ten - hundred - thousand) % 100000 / 10000;
	hundredthousand = (in - one - ten - hundred - thousand - tenthousand) % 1000000 / 100000;
	million = (in - one - ten - hundred - thousand - tenthousand - hundredthousand) % 10000000 / 1000000;

	onec = inttochar(one);
	tenc = inttochar(ten);
	hundredc = inttochar(hundred);
	thousandc = inttochar(thousand);
	tenthousandc = inttochar(tenthousand);
	hundredthousandc = inttochar(hundredthousand);
	millionc = inttochar(million);

	out[7] = 0;
	out[6] = onec;
	out[5] = tenc;
	out[4] = hundredc;
	out[3] = thousandc;
	out[2] = tenthousandc;
	out[1] = hundredthousandc;
	out[0] = millionc;

}

#endif
