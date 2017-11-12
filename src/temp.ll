; ModuleID = 'FlatB Compiler'

@num = common global i32 0, align 4
@i = common global i32 0, align 4
@den = common global i32 0, align 4
@val = common global i32 0, align 4
@r = common global i32 0, align 4
@n = common global i32 0, align 4
@0 = private unnamed_addr constant [5 x i8] c"%d%d\00"
@1 = private unnamed_addr constant [5 x i8] c"%d \0A\00"

define i32 @main() {
entry:
  %0 = call i32 @scanf(i8* getelementptr inbounds ([5 x i8], [5 x i8]* @0, i32 0, i32 0), i32* @n, i32* @r)
  store i32 1, i32* @num
  %1 = load i32, i32* @r
  store i32 1, i32* @i
  %2 = load i32, i32* @i
  %cond_cont = icmp ule i32 %2, %1
  br i1 %cond_cont, label %loopBlock, label %nextBlock

loopBlock:                                        ; preds = %loopBlock, %entry
  %3 = load i32, i32* @n
  %4 = load i32, i32* @i
  %SubOp = sub i32 %3, %4
  %AddOp = add i32 %SubOp, 1
  store i32 %AddOp, i32* @den
  %5 = load i32, i32* @num
  %6 = load i32, i32* @den
  %MulOp = mul i32 %5, %6
  %7 = load i32, i32* @i
  %DivOp = udiv i32 %MulOp, %7
  store i32 %DivOp, i32* @num
  %8 = load i32, i32* @i
  %9 = load i32, i32* @r
  %update = add i32 %8, 1
  store i32 %update, i32* @i
  %cond_cont1 = icmp ule i32 %update, %9
  br i1 %cond_cont1, label %loopBlock, label %nextBlock

nextBlock:                                        ; preds = %loopBlock, %entry
  %10 = load i32, i32* @num
  %11 = call i32 @printf(i8* getelementptr inbounds ([5 x i8], [5 x i8]* @1, i32 0, i32 0), i32 %10)
  ret i32 0
}

declare i32 @scanf(i8*, i32*, i32*)

declare i32 @printf(i8*, i32)
