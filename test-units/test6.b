declblock{
	int data[100];
	int i,sum;
}
codeblock{
	i = 10;
	sum = 2+5*3;
	println "sum :",sum;
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
