declblock{
	int data[37];
	int i,sum;
}
codeblock{
	read i;
	sum = 1;
	if i==10 {
		while i<13 {
			i = i + 1;
			sum = sum + i;
			data[sum] = sum;
		}
	}
	else
	{
	
		for i = 1,10,1 {
			sum = sum + i;
		}

	}

	print "i: ", i;
	println "Sum: ", sum;
}
