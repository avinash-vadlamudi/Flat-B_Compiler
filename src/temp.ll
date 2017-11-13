; ModuleID = 'FlatB Compiler'

@t = common global i32 0, align 4
@num = common global i32 0, align 4
@j = common global i32 0, align 4
@i = common global i32 0, align 4
@den = common global i32 0, align 4
@val = common global i32 0, align 4
@r = common global i32 0, align 4
@n = common global i32 0, align 4
@0 = private unnamed_addr constant [3 x i8] c"%d\00"
@1 = private unnamed_addr constant [5 x i8] c"%d%d\00"
@2 = private unnamed_addr constant [5 x i8] c"%d \0A\00"

define i32 @main() {
entry:
  %0 = call i32 @scanf(i8* getelementptr inbounds ([3 x i8], [3 x i8]* @0, i32 0, i32 0), i32* @t)
  %1 = load i32, i32* @t
  store i32 1, i32* @i
  %2 = load i32, i32* @i
  %cond_cont = icmp ule i32 %2, %1
  br i1 %cond_cont, label %loopBlock, label %nextBlock

loopBlock:                                        ; preds = %nextBlock2, %entry
  %3 = call i32 bitcast (i32 (i8*, i32*)* @scanf to i32 (i8*, i32*, i32*)*)(i8* getelementptr inbounds ([5 x i8], [5 x i8]* @1, i32 0, i32 0), i32* @n, i32* @r)
  store i32 1, i32* @num
  %4 = load i32, i32* @r
  store i32 1, i32* @j
  %5 = load i32, i32* @j
  %cond_cont3 = icmp ule i32 %5, %4
  br i1 %cond_cont3, label %loopBlock1, label %nextBlock2

nextBlock:                                        ; preds = %nextBlock2, %entry
  ret i32 0

loopBlock1:                                       ; preds = %loopBlock1, %loopBlock
  %6 = load i32, i32* @n
  %7 = load i32, i32* @j
  %SubOp = sub i32 %6, %7
  %AddOp = add i32 %SubOp, 1
  store i32 %AddOp, i32* @den
  %8 = load i32, i32* @num
  %9 = load i32, i32* @den
  %MulOp = mul i32 %8, %9
  %10 = load i32, i32* @j
  %DivOp = udiv i32 %MulOp, %10
  store i32 %DivOp, i32* @num
  %11 = load i32, i32* @j
  %12 = load i32, i32* @r
  %update = add i32 %11, 1
  store i32 %update, i32* @j
  %cond_cont4 = icmp ule i32 %update, %12
  br i1 %cond_cont4, label %loopBlock1, label %nextBlock2

nextBlock2:                                       ; preds = %loopBlock1, %loopBlock
  %13 = load i32, i32* @num
  %14 = call i32 @printf(i8* getelementptr inbounds ([5 x i8], [5 x i8]* @2, i32 0, i32 0), i32 %13)
  %15 = load i32, i32* @i
  %16 = load i32, i32* @t
  %update5 = add i32 %15, 1
  store i32 %update5, i32* @i
  %cond_cont6 = icmp ule i32 %update5, %16
  br i1 %cond_cont6, label %loopBlock, label %nextBlock
}

declare i32 @scanf(i8*, i32*)

declare i32 @printf(i8*, i32)
