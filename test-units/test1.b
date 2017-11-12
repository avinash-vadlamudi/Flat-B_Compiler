declblock{
	int data[100];
	int i,sum;
}
codeblock{
	i = 10;
	sum = 0;
	if i==10 {
		while i<100000 {
			i = i + 1;
			sum = sum + i;
		}
	}

	print "i: ", i;
	println "Sum: ",sum+1,sum;
}
