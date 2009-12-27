#include <cstdio>

unsigned int masks[8000008];

unsigned int checksum2(char str[], int len)
{
	unsigned int r = 0;
	for(int i=0;i<len * 8;i++)
	{
		int bit = str[i/8] & 1<<(7-i%8);
		if(bit)
		{
			r ^= masks[len*8-1-i];
		}
	}
	return r;
}

unsigned int apply(unsigned int prev, int bpos, char mods)
{
	for(int i=0;i<8;i++)
	{
		int bit = mods & 1<<(7-i%8);
		if(bit)
		{
			prev ^= masks[bpos*8+7-i];
		}
	}
	return prev;
}

void precalc(void)
{
	masks[0]=1;
	for(int i=1;i<=8000000;i++)
	{
		masks[i] = masks[i-1] << 1;
		if(masks[i-1] & (1<<31))
			masks[i] ^= 0x04c11db7;
	}
}

int main()
{
	precalc();

	char str[1000001],c;
	int TESTS,n,changes,p;
	for (scanf ("%d", &TESTS); TESTS>0; TESTS--) {
		scanf ("%d %s", &n, str); // read the input
		unsigned int current = checksum2(str,n);
		printf ("%u\n", checksum2(str, n)); // compute checksum for original string
		for (scanf ("%d", &changes); changes>0; changes--) 
		{
			scanf ("%d %c", &p, &c); // apply the change
			current = apply(current, n-p, str[p-1]^c);
			str[p-1] = c;
			printf ("%u\n", current);
		}
	}
}

