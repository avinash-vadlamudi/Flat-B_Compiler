declblock{
	int n,j,i,a[30],temp;
}

codeblock{
	n = 10;
	n = 10-3;
	while(n<10)
	{
		n = 1000;
L1:		n = n-1;
		print n;
		if(n<1)
		{
			goto L2;
		}

		goto L1;
		
		n = n+1;
	}
L2:	print n;
}
