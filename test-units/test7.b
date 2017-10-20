declblock{
	int data[100];
	int i,sum;
}
codeblock{
	sum = 0;
	read i;
L1:	i = i+1;
		sum = sum + i;
		if sum == 10 {
		goto L3;
		}
		goto L1 if sum<60;
		goto L1 if sum<100;

L3:	println "sum : ",sum;
		println "i : ",i;
}
