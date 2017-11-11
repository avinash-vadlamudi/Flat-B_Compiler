declblock{
	int i,j,n,a[100],temp,temp2,temp3;
}
codeblock{
	read n;
	for i = 0,n-1,1
	{
		read a[i];
	}
	for i = 0,n-2,1
	{
		for j = 0,n-i-2,1
		{
			if(a[j]>a[j+1])
			{
				temp = a[j];
				a[j]=a[j+1];
				a[j+1] = temp;
			}
		}
	}
	for i = 0,n-1
	{
		print a[i];
	}
}
