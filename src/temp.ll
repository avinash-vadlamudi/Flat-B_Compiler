; ModuleID = 'FlatB Compiler'

@n = common global i32 0, align 4
@j = common global i32 0, align 4
@i = common global i32 0, align 4
@0 = private unnamed_addr constant [3 x i8] c"%d\00"
@1 = private unnamed_addr constant [3 x i8] c"  \00"
@2 = private unnamed_addr constant [2 x i8] c" \00"
@3 = private unnamed_addr constant [5 x i8] c" *  \00"
@4 = private unnamed_addr constant [4 x i8] c" * \00"
@5 = private unnamed_addr constant [3 x i8] c"  \00"
@6 = private unnamed_addr constant [2 x i8] c" \00"
@7 = private unnamed_addr constant [3 x i8] c" \0A\00"
@8 = private unnamed_addr constant [1 x i8] zeroinitializer
@9 = private unnamed_addr constant [3 x i8] c"  \00"
@10 = private unnamed_addr constant [2 x i8] c" \00"
@11 = private unnamed_addr constant [5 x i8] c" *  \00"
@12 = private unnamed_addr constant [4 x i8] c" * \00"
@13 = private unnamed_addr constant [3 x i8] c"  \00"
@14 = private unnamed_addr constant [2 x i8] c" \00"
@15 = private unnamed_addr constant [3 x i8] c" \0A\00"
@16 = private unnamed_addr constant [1 x i8] zeroinitializer

