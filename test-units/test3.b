declblock{
	int data[36];
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

	println "i: ", i;
	print "Sum: ", sum;
}
