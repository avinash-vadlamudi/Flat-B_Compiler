declblock{
	int n,r,val,den,i,j,num,t;
}
codeblock{
	read t;
	for i = 1,t{
	read n,r;
	num = 1;
	for j = 1,r,1{
		den = n-j+1;
		num = (num*den)/j;
	}

	println num;
	}
}
