declblock{
	int data[40];
	int i,sum;
}
codeblock{
	i = 10;
	sum = 0;
	if i==10 {
		while i<13 {
			i = i + 1;
			sum = sum + i;
			data[sum] = sum;
		}
	}
	for i = 1,10,1 {
		sum = sum + i;
	}

	print "i: ", i;
	println "Sum: ", sum;
}