define i32 @main() {
entry:
  %0 = call i32 @scanf(i8* getelementptr inbounds ([3 x i8], [3 x i8]* @0, i32 0, i32 0), i32* @n)
  %1 = load i32, i32* @n
  %SubOp = sub i32 %1, 1
  store i32 0, i32* @i
  %2 = load i32, i32* @i
  %cond_cont = icmp ule i32 %2, %SubOp
  br i1 %cond_cont, label %loopBlock, label %nextBlock

loopBlock:                                        ; preds = %nextBlock18, %entry
  %3 = load i32, i32* @n
  %4 = load i32, i32* @i
  %SubOp1 = sub i32 %3, %4
  %SubOp2 = sub i32 %SubOp1, 1
  store i32 1, i32* @j
  %5 = load i32, i32* @j
  %cond_cont5 = icmp ule i32 %5, %SubOp2
  br i1 %cond_cont5, label %loopBlock3, label %nextBlock4

nextBlock:                                        ; preds = %nextBlock18, %entry
  %6 = load i32, i32* @n
  %SubOp27 = sub i32 %6, 1
  store i32 1, i32* @i
  %7 = load i32, i32* @i
  %cond_cont30 = icmp ule i32 %7, %SubOp27
  br i1 %cond_cont30, label %loopBlock28, label %nextBlock29

loopBlock3:                                       ; preds = %loopBlock3, %loopBlock
  %8 = call i32 @printf(i8* getelementptr inbounds ([3 x i8], [3 x i8]* @1, i32 0, i32 0))
  %9 = load i32, i32* @j
  %10 = load i32, i32* @n
  %11 = load i32, i32* @i
  %SubOp6 = sub i32 %10, %11
  %SubOp7 = sub i32 %SubOp6, 1
  %update = add i32 %9, 1
  store i32 %update, i32* @j
  %cond_cont8 = icmp ule i32 %update, %SubOp7
  br i1 %cond_cont8, label %loopBlock3, label %nextBlock4

nextBlock4:                                       ; preds = %loopBlock3, %loopBlock
  %12 = load i32, i32* @i
  %AddOp = add i32 %12, 1
  store i32 1, i32* @j
  %13 = load i32, i32* @j
  %cond_cont11 = icmp ule i32 %13, %AddOp
  br i1 %cond_cont11, label %loopBlock9, label %nextBlock10

loopBlock9:                                       ; preds = %loopBlock9, %nextBlock4
  %14 = call i32 @printf(i8* getelementptr inbounds ([5 x i8], [5 x i8]* @3, i32 0, i32 0))
  %15 = load i32, i32* @j
  %16 = load i32, i32* @i
  %AddOp12 = add i32 %16, 1
  %update13 = add i32 %15, 1
  store i32 %update13, i32* @j
  %cond_cont14 = icmp ule i32 %update13, %AddOp12
  br i1 %cond_cont14, label %loopBlock9, label %nextBlock10

nextBlock10:                                      ; preds = %loopBlock9, %nextBlock4
  %17 = load i32, i32* @n
  %18 = load i32, i32* @i
  %SubOp15 = sub i32 %17, %18
  %SubOp16 = sub i32 %SubOp15, 1
  store i32 1, i32* @j
  %19 = load i32, i32* @j
  %cond_cont19 = icmp ule i32 %19, %SubOp16
  br i1 %cond_cont19, label %loopBlock17, label %nextBlock18

loopBlock17:                                      ; preds = %loopBlock17, %nextBlock10
  %20 = call i32 @printf(i8* getelementptr inbounds ([3 x i8], [3 x i8]* @5, i32 0, i32 0))
  %21 = load i32, i32* @j
  %22 = load i32, i32* @n
  %23 = load i32, i32* @i
  %SubOp20 = sub i32 %22, %23
  %SubOp21 = sub i32 %SubOp20, 1
  %update22 = add i32 %21, 1
  store i32 %update22, i32* @j
  %cond_cont23 = icmp ule i32 %update22, %SubOp21
  br i1 %cond_cont23, label %loopBlock17, label %nextBlock18

nextBlock18:                                      ; preds = %loopBlock17, %nextBlock10
  %24 = call i32 @printf(i8* getelementptr inbounds ([3 x i8], [3 x i8]* @7, i32 0, i32 0))
  %25 = load i32, i32* @i
  %26 = load i32, i32* @n
  %SubOp24 = sub i32 %26, 1
  %update25 = add i32 %25, 1
  store i32 %update25, i32* @i
  %cond_cont26 = icmp ule i32 %update25, %SubOp24
  br i1 %cond_cont26, label %loopBlock, label %nextBlock

loopBlock28:                                      ; preds = %nextBlock44, %nextBlock
  %27 = load i32, i32* @i
  store i32 1, i32* @j
  %28 = load i32, i32* @j
  %cond_cont33 = icmp ule i32 %28, %27
  br i1 %cond_cont33, label %loopBlock31, label %nextBlock32

nextBlock29:                                      ; preds = %nextBlock44, %nextBlock
  ret i32 0

loopBlock31:                                      ; preds = %loopBlock31, %loopBlock28
  %29 = call i32 @printf(i8* getelementptr inbounds ([3 x i8], [3 x i8]* @9, i32 0, i32 0))
  %30 = load i32, i32* @j
  %31 = load i32, i32* @i
  %update34 = add i32 %30, 1
  store i32 %update34, i32* @j
  %cond_cont35 = icmp ule i32 %update34, %31
  br i1 %cond_cont35, label %loopBlock31, label %nextBlock32

nextBlock32:                                      ; preds = %loopBlock31, %loopBlock28
  %32 = load i32, i32* @n
  %33 = load i32, i32* @i
  %SubOp36 = sub i32 %32, %33
  store i32 1, i32* @j
  %34 = load i32, i32* @j
  %cond_cont39 = icmp ule i32 %34, %SubOp36
  br i1 %cond_cont39, label %loopBlock37, label %nextBlock38

loopBlock37:                                      ; preds = %loopBlock37, %nextBlock32
  %35 = call i32 @printf(i8* getelementptr inbounds ([5 x i8], [5 x i8]* @11, i32 0, i32 0))
  %36 = load i32, i32* @j
  %37 = load i32, i32* @n
  %38 = load i32, i32* @i
  %SubOp40 = sub i32 %37, %38
  %update41 = add i32 %36, 1
  store i32 %update41, i32* @j
  %cond_cont42 = icmp ule i32 %update41, %SubOp40
  br i1 %cond_cont42, label %loopBlock37, label %nextBlock38

nextBlock38:                                      ; preds = %loopBlock37, %nextBlock32
  %39 = load i32, i32* @i
  store i32 1, i32* @j
  %40 = load i32, i32* @j
  %cond_cont45 = icmp ule i32 %40, %39
  br i1 %cond_cont45, label %loopBlock43, label %nextBlock44

loopBlock43:                                      ; preds = %loopBlock43, %nextBlock38
  %41 = call i32 @printf(i8* getelementptr inbounds ([3 x i8], [3 x i8]* @13, i32 0, i32 0))
  %42 = load i32, i32* @j
  %43 = load i32, i32* @i
  %update46 = add i32 %42, 1
  store i32 %update46, i32* @j
  %cond_cont47 = icmp ule i32 %update46, %43
  br i1 %cond_cont47, label %loopBlock43, label %nextBlock44

nextBlock44:                                      ; preds = %loopBlock43, %nextBlock38
  %44 = call i32 @printf(i8* getelementptr inbounds ([3 x i8], [3 x i8]* @15, i32 0, i32 0))
  %45 = load i32, i32* @i
  %46 = load i32, i32* @n
  %SubOp48 = sub i32 %46, 1
  %update49 = add i32 %45, 1
  store i32 %update49, i32* @i
  %cond_cont50 = icmp ule i32 %update49, %SubOp48
  br i1 %cond_cont50, label %loopBlock28, label %nextBlock29
}

declare i32 @scanf(i8*, i32*)

declare i32 @printf(i8*)
