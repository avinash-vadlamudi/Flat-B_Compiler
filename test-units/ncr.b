declblock{
	int n,r,val,den,i,num;
}
codeblock{
	read n,r;
	num = 1;
	for i = 1,r,1{
		den = n-i+1;
		num = (num*den)/i;
	}
	println num;
}
