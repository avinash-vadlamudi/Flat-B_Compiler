declblock{
	int i,j,n;
}
codeblock{
	read n;
	for i = 0,n-1,1
	{
		for j = 1,n-i-1,1
		{
			print " ";
		}
		for j = 1,i+1,1
		{
			print " * ";
		}
		for j = 1,n-i-1,1
		{
			print " ";
		}
		println "";
	}
}
